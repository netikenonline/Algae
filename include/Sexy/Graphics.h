#pragma once
#include <Sexy/Color.h>
#include <AlgaeTools.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t Graphics_GetFont     = 0x455870;
        inline constexpr uintptr_t Graphics_SetFont     = 0x455880;
        inline constexpr uintptr_t Graphics_GetColor    = 0x4558B0;
        inline constexpr uintptr_t Graphics_SetColor    = 0x455890;
        inline constexpr uintptr_t Graphics_DrawString  = 0x455CF0;
    }

    class Font;

    class Graphics
    {
    public:
        inline Font*    GetFont() { return Algae::Call<Font*>(Addr::Graphics_GetFont, this); }
        inline void     SetFont(Font* font) { Algae::Call<void>(Addr::Graphics_SetFont, this, font); }
        inline Color    GetColor() { return *Algae::Call<const Color*>(Addr::Graphics_GetColor, this); }
        inline void     SetColor(const Color& color) { Algae::Call<void>(Addr::Graphics_SetColor, this, &color); }
        inline void     DrawString(const std::string& str, int x, int y)
        {
            Algae::OldString oStr(str);
            Algae::Call<void>(Addr::Graphics_DrawString, this, &oStr, x, y);
        }
    };
}
