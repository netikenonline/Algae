#pragma once
#include <AlgaeTools.h>
#include <Sexy/WidgetContainer.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t Widget_Resize = 0x46E1B0;
    }

    class Widget : public WidgetContainer
    {
    public:
        inline void Resize(int x, int y, int w, int h) { Algae::Call<void>(Addr::Widget_Resize, this, x, y, w, h); }
    };
}