#pragma once
#include <SFML/Graphics.hpp>

#include "System.h"

namespace SYS
{
    class RenderSystem : public ECS::System
    {
    public:
        bool dir = false;
        void updateAnim();
        void draw(sf::RenderWindow& window);
    };
}

