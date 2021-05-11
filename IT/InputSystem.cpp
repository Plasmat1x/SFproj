#include "InputSystem.h"
#include "Coordinator.h"
#include "COM_LIB.h"

extern ECS::Coordinator gCoordinator;

void SYS::InputSystem::input(float dt)
{
    for (auto const& entity : mEntities)
    {
        auto& Input = gCoordinator.GetComponent<COM::Input>(entity);
        auto& Velocity = gCoordinator.GetComponent<COM::RigidBody>(entity);

        for (auto& key : Input.KeyList)
        {

            if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::W)
            {
                if (Velocity.velocity.y > 0.0f) { Velocity.velocity.y = std::fmin(Velocity.velocity.y - Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.y = std::fmax(Velocity.velocity.y - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
            }
            if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::A)
            {
                if (Velocity.velocity.x > 0.0f) { Velocity.velocity.x = std::fmin(Velocity.velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.x = std::fmax(Velocity.velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
            }
            if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::S)
            {
                if (Velocity.velocity.y < 0.0f) { Velocity.velocity.y = std::fmax(Velocity.velocity.y + Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.y = std::fmin(Velocity.velocity.y + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
            }
            if (sf::Keyboard::isKeyPressed(key) && key == sf::Keyboard::D)
            {
                if (Velocity.velocity.x < 0.0f) { Velocity.velocity.x = std::fmax(Velocity.velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
                else { Velocity.velocity.x = std::fmin(Velocity.velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
            }
        }
    }
}