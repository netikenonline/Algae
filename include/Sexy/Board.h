#pragma once
#include <AlgaeTools.h>

class GameObject;

namespace Sexy
{
    inline constexpr uintptr_t Board_KeyDown = 0x540650;
    inline constexpr uintptr_t Board_DropGuppy = 0x546D70;

    class Board
    {
    public:
        inline GameObject* DropGuppy() { return Algae::Call<GameObject*>(Board_DropGuppy, this); }
    };
}
