#pragma once
#include <AlgaeTools.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t GameUtil_DrawStringWithOutline   = 0x500BF0;
        inline constexpr uintptr_t GameUtil_MakeDialogButton        = 0x506820;
    }

    class ButtonListener;
    class DialogButton;
    class Font;
    class Image;
    class Graphics;

    class GameUtil
    {
    public:
        inline static void DrawStringWithOutline(Graphics* g, const std::string& str, int x, int y, Font* font, int color)
        {
            Algae::OldString oStr(str);
            reinterpret_cast<void(*)(Graphics*, const Algae::OldString&, int, int, Font*, int)>(Addr::GameUtil_DrawStringWithOutline)(g, oStr, x, y, font, color);
        }

        inline static DialogButton* MakeDialogButton(int id, ButtonListener* listener, const std::string& text, Image* image)
        {
            Algae::OldString oText(text);
            return reinterpret_cast<DialogButton*(*)(int, ButtonListener*, const Algae::OldString&, Image*)>(Addr::GameUtil_MakeDialogButton)(id, listener, oText, image);
        }
    };
}
