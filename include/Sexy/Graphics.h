#pragma once
#include <AlgaeTools.h>

namespace Sexy
{
    inline constexpr uintptr_t Graphics_GetFont     = 0x455870;
    inline constexpr uintptr_t Graphics_SetFont     = 0x455880;
    inline constexpr uintptr_t Graphics_GetColor    = 0x4558B0;
    inline constexpr uintptr_t Graphics_SetColor    = 0x455890;
    inline constexpr uintptr_t Graphics_DrawString  = 0x455CF0;

    class Graphics
    {
    public:
        inline Font*    GetFont() { return Algae::Call<Font*>(Graphics_GetFont, this); }
        inline void     SetFont(Font* font) { Algae::Call<void>(Graphics_SetFont, this, font); }
        inline Color    GetColor() { return *Algae::Call<const Color*>(Graphics_GetColor, this); }
        inline void     SetColor(const Color& color) { Algae::Call<void>(Graphics_SetColor, this, &color); }
        inline void     DrawString(const std::string& str, int x, int y) { Algae::Call<void>(Graphics_DrawString, this, &str, x, y); }
    };
}
