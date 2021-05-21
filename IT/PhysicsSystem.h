#pragma once
#include <cmath>

#include "System.h"
#include "COM_LIB.h"
#include "Level.h"

namespace SYS
{
    class PhysicsSystem : public ECS::System
    {
    public:
        void init(Level* level);
        void update(float dt);

    private:
        sf::Vector2f oldPos;
        sf::Vector2f oldVel;

        Level* level;

        //float groundY = 0;

        void moveR(float dt, COM::RigidBody& Velocity);
        void moveL(float dt, COM::RigidBody& Velocity);
        void friction(float dt, COM::RigidBody& Velocity);

        // test physics
        bool hasGround(const sf::Vector2f& oldPos,
            const COM::Hitbox& hb, const COM::RigidBody& rb,
            float& groundY);

        bool hasCeil(const sf::Vector2f& oldPos,
            const COM::Hitbox& hb,
            const COM::RigidBody& rb,
            float& ceilY);

        bool hasLW(const sf::Vector2f& oldPos,
            const COM::Hitbox& hb,
            const COM::RigidBody& rb,
            float& wallL);

        bool hasRW(const sf::Vector2f& oldPos,
            const COM::Hitbox& hb,
            const COM::RigidBody& rb,
            float& wallR);

        //tools
        float clamp01(float value);
        sf::Vector2f lerpvec2(sf::Vector2f a, sf::Vector2f b, float t);

    };
}
