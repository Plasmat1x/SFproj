#pragma once
#include "System.h"

namespace SYS
{
    class InputSystem : public ECS::System
    {
    public:
        void input(float dt);
    };
}