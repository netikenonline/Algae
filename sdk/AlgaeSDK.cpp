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
        return false; // Uh oh
    }
    if (!Algae_InstallEventHooks())
        return false;

    return true;
}

ALGAE_API_DECL bool Algae_CreateHook(uintptr_t target, void* hook, void** trampoline)
{
    void* targetFunc = reinterpret_cast<void*>(target);
    MH_STATUS status = MH_CreateHook(targetFunc, hook, trampoline);
    if (status == MH_OK)
        status = MH_EnableHook(targetFunc);
    if (status != MH_OK)
    {
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
            // TODO handle exceptions n shiz
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
            // TODO handle exceptions n shiz
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
