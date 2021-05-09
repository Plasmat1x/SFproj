#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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
        void update(float dt)
        {
            for (auto const& entity : mEntities)
            {
                auto& Position = gCoordinator.GetComponent<COM::Position>(entity);
                auto& Velocity = gCoordinator.GetComponent<COM::Velocity>(entity);
                auto& Rect = gCoordinator.GetComponent<COM::Hitbox>(entity);
                
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
                auto& Sprite = gCoordinator.GetComponent<COM::Sprite>(entity);
                auto& Position = gCoordinator.GetComponent<COM::Position>(entity);
                auto& Rect = gCoordinator.GetComponent<COM::Hitbox>(entity);

                Sprite.sprite.setPosition(Position.x, Position.y);
             
                window.draw(Sprite.sprite);

                if (Rect.draw)
                {
                    window.draw(Rect.shape);
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
                auto& View = gCoordinator.GetComponent<COM::View>(entity);
                auto& Position = gCoordinator.GetComponent<COM::Position>(entity);

                View.view->setCenter(Position.x, Position.y);
            }
        }
    };

    class InputSystem : public ECS::System
    {
    public:
        void input(float dt)
        {
            for (auto const& entity : mEntities)
            {
                auto& Input = gCoordinator.GetComponent<COM::InputComponent>(entity);
                auto& Velocity = gCoordinator.GetComponent<COM::Velocity>(entity);

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
            }
        }
    };
}