#pragma once


namespace Algae
{
    class AlgaeHelper
    {
    public:
        // Similar to Board::DrawWavyEffect but decoupled for general use
        inline static void DrawWavyEffect(Sexy::Graphics* g, Sexy::Image* img, int x, int y, float amplitude, int tickCount, bool is3DAccelerated)
        {
            int aWidth = Algae::ReadVar<int>(img, Sexy::Addr::Image_mWidth);
            int aRowY = y;
            int aSrcY = 0;
            for (int anAngle = 0; anAngle < 180; anAngle += 9, aRowY += 24, aSrcY += 24)
            {
                if ((unsigned int)(aRowY - y - 81) > 358)
                    continue;

                float aRad = (float)((double)((tickCount + anAngle) * 5) * (double)3.14159f / 180.0);
                float aWave = (float)sin(aRad) * amplitude;
                if (is3DAccelerated)
                {
                    g->DrawImageF(img, (float)x, aWave + (float)aRowY, Sexy::Rect{ 0, aSrcY, aWidth, 24 });
                }
                else
                {
                    g->DrawImage(img, x, (int)(aWave + (float)aRowY), Sexy::Rect{ 0, aSrcY, aWidth, 24 });
                }
            }
        }
    };
}
