#pragma once
#include <unordered_map>
#include <vector>
#include <AlgaeSDK.h>


std::unordered_map<uintptr_t, uintptr_t> algaeFuncStore;
std::unordered_map<uintptr_t, uintptr_t> algaeHookOverrides;
std::unordered_map<uintptr_t, std::vector<uintptr_t>> algaePreHooks;
std::unordered_map<uintptr_t, std::vector<uintptr_t>> algaePostHooks;

template<class T, class... Args>
void Detour_RunInternal(uintptr_t funcPtr, T self, void* edx, Args... args);

// Detour macros for up to 10 variables (I apologize in advance)
// (I couldn't think of anything better atm, aiming for max C++ compat)

#define DETOUR_FUNC_0(type, addr) \
static void __fastcall Detour_##addr(type* self, void* edx) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx); }

#define DETOUR_FUNC_1(type, addr, aType0, arg0) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0); }

#define DETOUR_FUNC_2(type, addr, aType0, arg0, aType1, arg1) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1); }

#define DETOUR_FUNC_3(type, addr, aType0, arg0, aType1, arg1, aType2, arg2) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2; }

#define DETOUR_FUNC_4(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3); }

#define DETOUR_FUNC_5(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3, \
    aType4, arg4) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3, \
    aType4 arg4 ) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3, arg4); }

#define DETOUR_FUNC_6(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3, \
    aType4, arg4, aType5, arg5) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3, \
    aType4 arg4, aType5 arg5 ) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3, arg4, arg5); }

#define DETOUR_FUNC_7(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3, \
    aType4, arg4, aType5, arg5, aType6, arg6) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3, \
    aType4 arg4, aType5 arg5, aType6 arg6 ) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3, arg4, arg5, arg6); }

#define DETOUR_FUNC_8(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3, \
    aType4, arg4, aType5, arg5, aType6, arg6, aType7, arg7) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3, \
    aType4 arg4, aType5 arg5, aType6 arg6, aType7 arg7 ) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7); }

#define DETOUR_FUNC_9(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3, \
    aType4, arg4, aType5, arg5, aType6, arg6, aType7, arg7, aType8, arg8) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3, \
    aType4 arg4, aType5 arg5, aType6 arg6, aType7 arg7, aType8 arg8 ) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); }

#define DETOUR_FUNC_10(type, addr, aType0, arg0, aType1, arg1, aType2, arg2, aType3, arg3, \
    aType4, arg4, aType5, arg5, aType6, arg6, aType7, arg7, aType8, arg8, aType9, arg9) \
static void __fastcall Detour_##addr(type* self, void* edx, aType0 arg0, aType1 arg1, aType2 arg2, aType3 arg3, \
    aType4 arg4, aType5 arg5, aType6 arg6, aType7 arg7, aType8 arg8, aType9 arg9 ) { \
    Detour_RunInternal(Sexy::Addr::addr, self, edx, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); }

// https://stackoverflow.com/a/11763277 thanku
#define DETOUR_EXPAND(x) x
#define DETOUR_GETMACRO(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, name, ...) name
#define DETOUR_FUNC(type, target, ...) DETOUR_EXPAND( DETOUR_GETMACRO(__VA_ARGS__, DETOUR_FUNC_10, ERROR, \
DETOUR_FUNC_9, ERROR, DETOUR_FUNC_8, ERROR, DETOUR_FUNC_7, ERROR, DETOUR_FUNC_6, ERROR, DETOUR_FUNC_5, ERROR,  \
DETOUR_FUNC_4, ERROR, DETOUR_FUNC_3, ERROR, DETOUR_FUNC_2, ERROR, DETOUR_FUNC_1, DETOUR_FUNC_0)(type, target, __VA_ARGS__) )

DETOUR_FUNC(Sexy::Board, Board_KeyDown, int, key)
DETOUR_FUNC(Sexy::MainScreen, MainScreen_AddedToManager, Sexy::WidgetManager*, w)
DETOUR_FUNC(Sexy::MainScreen, MainScreen_RemovedFromManager, Sexy::WidgetManager*, w)
DETOUR_FUNC(Sexy::MainScreen, MainScreen_OrderInManagerChanged)
DETOUR_FUNC(Sexy::TitleScreen, TitleScreen_Draw, Sexy::Graphics*, g)

bool Algae_InstallEventHooks()
{
    bool result = true;
    void* trampoline = nullptr;

#define DETOUR_REGISTER(target) \
    result &= Algae_CreateHook(Sexy::Addr::##target, &Detour_##target, &trampoline); \
    algaeFuncStore[Sexy::Addr::##target] = reinterpret_cast<uintptr_t>(trampoline);

    DETOUR_REGISTER(TitleScreen_Draw)
    DETOUR_REGISTER(MainScreen_AddedToManager)
    DETOUR_REGISTER(MainScreen_RemovedFromManager)
    DETOUR_REGISTER(MainScreen_OrderInManagerChanged)
    DETOUR_REGISTER(Board_KeyDown)

    return result;
}
