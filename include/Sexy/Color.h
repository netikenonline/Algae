#pragma once
#include <AlgaeTools.h>

namespace Sexy
{
    // Just need to pass some bytes, no need for a Color API tbh (famous last words)
    struct Color
    {
        int mRed;
        int mGreen;
        int mBlue;
        int mAlpha;

        int ToInt() const { return (mAlpha << 24) | (mRed << 16) | (mGreen << 8) | (mBlue); }
    };
}
