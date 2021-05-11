#pragma once
#include <set>

#include "Types.h"
namespace ECS
{
    class System
    {
    public:
        std::set<Entity> mEntities;
    };
}
