#define ALGAE_SDK_BUILD
#include <AlgaeSDK.h>
#include <MinHook.h>
#include <vector>
#include <unordered_map>

bool Algae_InstallEventHooks();

std::unordered_map<uintptr_t, uintptr_t> algaeFuncStore;
std::unordered_map<uintptr_t, uintptr_t> algaeHookOverrides;
std::unordered_map<uintptr_t, std::vector<uintptr_t>> algaePreHooks;
std::unordered_map<uintptr_t, std::vector<uintptr_t>> algaePostHooks;

static const ModHost* gHost = nullptr;

// Called from AlgaeBloom (DLL loader) side
ALGAE_API_DECL bool Algae_Init(const ModHost* host)
{
    gHost = host;

    MH_STATUS status = MH_Initialize();
    if (status != MH_OK)
    {
        Algae_Log("[ALGAE] ERROR: MinHook failed to start on SDK side (%s).", MH_StatusToString(status));
        return false;
    }
    Algae_Log("[ALGAE] SDK event hooks being installed...");
    if (!Algae_InstallEventHooks())
    {
        Algae_Log("[ALGAE] SDK event hooking error! (May be a different or modified game version?)");
        return false;
    }

    return true;
}

ALGAE_API_DECL int Algae_GetVersion()
{
    return ALGAE_SDK_VERSION;
}

ALGAE_API_DECL void Algae_Log(const char* format, ...)
{
    // Best way I can think of is pack into buf now so it can be passed over
    char buf[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    gHost->Log(buf);
}

ALGAE_API_DECL bool Algae_CreateHook(uintptr_t target, void* hook, void** trampoline)
{
    void* targetFunc = reinterpret_cast<void*>(target);
    MH_STATUS status = MH_CreateHook(targetFunc, hook, trampoline);
    if (status == MH_OK)
        status = MH_EnableHook(targetFunc);
    if (status != MH_OK)
    {
        Algae_Log("[ALGAE] hooking at 0x%08X failed (%s)", (unsigned)target, MH_StatusToString(status));
        return false;
    }
    return true;
}

ALGAE_API_DECL void Algae_AddPreHook(uintptr_t target, void* hook)
{
    algaePreHooks[target].push_back(reinterpret_cast<uintptr_t>(hook));
}

ALGAE_API_DECL void Algae_AddPostHook(uintptr_t target, void* hook)
{
    algaePostHooks[target].push_back(reinterpret_cast<uintptr_t>(hook));
}

ALGAE_API_DECL void Algae_SetOverrideHook(uintptr_t target, void* hook)
{
    algaeHookOverrides[target] = reinterpret_cast<uintptr_t>(hook);
}

template<class... Args>
static void RunPreHooks(uintptr_t func, Args... args)
{
    DWORD callbackFault = 0;

    for (size_t i = 0; i < algaePreHooks[func].size(); ++i)
    {
        __try
        {
            reinterpret_cast<void(*)(Args...)>(algaePreHooks[func][i])(args...);
        }
        __except (callbackFault = GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)
        {
            // TODO build SEH exception mapping... and probably a hook name mapping too, would be helpful.
            Algae_Log("[ALGAE] a pre-hook on 0x%08X crashed with exception 0x%08X!", (unsigned)func, (unsigned)callbackFault);
        }
    }
}

template<class... Args>
static void RunPostHooks(uintptr_t func, Args... args)
{
    DWORD callbackFault = 0;

    for (size_t i = 0; i < algaePostHooks[func].size(); ++i)
    {
        __try
        {
            reinterpret_cast<void(*)(Args...)>(algaePostHooks[func][i])(args...);
        }
        __except (callbackFault = GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)
        {
            // TODO build SEH exception mapping... and probably a hook name mapping too, would be helpful.
            Algae_Log("[ALGAE] a post-hook on 0x%08X crashed with exception 0x%08X!", (unsigned)func, (unsigned)callbackFault);
        }
    }
}

template<class T, class... Args>
static void Detour_RunInternal(uintptr_t funcPtr, T self, void* edx, Args... args)
{
    auto overrideKV = algaeHookOverrides.find(funcPtr);
    if (overrideKV != algaeHookOverrides.end())
    {
        // TODO work on this later
        //RunOverrideHooks(funcPtr, self, args...);
    }
    else
    {
        // Call all pre-hooks, then the trampoline, then post-hooks
        RunPreHooks(funcPtr, self, args...);
        Algae::CallInternal<void>(algaeFuncStore[funcPtr], self, edx, args...);
        RunPostHooks(funcPtr, self, args...);
    }
}

static void __fastcall Detour_TitleScreenDraw(Sexy::Widget* self, void* edx, Sexy::Graphics* g)
{
    Detour_RunInternal(Sexy::TitleScreen_Draw, self, edx, g);
}

bool Algae_InstallEventHooks()
{
    bool result = true;

    void* trampoline = nullptr;
    result &= Algae_CreateHook(Sexy::TitleScreen_Draw, &Detour_TitleScreenDraw, &trampoline);
    // Store the trampoline in a map for later
    algaeFuncStore[Sexy::TitleScreen_Draw] = reinterpret_cast<uintptr_t>(trampoline);

    return result;
}
