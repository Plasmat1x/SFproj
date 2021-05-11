#pragma once
#include <utility>
#include <bitset>

namespace ECS
{
    // ECS
    using Entity = uint64_t;
    const Entity MAX_ENTITIES = 5000;

    using COM_type = uint8_t;
    const COM_type MAX_COMS = 32;

    using Signature = std::bitset<MAX_COMS>;
}
