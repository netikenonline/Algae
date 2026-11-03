#pragma once

#include <windows.h>
#include <string>

#include <Sexy/Color.h>
#include <Sexy/Font.h>
#include <Sexy/Graphics.h>
#include <Sexy/Res.h>
#include <Sexy/TitleScreen.h>
#include <Sexy/Widget.h>

#include <AlgaeTools.h>

namespace Algae
{
    namespace Addr
    {
        const uintptr_t WinMain = 0x5024F0;
    }

    // C++ has changed how std::strings work from 2005 to modern day, so this class
    // serves as an interop medium and allows strings to "just work" for modders.
    class OldString
    {
    public:
        OldString(std::string str) { SetInternal(str); }
        std::string ToString() const { return std::string(ToCStr()); };
        const char* ToCStr() const { return { (mRes < 16) ? mBuf : mPtr }; };
    private:
        // Handle our own value assignment from modern string to old string layout
        void SetInternal(std::string str)
        {
            mSize = str.size();
            if (mSize < 16)
            {
                mRes = 15;
                memcpy(mBuf, str.data(), mSize);
                mBuf[mSize] = '\0';
            }
            else
            {
                mRes = mSize;
                delete[] mPtr;
                mPtr = new char[mSize+1];
                std::strncpy(mPtr, str.data(), mSize + 1);
                mPtr[mSize] = '\0';
            }
        }

        void* mAlloc = nullptr; // basically unused for us
        union { char mBuf[16]; char* mPtr = nullptr; };
        size_t mSize = 0;
        size_t mRes = 15;
    };
}

#ifdef ALGAE_SDK_BUILD
#define ALGAE_API_DECL extern "C" __declspec(dllexport)
#else
#define ALGAE_API_DECL extern "C" __declspec(dllimport)
#endif

#define ALGAE_SDK_VERSION 1

struct ModHost
{
    // Info
    int Version;
    // Directories
    const wchar_t* GameDir;
    const wchar_t* AlgaeDir;
    const wchar_t* ModsDir;
    // Logging
    void (*Log)(const char* format, ...);
};

ALGAE_API_DECL int Algae_GetVersion();
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
