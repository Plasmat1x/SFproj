#include <iostream>

#include "Player.h"
#include "COM_LIB.h"


extern ECS::Coordinator gCoordinator;

void Player::moveL(float dt)
{
    if (Velocity->velocity.x > 0.0f) { Velocity->velocity.x = std::fmin(Velocity->velocity.x - Velocity->_ACCELERATION * dt, 0.0f); }
    else { Velocity->velocity.x = std::fmax(Velocity->velocity.x - Velocity->_ACCELERATION * dt, -Velocity->_MAXSPEED); }
}

void Player::moveR(float dt)
{
    if (Velocity->velocity.x < 0.0f) { Velocity->velocity.x = std::fmax(Velocity->velocity.x + Velocity->_ACCELERATION * dt, 0.0f); }
    else { Velocity->velocity.x = std::fmin(Velocity->velocity.x + Velocity->_ACCELERATION * dt, Velocity->_MAXSPEED); }
}

void Player::jump(float dt)
{
    Velocity->velocity.y = -Velocity->_ACCELERATION * 0.5f;
    state_com->states.at("on_ground") = false;//tmp
}

ECS::Entity Player::getEntity()
{
    return this->entity;
}

void Player::Init(sf::Vector2f pos)
{
    mass = 3.0f;

    sprite.setTextureRect(sf::IntRect(0, 0, 43, 60));
    sprite.setOrigin(44 * 0.5f, 60 * 0.5f);

    this->entity = gCoordinator.CreateEntity();
    gCoordinator.AddComponent<COM::Transform>(entity, { pos, sf::Vector2f(1,1), 0 });
    gCoordinator.AddComponent<COM::RigidBody>(entity, { sf::Vector2f(0,0), 500.0f, 100.0f });
    gCoordinator.AddComponent<COM::Sprite>(entity, { sprite });
    gCoordinator.AddComponent<COM::Input>(entity, { std::vector<sf::Keyboard::Key>{sf::Keyboard::W,sf::Keyboard::A,sf::Keyboard::S,sf::Keyboard::D} });
    gCoordinator.AddComponent<COM::View>(entity, { view });
    gCoordinator.AddComponent<COM::Hitbox>(entity, { sf::Vector2f(43,60), sf::Vector2f(0.0f, 22.0f), rect , true });
    gCoordinator.GetComponent<COM::Hitbox>(entity).initHitbox();
    /*/
    gCoordinator.AddComponent<COM::States>(entity, { COM::_state::IDLE, COM::_state::IDLE, 
        {//map
            {"direction", true},
            {"move_left", false},
            {"move_right", false},
            {"move_up", false},
            {"move_down", false},
            {"on_ground", true},
            {"was_ground", false},
            {"push_right", false},
            {"push_left", false},
            {"push_up", false},
            {"pushed_left", false},
            {"pushed_right", false},
            {"pushed_up", false},
            {"on_platform", false}
        } 
        });
    //*/
    gCoordinator.AddComponent<COM::States>(entity, {});
    gCoordinator.AddComponent<COM::Anim>(entity, { &anim, anim_mgr, 0.1f });

    anim.init(0.1f);

    anim_com = &gCoordinator.GetComponent<COM::Anim>(entity);
    state_com = &gCoordinator.GetComponent<COM::States>(entity);
    sprite_com = &gCoordinator.GetComponent<COM::Sprite>(entity);
    Velocity = &gCoordinator.GetComponent<COM::RigidBody>(entity);

    spriteptr = &gCoordinator.GetComponent<COM::Sprite>(entity).sprite;
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

    switch (state_com->cur_state)
    {
    case COM::_state::IDLE:
    {
        if (state_com->states.at("direction")) { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("idle")); }
        else { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("idlef")); }

        if (state_com->states.at("move_left") != state_com->states.at("move_right"))
        {
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::RUN;
            break;
        }

        if (state_com->states.at("move_up"))
        {
            jump(dt);
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::JUMP;
            break;
        }
        if (state_com->states.at("move_down"))
        {

        }

        //if (!state_com->states.at("on_ground") && Velocity->velocity.y > 0.0f)
        if (!state_com->states.at("on_ground"))
        {
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::FALL;
            break;
        }

        if (Velocity->velocity.x > 0.0f)
        {
            Velocity->velocity.x = int(std::fmax(Velocity->velocity.x - std::abs(Velocity->velocity.x * dt * mass), 0.0f));
        }
        else if (Velocity->velocity.x < 0.0f)
        {
            Velocity->velocity.x = int(std::fmin(Velocity->velocity.x + std::abs(Velocity->velocity.x * dt * mass), 0.0f));
        }

        break;
    }
    case COM::_state::RUN:
    {
        if (state_com->states.at("direction")) { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("run")); }
        else { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("runf"));}

        if (!state_com->states.at("move_left") && !state_com->states.at("move_right"))
        {
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::IDLE;
            break;
        }

        if (state_com->states.at("move_right"))
        {
            moveR(dt);
        }
        if (state_com->states.at("move_left"))
        {
            moveL(dt);
        }
        if (state_com->states.at("move_up"))
        {
            jump(dt);
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::JUMP;
            break;
        }
        if (state_com->states.at("move_down"))
        {
        }
        if (!state_com->states.at("on_ground"))
        {
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::FALL;
            break;
        }



        break;
    }
    case COM::_state::JUMP:
    {
        if (state_com->states.at("direction")) { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("jump")); }
        else { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("jumpf")); }

        Velocity->velocity.y += std::fmax(1.0f * dt, 10.0f);

        if (state_com->states.at("move_right"))
        {    
            moveR(dt);
        }
        if (state_com->states.at("move_left"))
        {
            moveL(dt);
        }
        if (!state_com->states.at("move_left") && !state_com->states.at("move_right"))
        {
            Velocity->velocity.x = 0.0f;
        }
        if (!state_com->states.at("move_up") && Velocity->velocity.y < 0)
        {
            Velocity->velocity.y = std::fmin(Velocity->velocity.y, 1.0f);
        }
        if (Velocity->velocity.y > 0.0f && !state_com->states.at("on_ground"))
        {
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::FALL;
            break;
        }
        if (state_com->states.at("on_ground"))
        {
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::IDLE;
            break;
        }


        break;
    }
    case COM::_state::FALL:
    {
        if (state_com->states.at("direction")) { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("fall")); }
        else { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("fallf")); }

        Velocity->velocity.y += std::fmax(5.0f * dt, 20.0f);

        if (state_com->states.at("move_right"))
        {
            moveR(dt);
        }
        if (state_com->states.at("move_left"))
        {
            moveL(dt);
        }
        if (!state_com->states.at("move_left") && !state_com->states.at("move_right"))
        {
            Velocity->velocity.x = 0.0f;
        }
        if (!state_com->states.at("move_up") && Velocity->velocity.y < 0)
        {
            Velocity->velocity.y = std::fmin(Velocity->velocity.y, 5.0f);
        }
        if (state_com->states.at("on_ground"))
        {
            Velocity->velocity.y = 0.0f;
            state_com->prev_state = state_com->cur_state;
            state_com->cur_state = COM::_state::IDLE;
            break;
        }
        break;
    }
    case COM::_state::CLIMB: // на допил
    {
        if (state_com->states.at("direction")) { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("clim")); }
        else { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("climf")); }

        break;
    }
    case COM::_state::ROLL: // на допил
    {
        if (state_com->states.at("direction")) { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("roll")); }
        else { anim_com->anim->play(spriteptr, anim_com->mgr->getAnimation("rollf")); }

        if (state_com->states.at("move_right"))
        {
            moveR(dt);
        }
        if (state_com->states.at("move_left"))
        {
            moveL(dt);
        }
        break;
    }
    default: break;
    }
}
