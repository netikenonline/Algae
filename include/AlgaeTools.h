#pragma once

namespace Algae
{
    // Helper function for calling functions based on address, this and args
    template<class Ret, class... Args>
    inline Ret Call(uintptr_t functionAddr, const void* thisPtr, Args... args)
    {
        return reinterpret_cast<Ret(__fastcall*)(const void*, void*, Args...)>(functionAddr)(thisPtr, nullptr, args...);
    }

    // Helper function for calling virtual functions based on vtable offset, this and args
    template<class Ret, class... Args>
    inline Ret CallVirtual(size_t addrOffset, const void* thisPtr, Args... args)
    {
        uintptr_t vTable = *reinterpret_cast<const uintptr_t*>(thisPtr);
        return Call<Ret>(*reinterpret_cast<const uintptr_t*>(vTable + addrOffset), thisPtr, args...);
    }

    // Internal helper function for calling pointers to the original function provided from MinHook.
    template<class Ret, class... Args>
    inline Ret CallInternal(uintptr_t functionAddr, const void* thisPtr, void* edx, Args... args)
    {
        return reinterpret_cast<Ret(__fastcall*)(const void*, void*, Args...)>(functionAddr)(thisPtr, edx, args...);
    }

    // Helper function for reading any data that we know the address of
    template<class T>
    inline T ReadGlobal(uintptr_t addr)
    {
        return *reinterpret_cast<T*>(addr);
    }

    // C++ has changed how std::strings work from 2005 to modern day, so this class
    // serves as an interop medium and allows strings to "just work" for modders.
    class OldString
    {
    public:
        OldString(std::string str) { SetInternal(str); }
        std::string ToString() const { return std::string(ToCStr()); };
        const char* ToCStr() const { return { (mRes < 16) ? mBuf : mPtr }; };
    private:
        // Handle our own value assignment from modern string to old string layout
        void SetInternal(std::string str)
        {
            mSize = str.size();
            if (mSize < 16)
            {
                mRes = 15;
                memcpy(mBuf, str.data(), mSize);
                mBuf[mSize] = '\0';
            }
            else
            {
                mRes = mSize;
                delete[] mPtr;
                mPtr = new char[mSize + 1];
                std::strncpy(mPtr, str.data(), mSize + 1);
                mPtr[mSize] = '\0';
            }
        }

        void* mAlloc = nullptr; // basically unused for us
        union { char mBuf[16]; char* mPtr = nullptr; };
        size_t mSize = 0;
        size_t mRes = 15;
    };
}