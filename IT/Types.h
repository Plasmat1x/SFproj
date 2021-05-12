#pragma once
#include <utility>
#include <bitset>
#include <functional>

namespace ECS
{
    // Source: https://gist.github.com/Lee-R/3839813
    constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
    {
        return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
    }

    constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count)
    {
        return fnv1a_32(s, count);
    }


    // ECS
    using Entity = uint64_t;
    const Entity MAX_ENTITIES = 5000;

    using COM_type = uint8_t;
    const COM_type MAX_COMS = 32;

    using Signature = std::bitset<MAX_COMS>;

    enum class InputButtons
    {
        W,A,S,D,Q,E
    };

    using EventId = uint32_t;
    using ParamId = uint32_t;

#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

    namespace Events
    {
        const EventId INPUT = "Events::INPUT"_hash;
    }

    namespace Events::Input
    {
        const ParamId INPUT = "Events::Input::INPUT"_hash;
    }
}
