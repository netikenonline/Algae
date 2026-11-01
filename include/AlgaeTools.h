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
}