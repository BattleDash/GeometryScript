// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>

#include "program.h"
#include <cstdio>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason,
    LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        gProgram = new GeometryScript::Program(hModule);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        delete gProgram;

    return TRUE;
}