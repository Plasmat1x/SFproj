#pragma once
#include <SFML/Graphics.hpp>

namespace COM
{
    class RigidBody
    {
    public:
        sf::Vector2f velocity;

        float _ACCELERATION;
        float _MAXSPEED;
    };
}

