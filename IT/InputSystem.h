#pragma once
#include "System.h"

namespace ECS
{
    class Event;
}

namespace SYS
{


    class InputSystem : public ECS::System
    {
    public:
        void init();
        void input(float dt);

    private:
        std::bitset<8> mButtons;

        void InputListener(ECS::Event& event);
    };
}