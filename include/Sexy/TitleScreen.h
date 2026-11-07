#pragma once
#include <AlgaeTools.h>
#include <Sexy/ButtonListener.h>
#include <Sexy/Widget.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t TitleScreen_Draw = 0x52D490;
        inline constexpr uintptr_t TitleScreen_ButtonListener_Offset = 0x88;
    }

    class TitleScreen : public Widget, public ButtonListener
    {
    public:
        inline ButtonListener* AsButtonListener() { return reinterpret_cast<Sexy::ButtonListener*>(this + Addr::TitleScreen_ButtonListener_Offset); }
    };
}