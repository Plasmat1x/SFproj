#include "PhysicsSystem.h"
#include "Coordinator.h"

#include "COM_LIB.h"

extern ECS::Coordinator gCoordinator;

void SYS::PhysicsSystem::update(float dt)
{
    for (auto const& entity : mEntities)
    {
        auto& Position = gCoordinator.GetComponent<COM::Transform>(entity);
        auto& Velocity = gCoordinator.GetComponent<COM::RigidBody>(entity);
        auto& Rect = gCoordinator.GetComponent<COM::Hitbox>(entity);

        float mass = 3.0f;

        if (Velocity.velocity.y > 0.0f)
        {
            Velocity.velocity.y = int(std::fmax(Velocity.velocity.y - std::abs(Velocity.velocity.y * dt * mass), 0.0f));
        }
        else if (Velocity.velocity.y < 0.0f)
        {
            Velocity.velocity.y = int(std::fmin(Velocity.velocity.y + std::abs(Velocity.velocity.y * dt * mass), 0.0f));
        }

        if (Velocity.velocity.x > 0.0f)
        {
            Velocity.velocity.x = int(std::fmax(Velocity.velocity.x - std::abs(Velocity.velocity.x * dt * mass), 0.0f));
        }
        else if (Velocity.velocity.x < 0.0f)
        {
            Velocity.velocity.x = int(std::fmin(Velocity.velocity.x + std::abs(Velocity.velocity.x * dt * mass), 0.0f));
        }

        Position.position.x += Velocity.velocity.x * dt;
        Position.position.y += Velocity.velocity.y * dt;

        Rect.update(Position.position.x, Position.position.y);
    }
}