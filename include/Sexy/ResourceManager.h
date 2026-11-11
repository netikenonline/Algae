#pragma once
#include <map>
#include <string>
#include <vector>
#include <Windows.h>
#include <AlgaeTools.h>

namespace Sexy
{
    namespace Addr
    {
        inline constexpr uintptr_t ResourceManager_DoLoadImage = 0x418D80;
        inline constexpr uintptr_t ResourceManager_DoLoadSound = 0x419320;
        inline constexpr uintptr_t ResourceManager_DoLoadFont  = 0x419480;
    }

    // A shit ton of declarations to get our resource hacking voodoo to work (good byte offsets are vital to get this to work)
    // Tons of this stuff pulled from (seemingly) official sources: https://github.com/sureandrew/SexyAppFramework

    // TODO organize and move this stuff into better places?

    enum ResType
    {
        ResType_Image,
        ResType_Sound,
        ResType_Font,
    };

    enum AnimType
    {
        AnimType_None,
        AnimType_Once,
        AnimType_PingPong,
        AnimType_Loop
    };

    //typedef std::map<std::wstring, std::wstring> XMLParamMap;
    struct XMLParamMap // std::map is not temporally interoperable AFAIK, we should build a bridge at some point
    {
        void* mAlloc;
        void* mHead;
        size_t mSize;
    };

    class Font;
    class Image;
    class DDImage;
    class MemoryImage;

    class SharedImage
    {
    public:
        DDImage* mImage;
        int mRefCount;
    };

    class SharedImageRef
    {
    public:
        SharedImage* mSharedImage;
        MemoryImage* mUnsharedImage;
        bool mOwnsUnshared;
    };

    struct AnimInfo
    {
        AnimType            mAnimType;
        int                 mFrameDelay;
        int                 mNumCels;
        std::vector<int>    mPerFrameDelay;
        std::vector<int>    mFrameMap;
        int                 mTotalAnimTime;
    };

    struct BaseRes
    {
        ResType mType;
        std::string mId;
        std::string mResGroup;
        std::string mPath;
        XMLParamMap mXMLAttributes;
        bool mFromProgram;
    };

    struct ImageRes : public BaseRes
    {
        SharedImageRef mImage;
        std::string mAlphaImage;
        std::string mAlphaGridImage;
        std::string mVariant;
        bool mAutoFindAlpha;
        bool mPalletize;
        bool mA4R4G4B4;
        bool mA8R8G8B8;
        bool mDDSurface;
        bool mPurgeBits;
        bool mMinimizeSubdivisions;
        int mRows;
        int mCols;
        DWORD mAlphaColor;
        AnimInfo mAnimInfo;
    };

    struct SoundRes : public BaseRes
    {
        int mSoundId;
        double mVolume;
        int mPanning;
    };

    struct FontRes : public BaseRes
    {
        Font* mFont;
        Image* mImage;
        std::string mImagePath;
        std::string mTags;
        bool mSysFont;
        bool mBold;
        bool mItalic;
        bool mUnderline;
        bool mShadow;
        int mSize;
    };

    class ResourceManager
    {
    public:
        inline bool DoLoadImage(ImageRes* imageRes) { return Algae::Call<bool>(Addr::ResourceManager_DoLoadImage, this, imageRes); }
        inline bool DoLoadSound(ImageRes* soundRes) { return Algae::Call<bool>(Addr::ResourceManager_DoLoadSound, this, soundRes); }
        inline bool DoLoadFont(ImageRes* fontRes) { return Algae::Call<bool>(Addr::ResourceManager_DoLoadFont, this, fontRes); }
    };
}