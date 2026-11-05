#pragma once
#include <AlgaeTools.h>


namespace Sexy
{
    class Font;
    class Graphics;

    inline constexpr uintptr_t GameUtil_DrawStringWithOutline = 0x500BF0;

    class GameUtil
    {
    public:
        inline static void DrawStringWithOutline(Graphics* g, const std::string& str, int x, int y, Font* font, int color)
        {
            Algae::OldString oStr(str);
            reinterpret_cast<void(*)(Graphics*, const Algae::OldString&, int, int, Font*, int)>(GameUtil_DrawStringWithOutline)(g, oStr, x, y, font, color);
        }
    };
}
