#pragma once
#include <AlgaeTools.h>
#include <Sexy/ButtonListener.h>
#include <Sexy/Widget.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t TitleScreen_Draw = 0x52D490;
    }

    class TitleScreen : public Widget, public ButtonListener
    {
    };
}