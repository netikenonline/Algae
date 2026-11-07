#pragma once
#include <Sexy/Color.h>
#include <Sexy/Rect.h>
#include <AlgaeTools.h>


namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t Graphics_GetFont         = 0x455870;
        inline constexpr uintptr_t Graphics_SetFont         = 0x455880;
        inline constexpr uintptr_t Graphics_GetColor        = 0x4558B0;
        inline constexpr uintptr_t Graphics_SetColor        = 0x455890;
        inline constexpr uintptr_t Graphics_DrawImage       = 0x455D20;
        inline constexpr uintptr_t Graphics_DrawImage2      = 0x455E40;
        inline constexpr uintptr_t Graphics_DrawImage3      = 0x456260;
        inline constexpr uintptr_t Graphics_DrawImageF      = 0x4562E0;
        inline constexpr uintptr_t Graphics_DrawString      = 0x455CF0;
    }

    class Font;

    class Graphics
    {
    public:
        inline Font*    GetFont() { return Algae::Call<Font*>(Addr::Graphics_GetFont, this); }
        inline void     SetFont(Font* font) { Algae::Call<void>(Addr::Graphics_SetFont, this, font); }
        inline Color    GetColor() { return *Algae::Call<const Color*>(Addr::Graphics_GetColor, this); }
        inline void     SetColor(const Color& color) { Algae::Call<void>(Addr::Graphics_SetColor, this, &color); }
        inline void     DrawImage(Image* img, int x, int y) { Algae::Call<void>(Addr::Graphics_DrawImage, this, img, x, y); }
        inline void     DrawImage(Image* img, int x, int y, const Rect& srcRect) { Algae::Call<void>(Addr::Graphics_DrawImage2, this, img, x, y, &srcRect); }
        inline void     DrawImage(Image* img, const Rect& dstRect, const Rect& srcRect) { Algae::Call<void>(Addr::Graphics_DrawImage3, this, img, &dstRect, &srcRect); }
        inline void     DrawImageF(Image* img, float x, float y, const Rect& srcRect) { Algae::Call<void>(Addr::Graphics_DrawImageF, this, img, x, y, &srcRect); }
        inline void     DrawString(const std::string& str, int x, int y)
        {
            Algae::OldString oStr(str);
            Algae::Call<void>(Addr::Graphics_DrawString, this, &oStr, x, y);
        }
    };
}
