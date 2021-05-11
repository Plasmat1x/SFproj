#pragma once
#include <cmath>

#include "System.h"

namespace SYS
{
    class PhysicsSystem : public ECS::System
    {
    public:
        void update(float dt);
    };
}
