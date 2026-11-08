#include <chrono>
#include <filesystem>
#include <fstream>
#include <optional>
#include <shlobj_core.h>
#include <string>
#include <MinHook.h>
#include <AlgaeSDK.h>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

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

static std::optional<ModInfo> LoadModInfo(fs::path filePath)
{
    ModInfo modInfo;
    modInfo.dllPath = filePath.string();

    // Parse the manifest JSON in the immediate area ("manifest.jsonc" or ".json" are valid)
    fs::path jsonPath = filePath.parent_path().append("manifest.jsonc");
    if (!fs::exists(jsonPath)) jsonPath = filePath.parent_path().append("manifest.json");

    if (fs::exists(jsonPath) && fs::is_regular_file(jsonPath))
    {
        std::ifstream jsonFile(jsonPath);

        if (!jsonFile.is_open()) {
            Log("[ALGAE] Failed to load mod manifest (is the file busy?): %ls", jsonPath.c_str());
            return std::nullopt;
        }

        try
        {
            // Parse w/ comments support
            json data = json::parse(jsonFile, nullptr, true, true);

            modInfo.name = data["name"];
            modInfo.version = data["version"];
            modInfo.description = data["description"];
            modInfo.creator = data["creator"];
            modInfo.iconPath = data["iconPath"];

            for (const auto& res : data["resources"])
            {
                modInfo.resources.push_back(ModInfoRes{ res["id"], res["type"], res["path"] });
            }
        }
        catch (const json::parse_error& e)
        {
            Log("[ALGAE] Mod manifest parsing error: %s", e.what());
            return std::nullopt;
        }
    }
    else
    {
        Log("[ALGAE] Mod loading without a manifest.jsonc or manifest.json nearby!");
        return std::nullopt;
    }

    return modInfo;
}

static int LoadMods()
{
    // Exit early if no DLL's exist
    wchar_t modPattern[MAX_PATH];
    swprintf_s(modPattern, L"%s\\*.dll", gModsDir);
    WIN32_FIND_DATAW findData;
    if (HANDLE find = FindFirstFileW(modPattern, &findData); find == INVALID_HANDLE_VALUE)
    {
        Log("[ALGAE] No mods found!");
        FindClose(find);
        return 0;
    }

    int modCounter = 0;
    try
    {
        for (const auto& file : fs::recursive_directory_iterator(gModsDir, fs::directory_options::skip_permission_denied))
        {
            if (file.path().extension() == ".dll")
            {
                Log("[ALGAE] Found mod: %ls", file.path());
                HMODULE mod = LoadLibraryW(file.path().c_str());
                if (mod == NULL)
                {
                    Log("[ALGAE] Unknown error occured while loading %ls, skipping.", file.path().filename().c_str());
                    continue;
                }
                ModInitFunc modInit = (ModInitFunc)GetProcAddress(mod, "ModInit");
                if (modInit == NULL)
                {
                    Log("[ALGAE] Found potential mod %ls but no suitable ModInit exists, skipping.", file.path().filename().c_str());
                    continue;
                }
                auto modInfo = LoadModInfo(file.path());
                if (!modInfo.has_value())
                {
                    Log("[ALGAE] Mod %ls is missing a manifest file or an error occured, skipping.", file.path().filename().c_str());
                    FreeLibrary(mod);
                    continue;
                }
                gHost.Infos.push_back(modInfo.value());
                Log("[ALGAE] Starting %ls...", file.path().filename().c_str());
                modInit(&gHost);
                modCounter++;
            }
        }
        Log("[ALGAE] Finished mod initialization (%d mod(s) loaded).", modCounter);
    }
    catch (const fs::filesystem_error& e)
    {
        // idfk what to do, panic?
        Log("[ALGAE] Filesystem error while reading mods (stopping here): \"%s\"", e.what());
    }
    return modCounter;
}

static int WINAPI Hook_WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)
{
    MH_DisableHook((LPVOID)Algae::Addr::WinMain);
    MH_Uninitialize();

    gHost.GameDir = gGameDir;
    gHost.AlgaeDir = gAlgaeDir;
    gHost.ModsDir = gModsDir;
    gHost.Log = Log;

    Log("[ALGAE] Hello from WinMain hook! Now setting up Algae SDK v%s...", ALGAE_SDK_VERSION);

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
        int modCount = LoadMods();
        gHost.ModCount = modCount;
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
    CreateDirectoryW(gAlgaeDir, NULL);
    swprintf_s(gModsDir, L"%s\\mods", gAlgaeDir);
    CreateDirectoryW(gModsDir, NULL);

    // Initialize logger as early as we can (so various things can access it)
    wchar_t logPath[MAX_PATH];
    swprintf_s(logPath, L"%s\\Algae.log", gAlgaeDir);
    gLogFile = CreateFileW(logPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    Log("[ALGAE] Algae log file is created:   %ls", logPath);
    Log("[ALGAE] Found game path (GameDir):   %ls", gGameDir);
    Log("[ALGAE] Found Algae path (AlgaeDir): %ls", gAlgaeDir);
    Log("[ALGAE] Found mods path (ModsDir):   %ls", gModsDir);

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
