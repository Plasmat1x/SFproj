#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Level.h"
#include "COM_LIB.h"

namespace SYS
{
    //extern ECS::Coordinator gCoordinator;
    extern ECS::System System;

    /// <summary>
    /// ECS systems must be inheritate from ECS::System located in ECS.h
    /// </summary>

    //example system
    class PhysicsSystem : public ECS::System
    {
    public:
        void update(float dt, Level level)
        {
            for (auto const& entity : mEntities)
            {
                auto& Position = gCoordinator.GetComponent<COM::c_position>(entity);
                auto& Velocity = gCoordinator.GetComponent<COM::c_velocity>(entity);
                auto& Rect = gCoordinator.GetComponent<COM::c_hitbox>(entity);
                auto& State = gCoordinator.GetComponent<COM::c_state>(entity);
                //*/
                float mass = 3.0f;

                if (Velocity.y > 0.0f)
                {
                    Velocity.y = int(std::fmax(Velocity.y - std::abs(Velocity.y * dt * mass), 0.0f));
                }
                else if (Velocity.y < 0.0f)
                {
                    Velocity.y = int(std::fmin(Velocity.y + std::abs(Velocity.y * dt * mass), 0.0f));
                }

                if (Velocity.x > 0.0f)
                {
                    Velocity.x = int(std::fmax(Velocity.x - std::abs(Velocity.x * dt * mass), 0.0f));
                }
                else if (Velocity.x < 0.0f)
                {
                    Velocity.x = int(std::fmin(Velocity.x + std::abs(Velocity.x * dt * mass), 0.0f));
                }
                //*/
                Position.x += Velocity.x * dt;
                Position.y += Velocity.y * dt;

                Rect.update(Position.x, Position.y);
            }
        }
    };

    class RenderSystem : public ECS::System
    {
    public:
        void draw(sf::RenderWindow& window)
        {
            for (auto const& entity : mEntities)
            {
                auto& Sprite = gCoordinator.GetComponent<COM::c_sprite>(entity);
                auto& Position = gCoordinator.GetComponent<COM::c_position>(entity);
                auto& Rect = gCoordinator.GetComponent<COM::c_hitbox>(entity);

                Sprite.sprite.setPosition(Position.x, Position.y);
             
                window.draw(Sprite.sprite);

                if (Rect.draw)
                {
                    window.draw(Rect.shape);
                }

            }
        }
    };

    class AnimationSystem : public ECS::System
    {
    public:
        void update()
        {
            for (auto const& entity : mEntities)
            {
                auto& Anim = gCoordinator.GetComponent<COM::c_animation>(entity);
                auto& State = gCoordinator.GetComponent<COM::c_state>(entity);

                for (auto const& [name, s] : State.anim_states)
                {
                    if (s)
                    {
                        Anim._animation.play(Anim.sprite, gCoordinator.GetComponent<COM::c_animation>(entity).anim_mgr.getAnimation(name));
                    }           
                }
            }
        }

    };

    class CameraSystem : public ECS::System
    {
    public: 
        void update()
        {
            for (auto const& entity : mEntities)
            {
                auto& View = gCoordinator.GetComponent<COM::c_view>(entity);
                auto& Position = gCoordinator.GetComponent<COM::c_position>(entity);

                View.view->setCenter(Position.x, Position.y);
            }
        }
    };

    class InputSystem : public ECS::System
    {
    private:
        std::bitset<8> mButtons;
        void InputListener(ECS::Event& event)
        {
            mButtons = event.GetParam<std::bitset<8>>(ECS::Events::Window::Input::INPUT);
        }

    public:
        void init()
        {
            gCoordinator.AddEventListener(METHOD_LISTENER(ECS::Events::Window::INPUT, InputSystem::InputListener));
        }

        void update(float dt)
        {
            for (auto const& entity : mEntities)
            {
                auto& Input = gCoordinator.GetComponent<COM::c_input>(entity);
                auto& Velocity = gCoordinator.GetComponent<COM::c_velocity>(entity);
                auto& State = gCoordinator.GetComponent<COM::c_state>(entity);
                auto& Animation = gCoordinator.GetComponent<COM::c_animation>(entity);
                //*/
                for (auto& key : Input.KeyList)
                {
                    /*/
                    if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::W)
                    {
                        if (Velocity.y > 0.0f) { Velocity.y = std::fmin(Velocity.y - Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.y = std::fmax(Velocity.y - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
                        Animation._animation.play(Animation.sprite, Animation.anim_mgr.getAnimation("run"));
                    }
                    else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::A)
                    {
                        if (Velocity.x > 0.0f) { Velocity.x = std::fmin(Velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.x = std::fmax(Velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
                        Animation._animation.play(Animation.sprite, Animation.anim_mgr.getAnimation("runf"));
                    }
                    else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::S)
                    {
                        if (Velocity.y < 0.0f) { Velocity.y = std::fmax(Velocity.y + Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.y = std::fmin(Velocity.y + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
                        Animation._animation.play(Animation.sprite, Animation.anim_mgr.getAnimation("run"));
                    }
                    else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::D)
                    {
                        if (Velocity.x < 0.0f) { Velocity.x = std::fmax(Velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.x = std::fmin(Velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
                        Animation._animation.play(Animation.sprite, Animation.anim_mgr.getAnimation("run"));
                    }
                    else
                    {
                        Animation._animation.play(Animation.sprite, Animation.anim_mgr.getAnimation("idle"));
                    }
                    //*/
                    if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::W)
                    {
                        State.states["idle"] = false;
                        State.states["run"] = true;
                    }
                    else
                    {
                        State.states["run"] = false;
                        State.states["idle"] = true;
                    }

                }
                //*/

            }
        }
    };
}

/*
Control
                float mass = 3.0f;

                if (Velocity.y > 0.0f)
                {
                    Velocity.y = int(std::fmax(Velocity.y - std::abs(Velocity.y * dt * mass), 0.0f));
                }
                else if (Velocity.y < 0.0f)
                {
                    Velocity.y = int(std::fmin(Velocity.y + std::abs(Velocity.y * dt * mass), 0.0f));
                }

                if (Velocity.x > 0.0f)
                {
                    Velocity.x = int(std::fmax(Velocity.x - std::abs(Velocity.x * dt * mass), 0.0f));
                }
                else if (Velocity.x < 0.0f)
                {
                    Velocity.x = int(std::fmin(Velocity.x + std::abs(Velocity.x * dt * mass), 0.0f));
                }


                for (auto& key : Input.KeyList)
                {

                    if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::W)
                    {
                        if(Velocity.y > 0.0f) { Velocity.y = std::fmin(Velocity.y - Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.y = std::fmax(Velocity.y - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
                    }
                    if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::A)
                    {
                        if(Velocity.x > 0.0f) { Velocity.x = std::fmin(Velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.x = std::fmax(Velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
                    }
                    if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::S)
                    {
                        if(Velocity.y < 0.0f) { Velocity.y = std::fmax(Velocity.y + Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.y = std::fmin(Velocity.y + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
                    }
                    if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::D)
                    {
                        if (Velocity.x < 0.0f) { Velocity.x = std::fmax(Velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
                        else { Velocity.x = std::fmin(Velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
                    }
                }
//*/