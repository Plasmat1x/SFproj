#include "InputSystem.h"
#include "Coordinator.h"
#include "COM_LIB.h"

#include <iostream>

extern ECS::Coordinator gCoordinator;

void SYS::InputSystem::input(float dt)
{
    for (auto const& entity : mEntities)
    {
        auto& Input = gCoordinator.GetComponent<COM::Input>(entity);
        auto& Velocity = gCoordinator.GetComponent<COM::RigidBody>(entity);
        auto& States = gCoordinator.GetComponent<COM::States>(entity);

        for (auto& key : Input.KeyList)
        {

            if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::W)
            {
                States.states.at("run") = true;
                States.states.at("idle") = false;
                States.states.at("move_up") = true;
                break;
            }
            else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::A)
            {
                States.states.at("run") = true;
                States.states.at("idle") = false;
                States.states.at("direction") = false;
                States.states.at("move_left") = true;
                break;
            }
            else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::S)
            {
                States.states.at("run") = true;
                States.states.at("idle") = false;
                States.states.at("move_down") = true;
                break;
            }
            else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::D)
            {
                States.states.at("run") = true;
                States.states.at("idle") = false;
                States.states.at("direction") = true;
                States.states.at("move_right") = true;
                break;
            }
            else
            {
                States.states.at("run") = false;
                States.states.at("idle") = true;
                States.states.at("move_up") = false;
                States.states.at("move_left") = false;
                States.states.at("move_down") = false;
                States.states.at("move_right") = false;
            }
        }
    }
}

/*
 
 if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::W)
            {
                if (Velocity.velocity.y > 0.0f) { Velocity.velocity.y = std::fmin(Velocity.velocity.y - Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.y = std::fmax(Velocity.velocity.y - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
            }
            else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::A)
            {
                if (Velocity.velocity.x > 0.0f) { Velocity.velocity.x = std::fmin(Velocity.velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.x = std::fmax(Velocity.velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
            }
            else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::S)
            {
                if (Velocity.velocity.y < 0.0f) { Velocity.velocity.y = std::fmax(Velocity.velocity.y + Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.y = std::fmin(Velocity.velocity.y + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
            }
            else if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::D)
            {
                if (Velocity.velocity.x < 0.0f) { Velocity.velocity.x = std::fmax(Velocity.velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.x = std::fmin(Velocity.velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
            }
*/