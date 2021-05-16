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


    COM::States* state_com;
    COM::Anim* anim_com;
    COM::Sprite* sprite_com;
    COM::RigidBody* Velocity;
    sf::Sprite* spriteptr;

    float mass;

public:

    ECS::Entity getEntity();

    void Init(sf::Vector2f pos);

    void SetView(sf::View* view);
    void SetRect(sf::RectangleShape rect);
    void SetTexture(sf::Texture texture);
    void SetAnimation(Animation animation);
    void SetAnimMgr(AnimationManager* mgr);

    void update(float dt);

    void input(float dt);
};

