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
        auto& States = gCoordinator.GetComponent<COM::States>(entity);

        float mass = 3.0f;

        //decrase velocity
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

        /*/
        if (States.states.at("move_up"))
        {
            if (Velocity.velocity.y > 0.0f) { Velocity.velocity.y = std::fmin(Velocity.velocity.y - Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.y = std::fmax(Velocity.velocity.y - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
        }
        else if (States.states.at("move_left"))
        {
            if (Velocity.velocity.x > 0.0f) { Velocity.velocity.x = std::fmin(Velocity.velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.x = std::fmax(Velocity.velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
        }
        else if (States.states.at("move_down"))
        {
            if (Velocity.velocity.y < 0.0f) { Velocity.velocity.y = std::fmax(Velocity.velocity.y + Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.y = std::fmin(Velocity.velocity.y + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
        }
        else if (States.states.at("move_right")) 
        {
            if (Velocity.velocity.x < 0.0f) { Velocity.velocity.x = std::fmax(Velocity.velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.x = std::fmin(Velocity.velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
        }
        //*/

        //incrase velocity
        if (States.states.at("move_up"))
        {
            if (Velocity.velocity.y > 0.0f) { Velocity.velocity.y = std::fmin(Velocity.velocity.y - Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.y = std::fmax(Velocity.velocity.y - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
        }
        if (States.states.at("move_left"))
        {
            if (Velocity.velocity.x > 0.0f) { Velocity.velocity.x = std::fmin(Velocity.velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.x = std::fmax(Velocity.velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
        }
        if (States.states.at("move_down"))
        {
            if (Velocity.velocity.y < 0.0f) { Velocity.velocity.y = std::fmax(Velocity.velocity.y + Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.y = std::fmin(Velocity.velocity.y + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
        }
        if (States.states.at("move_right"))
        {
            if (Velocity.velocity.x < 0.0f) { Velocity.velocity.x = std::fmax(Velocity.velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
            else { Velocity.velocity.x = std::fmin(Velocity.velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
        }

        Position.position.x += Velocity.velocity.x * dt;
        Position.position.y += Velocity.velocity.y * dt;

        Rect.update(Position.position.x, Position.position.y);
    }
}