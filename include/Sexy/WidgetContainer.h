#pragma once
#include <list>
#include <AlgaeTools.h>

namespace Sexy
{
    namespace Addr
    {
        // Functions

        inline constexpr uintptr_t WidgetContainer_AddWidget        = 0x46B640;
        inline constexpr uintptr_t WidgetContainer_RemoveWidget     = 0x46B760;
        inline constexpr uintptr_t WidgetContainer_PutInFront       = 0x46BF00;

        // Variables

        inline constexpr uintptr_t WidgetContainer_mWidgets         = 0x04; // std::list<Widget*>
        inline constexpr uintptr_t WidgetContainer_mWidgetManager   = 0x10; // WidgetManager*
        inline constexpr uintptr_t WidgetContainer_mX               = 0x30; // int
        inline constexpr uintptr_t WidgetContainer_mY               = 0x34; // int
        inline constexpr uintptr_t WidgetContainer_mWidth           = 0x38; // int
        inline constexpr uintptr_t WidgetContainer_mHeight          = 0x3C; // int
    }

    class Widget;
    typedef std::list<Widget*> WidgetList;

    class WidgetContainer
    {
    public:
        inline void     AddWidget(Widget* widget) { Algae::Call<void>(Addr::WidgetContainer_AddWidget, this, widget); }
        inline void     RemoveWidget(Widget* widget) { Algae::Call<void>(Addr::WidgetContainer_RemoveWidget, this, widget); }
        inline void     PutInFront(Widget* widget, Widget* refWidget) { Algae::Call<void>(Addr::WidgetContainer_PutInFront, this, widget, refWidget); }
    };
}