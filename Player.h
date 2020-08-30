#pragma once
#include "Entity.h"

class Player :
    public Entity
{
public:
    Player(std::string imageName, sf::Vector2f position, sf::Vector2i size, sf::IntRect textureRect, float scale = 1.0f);
    ~Player();
};

