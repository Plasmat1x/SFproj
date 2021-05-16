#pragma once
#include <cmath>

#include "System.h"
#include "COM_LIB.h"

namespace SYS
{
    class PhysicsSystem : public ECS::System
    {
    public:
        void update(float dt);

    private:
        sf::Vector2f oldPos;
        sf::Vector2f oldVel;

        float groundY;
        float lwallX;
        float rwallX;
        float ceil;
        float threshold;

        void moveR(float dt, COM::RigidBody& Velocity);
        void moveL(float dt, COM::RigidBody& Velocity);

        bool hasGround(sf::Vector2f oldpos, sf::Vector2f pos, sf::Vector2f speed);
        bool hasLwall();
        bool hasRwall();
        bool hasCeil();
    };
}
