#pragma once
#include <list>
#include <map>
#include <string>


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

    // Helper function for reading the variable of an object given its address and variable offset
    template<class T>
    inline T ReadVar(void* obj, uintptr_t offset)
    {
        return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(obj) + offset);
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

    // TODO build bridge between old and new std::list! Layout has changed over the years (rip me)
    // MSVC 2005: 12 bytes (4 (void* mAlloc), 4 (void* mHead), 4 (uint32_t mSize))
    // MSVC 2022: 16 bytes (4 (void* mHead), 4 (uint32_t mSize), 4 (void* mProxy), 4 (void* mAlloc))

    // C++ has changed how std::lists work from 2005 to modern day, so this class is made to
    // convert between the two versions and "just work" for modders.
    template<class T>
    class OldList
    {
    public:
        std::list<T> ToList() const
        {
            /* TODO convert old to new? */
        };
        void FromList(std::list<T>)
        {
            /* TODO update from new to old? */
        };
    private:
        void* mAlloc = nullptr;
        void* mHead = nullptr;
        size_t mSize = 0;
    };

    // TODO build bridge between old and new std::map! Layout has changed over the years
    // MSVC 2005: 12 bytes (4 (void* mHead), 4 (uint32_t mSize), 4 (void* mAlloc))
    // MSVC 2022: 8 bytes (4 (void* mHead), 4 (uint32_t mSize))

    // C++ has changed how std::maps work from 2005 to modern day, so this class is made to
    // convert between the two versions and "just work" for modders.
    template<class T>
    class OldMap
    {
    public:
        std::map<T> ToMap() const
        {
            /* TODO convert old to new? */
        };
        void FromMap(std::map<T>)
        {
            /* TODO update from new to old? */
        };
    private:
        void* mHead = nullptr;
        size_t mSize = 0;
        void* mAlloc = nullptr;
    };
}