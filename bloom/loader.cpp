#include <cstdio>
#include <MinHook.h>
#include <AlgaeSDK.h>

typedef int (WINAPI* FishWinMain)(HINSTANCE, HINSTANCE, LPSTR, int);
typedef void(* ModInitFunc)(const ModHost* host);
typedef bool(* AlgaeInitFunc)(const ModHost* host);

void LoadWinMM(); // winmm_proxy.cpp

static wchar_t          gGameDir[MAX_PATH];
static wchar_t          gModsDir[MAX_PATH];
static ModHost          gHost;

static void LoadMods()
{
    wchar_t modPattern[MAX_PATH];
    swprintf_s(modPattern, L"%s\\*.dll", gModsDir);
    WIN32_FIND_DATAW findData;
    HANDLE find = FindFirstFileW(modPattern, &findData);

    if (find == INVALID_HANDLE_VALUE)
    {
        return; // No mods found
    }

    do
    {
        wchar_t modPath[MAX_PATH];
        swprintf_s(modPath, L"%s\\%s", gModsDir, findData.cFileName);
        HMODULE mod = LoadLibraryW(modPath);
        if (mod == NULL)
        {
            continue; // Bad load, skip
        }
        ModInitFunc modInit = (ModInitFunc)GetProcAddress(mod, "ModInit");
        if (modInit == NULL)
        {
            continue; // No ModInit, skip
        }
        modInit(&gHost);
    } while (FindNextFileW(find, &findData));
    FindClose(find);
}

static int WINAPI Hook_WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
    MH_DisableHook((LPVOID)Algae::Addr::WinMain);
    MH_Uninitialize();

    gHost.GameDir = gGameDir;
    gHost.ModsDir = gModsDir;

    // Load up Algae SDK and then mods after
    wchar_t sdkPath[MAX_PATH];
    swprintf_s(sdkPath, L"%s\\AlgaeSDK.dll", gGameDir);
    HMODULE sdk = LoadLibraryW(sdkPath);
    if (sdk == NULL)
    {
        return 0;
    }
    AlgaeInitFunc algaeInit = (AlgaeInitFunc)GetProcAddress(sdk, "Algae_Init");
    algaeInit(&gHost);

    LoadMods();

    // Call original WinMain when done
    return ((FishWinMain)Algae::Addr::WinMain)(instance, prevInstance, cmdLine, cmdShow);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    // Use me for debugging!
    /*
    while (!IsDebuggerPresent()) {
        Sleep(100);
    }
    */

    if (reason != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(instance);

    // Get folders for game and mods
    GetModuleFileNameW(NULL, gGameDir, MAX_PATH);
    wchar_t* lastSlash = wcsrchr(gGameDir, L'\\');
    *lastSlash = L'\0'; // Truncate by slapping a null byte in there
    swprintf_s(gModsDir, L"%s\\mods", gGameDir);
    CreateDirectoryW(gModsDir, NULL);

    LoadWinMM();

    // It's hooking time (what the fuck minhook is so cool)
    LPVOID winMainAddr = (LPVOID)Algae::Addr::WinMain;
    MH_STATUS status = MH_Initialize();
    if (status == MH_OK)
    {
        // TODO error handling
        MH_CreateHook(winMainAddr, (LPVOID)&Hook_WinMain, NULL);
        MH_EnableHook(winMainAddr);
    }
    else
    {
        // Couldn't hook for whatever reason, pull back MH and just play without mods
        // TODO log this? Error popup?
        MH_Uninitialize();
    }

    return TRUE;
}
