#pragma once
#include <SFML/Graphics.hpp>

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

                
                Position.x += Velocity.x * dt;
                Position.y += Velocity.y * dt;
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

                Sprite.sprite.setPosition(Position.x, Position.y);
                window.draw(Sprite.sprite);
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
                        Velocity.y += -Velocity._ACCELERATION * dt;
                    }
                    else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::A)
                    {
                        Velocity.x += -Velocity._ACCELERATION * dt;
                    }
                    else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::S)
                    {
                        Velocity.y += Velocity._ACCELERATION * dt;
                    }
                    else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::D)
                    {
                        Velocity.x += Velocity._ACCELERATION * dt;
                    }

                }
            }
        }
    };
}