#pragma once
#include <AlgaeTools.h>
#include <Sexy/ButtonListener.h>
#include <Sexy/Widget.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t MainScreen_AddedToManager = 0x51EF10;
        inline constexpr uintptr_t MainScreen_RemovedFromManager = 0x517660;
        inline constexpr uintptr_t MainScreen_OrderInManagerChanged = 0x517720;
        inline constexpr uintptr_t MainScreen_ButtonListener_Offset = 0x88;
    }

    class MainScreen : public Widget, public ButtonListener
    {
    public:
        inline ButtonListener* AsButtonListener() { return reinterpret_cast<Sexy::ButtonListener*>(this + Addr::MainScreen_ButtonListener_Offset); }
    };
}