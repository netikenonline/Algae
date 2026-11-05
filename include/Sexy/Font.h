#pragma once
#include <AlgaeTools.h>


namespace Sexy
{
    inline constexpr size_t Font_StringWidth_Offset = 0x1C;

    class Font
    {
    public:
        inline int StringWidth(const std::string& str)
        {
            Algae::OldString oStr(str);
            return Algae::CallVirtual<int>(Font_StringWidth_Offset, this, &oStr);
        }
    };
}