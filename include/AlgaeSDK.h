#pragma once
#include <windows.h>
#include <string>
#include <Sexy/Board.h>
#include <Sexy/ButtonListener.h>
#include <Sexy/ButtonWidget.h>
#include <Sexy/Color.h>
#include <Sexy/DialogButton.h>
#include <Sexy/Font.h>
#include <Sexy/GameObject.h>
#include <Sexy/GameUtil.h>
#include <Sexy/Graphics.h>
#include <Sexy/MainScreen.h>
#include <Sexy/Resources.h>
#include <Sexy/TitleScreen.h>
#include <Sexy/Widget.h>
#include <Sexy/WidgetContainer.h>
#include <Sexy/WidgetManager.h>
#include <AlgaeTools.h>


namespace Algae
{
    namespace Addr
    {
        const uintptr_t WinMain = 0x5024F0;
    }
}

#ifdef ALGAE_SDK_BUILD
#define ALGAE_API_DECL extern "C" __declspec(dllexport)
#else
#define ALGAE_API_DECL extern "C" __declspec(dllimport)
#endif

#define STRHELPER(x) #x
#define STR(x) STRHELPER(x)

#define ALGAE_SDK_VERSION_MAJOR 0
#define ALGAE_SDK_VERSION_MINOR 0
#define ALGAE_SDK_VERSION_PATCH 1
#define ALGAE_SDK_VERSION STR(ALGAE_SDK_VERSION_MAJOR) "." STR(ALGAE_SDK_VERSION_MINOR) "." STR(ALGAE_SDK_VERSION_PATCH)

struct ModHost
{
    // Info
    int ModCount;
    // Directories
    const wchar_t* GameDir;
    const wchar_t* AlgaeDir;
    const wchar_t* ModsDir;
    // Logging
    void (*Log)(const char* format, ...);
};

ALGAE_API_DECL void Algae_Log(const char* format, ...);

// Creates and returns an event hook via MinHook to a function at the target address,
// and outputs a "trampoline" function to call as well.
ALGAE_API_DECL bool Algae_CreateHook(uintptr_t target, void* hook, void** trampoline);

// Adds a hook to a function at the target address, and calls the hook before the
// original one is called.
ALGAE_API_DECL void Algae_AddPreHook(uintptr_t target, void* hook);

// Adds a hook to a function at the target address, and calls the hook after the
// original one is called.
ALGAE_API_DECL void Algae_AddPostHook(uintptr_t target, void* hook);

// Replaces a function at the target address with your own.
// (Use at your own risk!)
ALGAE_API_DECL void Algae_SetOverrideHook(uintptr_t target, void* hook);
