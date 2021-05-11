#pragma once
#include <SFML/Graphics.hpp>

#include "Coordinator.h"
#include "COM_LIB.h"
#include "Animation.h"

class Player
{
private:
    ECS::Entity entity;
    sf::Sprite sprite;
    sf::Texture texture;
    Animation anim;
    AnimationManager* anim_mgr;
    sf::View* view;
    sf::RectangleShape rect;

public:

    ECS::Entity getEntity();

    void Init(sf::Vector2f pos);

    void SetView(sf::View* view);
    void SetRect(sf::RectangleShape rect);
    void SetTexture(sf::Texture texture);
};

