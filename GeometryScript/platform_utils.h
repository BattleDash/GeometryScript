#pragma once

#include <Windows.h>
#include <psapi.h>

namespace GeometryScript
{
	namespace Utilities
	{
		class PlatformUtils
		{
		public:
			static uintptr_t BaseAddress();
			static PBYTE FindPattern(const char* pattern, const char* mask, int patternIndex);
			static PBYTE FindPattern(PVOID pBase, DWORD dwSize, LPCSTR lpPattern, LPCSTR lpMask);
			static PBYTE FindPattern(LPCSTR lpPattern, LPCSTR lpMask);
			static PBYTE FindPattern(LPCSTR lpPattern, LPCSTR lpMask, LPCWSTR lpModuleName);
		private:
			static BOOL MaskCompare(PVOID pBuffer, LPCSTR lpPattern, LPCSTR lpMask);
		};
	}
}