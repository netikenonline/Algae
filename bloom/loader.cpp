#include <chrono>
#include <shlobj_core.h>
#include <MinHook.h>
#include <AlgaeSDK.h>

typedef int (WINAPI* FishWinMain)(HINSTANCE, HINSTANCE, LPSTR, int);
typedef void(* ModInitFunc)(const ModHost* host);
typedef bool(* AlgaeInitFunc)(const ModHost* host);

void LoadWinMM(); // winmm_proxy.cpp

//static CRITICAL_SECTION gLogCrit;
static HANDLE           gLogFile = INVALID_HANDLE_VALUE;
static wchar_t          gGameDir[MAX_PATH];
static wchar_t          gAlgaeDir[MAX_PATH];
static wchar_t          gModsDir[MAX_PATH];
static ModHost          gHost;

static std::chrono::steady_clock::time_point algaeStartTime;

static void Log(const char* format, ...)
{
    // TODO possible chance to overrun if we're coming from Algae_Log that has a 1024 buffer too
    // Is 1024 good enough for logging? Is this even worth worrying over?

    auto algaeNowTime = std::chrono::steady_clock::now();
    unsigned long long ms = std::chrono::duration_cast
        <std::chrono::milliseconds>(algaeNowTime - algaeStartTime).count();

    char buf[1024];
    int tLen = snprintf(buf, sizeof(buf), "[%0.3f] ", (ms / 1000.0));
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buf + tLen, sizeof(buf) - (tLen+1), format, args);
    len += tLen;
    va_end(args);

    // Output to console
    OutputDebugStringA(buf);
    OutputDebugStringA("\n");

    // Also output to log file, if it's ready
    if (gLogFile != nullptr)
    {
        DWORD bytesWritten;
        WriteFile(gLogFile, buf, len, &bytesWritten, NULL);
        WriteFile(gLogFile, "\r\n", 2, &bytesWritten, NULL);
    }
}

static void LoadMods()
{
    // TODO recursive file search at some point please!

    wchar_t modPattern[MAX_PATH];
    swprintf_s(modPattern, L"%s\\*.dll", gModsDir);
    WIN32_FIND_DATAW findData;
    HANDLE find = FindFirstFileW(modPattern, &findData);

    if (find == INVALID_HANDLE_VALUE)
    {
        Log("[ALGAE] No mods found!");
        return; // No mods found (not an error... hopefully)
    }

    int modCounter = 0;
    do
    {
        wchar_t modPath[MAX_PATH];
        swprintf_s(modPath, L"%s\\%s", gModsDir, findData.cFileName);
        HMODULE mod = LoadLibraryW(modPath);
        if (mod == NULL)
        {
            Log("[ALGAE] Unknown error occured while loading %ls, skipping.", findData.cFileName);
            continue;
        }
        ModInitFunc modInit = (ModInitFunc)GetProcAddress(mod, "ModInit");
        if (modInit == NULL)
        {
            Log("[ALGAE] Found potential mod %ls but no suitable ModInit exists, skipping.", findData.cFileName);
            continue;
        }
        Log("[ALGAE] Starting %ls...", findData.cFileName);
        modInit(&gHost);
        modCounter++;
    } while (FindNextFileW(find, &findData));
    Log("[ALGAE] Finished mod initialization (%d mod(s) loaded).", modCounter);
    FindClose(find);
}

static int WINAPI Hook_WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
    MH_DisableHook((LPVOID)Algae::Addr::WinMain);
    MH_Uninitialize();

    gHost.Version = ALGAE_SDK_VERSION;
    gHost.GameDir = gGameDir;
    gHost.AlgaeDir = gAlgaeDir;
    gHost.ModsDir = gModsDir;
    gHost.Log = Log;

    Log("[ALGAE] Hello from WinMain hook! Now setting up Algae SDK v%d...", ALGAE_SDK_VERSION);

    // Load up Algae SDK and then mods after
    wchar_t sdkPath[MAX_PATH];
    swprintf_s(sdkPath, L"%s\\AlgaeSDK.dll", gGameDir);
    HMODULE sdk = LoadLibraryW(sdkPath);
    if (sdk == NULL)
    {
        Log("[ALGAE] ...either the SDK is missing from your Insaniquarium folder, or may be corrupted. Continuing without mods!");
    }
    else
    {
        Log("[ALGAE] ...found! Initializing...");
        AlgaeInitFunc algaeInit = (AlgaeInitFunc)GetProcAddress(sdk, "Algae_Init");
        algaeInit(&gHost);

        Log("[ALGAE] Algae SDK initialization finished! Loading mods.");

        LoadMods();
    }

    Log("[ALGAE] Algae setup finished. Starting game now!");

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

    algaeStartTime = std::chrono::steady_clock::now();

    if (reason != DLL_PROCESS_ATTACH)
        return TRUE;

    DisableThreadLibraryCalls(instance);

    // Get folders for game, Algae dir and mods
    GetModuleFileNameW(NULL, gGameDir, MAX_PATH);
    wchar_t* lastSlash = wcsrchr(gGameDir, L'\\');
    *lastSlash = L'\0'; // Truncate by slapping a null byte in there
    PWSTR algaeDir = NULL;
    SHGetKnownFolderPath(FOLDERID_ProgramData, KF_FLAG_CREATE, NULL, &algaeDir);
    swprintf_s(gAlgaeDir, L"%s\\PopCap Games\\Insaniquarium\\Algae", algaeDir);
    // TODO handle potential error if path doesn't exist (have to boot the game at least once mod-free)
    CreateDirectoryW(gAlgaeDir, NULL);
    swprintf_s(gModsDir, L"%s\\mods", gAlgaeDir);

    // Initialize logger as early as we can (so various things can access it)
    wchar_t logPath[MAX_PATH];
    swprintf_s(logPath, L"%s\\Algae.log", gAlgaeDir);
    gLogFile = CreateFileW(logPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    Log("[ALGAE] Algae log file is created:   %ls", logPath);
    Log("[ALGAE] Found game path (GameDir):   %ls", gGameDir);
    Log("[ALGAE] Found Algae path (AlgaeDir): %ls", gAlgaeDir);
    Log("[ALGAE] Found mods path (ModsDir):   %ls", gModsDir);
    CreateDirectoryW(gModsDir, NULL);

    LoadWinMM();

    Log("[ALGAE] Initialized winmm.dll passthrough.");

    // It's hooking time >:3
    LPVOID winMainAddr = (LPVOID)Algae::Addr::WinMain;
    MH_STATUS status = MH_Initialize();
    if (status == MH_OK)
    {
        Log("[ALGAE] MinHook initialized. Connecting to WinMain...");
        status = MH_CreateHook(winMainAddr, (LPVOID)&Hook_WinMain, NULL);
        if (status == MH_OK)
        {
            MH_EnableHook(winMainAddr);
            Log("[ALGAE] ...connection successful! Continuing.");
        }
        else
        {
            Log("[ALGAE] ...woops, something happened (%s). Continuing without mods!", MH_StatusToString(status));
            MH_Uninitialize();
        }
    }
    else
    {
        Log("[ALGAE] Could not hook WinMain (%s). Continuing without mods!", MH_StatusToString(status));
        MH_Uninitialize();
    }

    return TRUE;
}
