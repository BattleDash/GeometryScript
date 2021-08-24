#include "platform_utils.h"

#include <string>

namespace GeometryScript
{
    namespace Utilities
    {
        BOOL PlatformUtils::MaskCompare(PVOID pBuffer, LPCSTR lpPattern, LPCSTR lpMask)
        {
            for (auto value = static_cast<PBYTE>(pBuffer); *lpMask; ++lpPattern, ++lpMask, ++value)
            {
                if (*lpMask == 'x' && *reinterpret_cast<LPCBYTE>(lpPattern) != *value)
                    return false;
            }

            return true;
        }

        // Get the Base Address.
        uintptr_t PlatformUtils::BaseAddress()
        {
            return reinterpret_cast<uintptr_t>(GetModuleHandle(0));
        }

        // Find a pattern with an index, eg; if there are 2 results, and index is 1, return result #2
        PBYTE PlatformUtils::FindPattern(const char* pattern, const char* mask, int patternIndex)
        {
            MODULEINFO mInfo = { 0 };

            GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &mInfo, sizeof(mInfo));

            PVOID base = mInfo.lpBaseOfDll;
            DWORD64 size = (DWORD64)mInfo.SizeOfImage;

            DWORD64 patternLength = (DWORD64)strlen(mask);

            int patternI = 0;

            for (DWORD64 i = 0; i < size - patternLength; i++)
            {
                bool found = true;
                for (DWORD64 j = 0; j < patternLength; j++)
                {
                    found &= mask[j] == '?' || pattern[j] == *(char*)(static_cast<PBYTE>(base) + i + j);
                }

                if (found)
                {
                    if (patternI == patternIndex)
                    {
                        return static_cast<PBYTE>(base) + i;
                    }
                    patternI++;
                }
            }
            return NULL;
        }
        // Find a pattern.
        PBYTE PlatformUtils::FindPattern(PVOID pBase, DWORD dwSize, LPCSTR lpPattern, LPCSTR lpMask)
        {
            dwSize -= static_cast<DWORD>(strlen(lpMask));

            for (auto i = 0UL; i < dwSize; ++i)
            {
                auto pAddress = static_cast<PBYTE>(pBase) + i;

                if (PlatformUtils::MaskCompare(pAddress, lpPattern, lpMask))
                    return pAddress;
            }

            return NULL;
        }
        PBYTE PlatformUtils::FindPattern(LPCSTR lpPattern, LPCSTR lpMask, LPCWSTR lpModuleName)
        {
            MODULEINFO info = { 0 };

            GetModuleInformation(GetCurrentProcess(), GetModuleHandle(lpModuleName), &info, sizeof(info));

            return PlatformUtils::FindPattern(info.lpBaseOfDll, info.SizeOfImage, lpPattern, lpMask);
        }
        PBYTE PlatformUtils::FindPattern(LPCSTR lpPattern, LPCSTR lpMask)
        {
            return PlatformUtils::FindPattern(lpPattern, lpMask, 0);
        }
    }
}