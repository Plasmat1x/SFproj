#pragma once
#include <string>

#include "System.h"

namespace SYS
{
    class AnimationSystem : public ECS::System
    {
    public:
        void playAnimation(ECS::Entity entity, std::string);
    };
}


