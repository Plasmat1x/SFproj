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

        oldPos = Position.position;
        oldVel = Velocity.velocity;

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
        }});
        //*/

        States.states.at("was_ground") = States.states.at("on_ground");
        States.states.at("pushed_left") = States.states.at("push_left");
        States.states.at("pushed_right") = States.states.at("push_right");
        States.states.at("pushed_up") = States.states.at("push_up");

        groundY = 0;
        ceil = 0;
        lwallX = 0;
        rwallX = 0;

        if (Velocity.velocity.x > 0.0f)
        {
            Velocity.velocity.x = int(std::fmax(Velocity.velocity.x - std::abs(Velocity.velocity.x * dt * 3.0f), 0.0f));
        }
        else if (Velocity.velocity.x < 0.0f)
        {
            Velocity.velocity.x = int(std::fmin(Velocity.velocity.x + std::abs(Velocity.velocity.x * dt * 3.0f), 0.0f));
        }

        if (!States.states.at("on_ground"))
        {
            Velocity.velocity.y += std::fmax(5.0f * dt, 20.0f);
        }
        else if(States.states.at("on_ground"))
        {
            Velocity.velocity.y = 0.0f;
        }
        

        if (States.states.at("move_left"))
        {
            moveL(dt, Velocity);
        }
        if (States.states.at("move_right"))
        {
            moveR(dt, Velocity);
        }

        if (Position.position.y + Velocity.velocity.y * dt >= 440)
        {
            States.states.at("on_ground") = true;
        }

        Position.position.x += Velocity.velocity.x * dt;
        Position.position.y += Velocity.velocity.y * dt;

        Rect.update(Position.position.x, Position.position.y);
    }
}

void SYS::PhysicsSystem::moveR(float dt, COM::RigidBody& Velocity)
{
    if (Velocity.velocity.x < 0.0f) { Velocity.velocity.x = std::fmax(Velocity.velocity.x + Velocity._ACCELERATION * dt, 0.0f); }
    else { Velocity.velocity.x = std::fmin(Velocity.velocity.x + Velocity._ACCELERATION * dt, Velocity._MAXSPEED); }
}

void SYS::PhysicsSystem::moveL(float dt, COM::RigidBody& Velocity)
{
    if (Velocity.velocity.x > 0.0f) { Velocity.velocity.x = std::fmin(Velocity.velocity.x - Velocity._ACCELERATION * dt, 0.0f); }
    else { Velocity.velocity.x = std::fmax(Velocity.velocity.x - Velocity._ACCELERATION * dt, -Velocity._MAXSPEED); }
}



/*/
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

//*/