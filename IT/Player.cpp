#include <iostream>

#include "Player.h"
#include "COM_LIB.h"


extern ECS::Coordinator gCoordinator;

ECS::Entity Player::getEntity()
{
    return this->entity;
}

void Player::Init(sf::Vector2f pos)
{
    sprite.setTextureRect(sf::IntRect(0, 0, 43, 60));
    sprite.setOrigin(44 * 0.5f, 60 * 0.5f);

    this->entity = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::Transform>(entity, { pos, sf::Vector2f(1,1), 0 });
    gCoordinator.AddComponent<COM::RigidBody>(entity, { sf::Vector2f(0,0), 500.0f, 150.0f });
    gCoordinator.AddComponent<COM::Sprite>(entity, { sprite });
    gCoordinator.AddComponent<COM::Input>(entity, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });
    gCoordinator.AddComponent<COM::View>(entity, { view });
    gCoordinator.AddComponent<COM::Hitbox>(entity, { sf::Vector2f(43,60), sf::Vector2f(0.0f, 22.0f), rect , true });
    gCoordinator.GetComponent<COM::Hitbox>(entity).initHitbox();
    gCoordinator.AddComponent<COM::States>(entity, { 
        {//map
            {"direction", true},
            {"idle", false},
            {"run", false},
            {"jump", false},
            {"fall", false},
            {"clim", false},
            {"roll", false},
            {"move_left", false},
            {"move_right", false},
            {"move_up", false},
            {"move_down", false},
            {"on_ground", false}
        } 
        });
    gCoordinator.AddComponent<COM::Anim>(entity, { &anim, anim_mgr, 0.1f });
}

void Player::SetView(sf::View* view)
{
    this->view = view;
}

void Player::SetRect(sf::RectangleShape rect)
{
    this->rect = rect;
}

void Player::SetTexture(sf::Texture texture)
{
    this->texture = texture;
    this->sprite.setTexture(this->texture);
}

void Player::SetAnimation(Animation animation)
{
    this->anim = animation;
    anim.init(0.1f);
}

void Player::SetAnimMgr(AnimationManager* mgr)
{
    this->anim_mgr = mgr;
}

void Player::update(float dt)
{

}

void Player::input(float dt)
{
}
