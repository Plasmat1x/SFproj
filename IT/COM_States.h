#pragma once
#include <map>
#include <unordered_map>
namespace COM
{
    enum class _state
    {
        IDLE,
        RUN,
        JUMP,
        FALL,
        CLIMB,
        ROLL
    };

    class States
    {
    public:
        _state cur_state = _state::IDLE;
        _state prev_state = _state::IDLE;

        std::unordered_map<std::string, bool> states = {
        { "direction", true },
        { "move_left", false },
        { "move_right", false },
        { "move_up", false },
        { "move_down", false },
        { "on_ground", true },
        { "was_ground", false },
        { "push_right", false },
        { "push_left", false },
        { "push_up", false },
        { "pushed_left", false },
        { "pushed_right", false },
        { "pushed_up", false },
        { "on_platform", false }
        };
    };
}