#include "PhysicsSystem.h"
#include "Coordinator.h"

#include "COM_LIB.h"

#include <iostream>

extern ECS::Coordinator gCoordinator;

void SYS::PhysicsSystem::init(Level* level)
{
    /*/
    groundY = 0;
    ceil = 0;
    lwallX = 0;
    rwallX = 0;
    //*/
    this->level = level;
}

void SYS::PhysicsSystem::update(float dt)
{
    for (auto const& entity : mEntities)
    {
        auto& Position = gCoordinator.GetComponent<COM::Transform>(entity);
        auto& Velocity = gCoordinator.GetComponent<COM::RigidBody>(entity);
        auto& Rect = gCoordinator.GetComponent<COM::Hitbox>(entity);
        auto& States = gCoordinator.GetComponent<COM::States>(entity);

        //save prev frame data
        oldPos = Rect.position;
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

        //update positions
        Position.position.x += Velocity.velocity.x * dt;
        Position.position.y += Velocity.velocity.y * dt;

        Rect.update(Position.position.x, Position.position.y);

        // Test physics
        float groundY = 0;
        float ceilY = 0;
        float wallL = 0;
        float wallR = 0;

        //check leftwall
        if (Velocity.velocity.x <= 0.0f
            && hasLW(oldPos, Rect, Velocity, wallL))
        {
            if (oldPos.x - Rect.half.x + Rect.offset.x >= wallL)
            {
                Position.position.x = wallL - Rect.offset.x;
                States.states.at("push_left") = true;
            }
            Velocity.velocity.x = std::fmax(Velocity.velocity.x, 0.0f);
        }
        else
        {
            States.states.at("push_left") = false;
        }

        //check right wall
        if (Velocity.velocity.x >= 0.0f
            && hasRW(oldPos, Rect, Velocity, wallR))
        {
            if (oldPos.x + Rect.half.x - Rect.offset.x <= wallR)
            {
                Position.position.x = wallR - Rect.size.x - Rect.offset.x;
                States.states.at("push_right") = true;
            }
            Velocity.velocity.x = std::fmin(Velocity.velocity.x ,0.0f);
        }
        else
        {
            States.states.at("push_right") = false;
        }

        //check ground
        if (Velocity.velocity.y >= 0.0f
            && hasGround(oldPos, Rect, Velocity, States, groundY))
        {
            Position.position.y = groundY - Rect.size.y - Rect.offset.y;
            States.states.at("on_ground") = true;
        }
        else
        {
            States.states.at("on_ground") = false;
            States.states.at("on_platform") = false;
        }

        //check ceil
        if (Velocity.velocity.y <= 0.0f
            && hasCeil(oldPos, Rect, Velocity, ceilY))
        {
            Position.position.y = ceilY - Rect.offset.y;
            States.states.at("push_up") = true;
            Velocity.velocity.y = 0.0f;
        }
        else
        {
            States.states.at("push_up") = false;
        }

        //*//gravity
        if (!States.states.at("on_ground"))
        {
            Velocity.velocity.y = std::fmin(Velocity.velocity.y + 23.0f, 1000.0f);
        }
        else if (States.states.at("on_ground"))
        {
            Velocity.velocity.y = 0.0f;
            //friction(трение)
            friction(dt, Velocity);
        }
        //*/

        //move entity x axis
        if (States.states.at("move_left"))
        {
            moveL(dt, Velocity);
        }
        if (States.states.at("move_right"))
        {
            moveR(dt, Velocity);
        }
        if (States.states.at("move_down"))
        {
            if (States.states.at("on_platform") && States.states.at("on_ground"))
            {
                Position.position.y += level->getTileSize().y * 1;
            }
        }

        /*/
        //collision with end map"512"
        if (Position.position.y + Velocity.velocity.y * dt >= 512 - 60)
        {
            States.states.at("on_ground") = true;
        }
        //*/
        //Rect.update(Position.position.x, Position.position.y); // chek
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

void SYS::PhysicsSystem::friction(float dt, COM::RigidBody& Velocity)
{
    if (Velocity.velocity.x > 0.0f)
    {
        Velocity.velocity.x = int(std::fmax(Velocity.velocity.x - std::abs(Velocity.velocity.x * dt * 3.0f), 0.0f));
    }
    else if (Velocity.velocity.x < 0.0f)
    {
        Velocity.velocity.x = int(std::fmin(Velocity.velocity.x + std::abs(Velocity.velocity.x * dt * 3.0f), 0.0f));
    }
}

bool SYS::PhysicsSystem::hasGround(const sf::Vector2f& oldPos, const COM::Hitbox& hb, const COM::RigidBody& rb, COM::States& st, float& groundY)
{
    sf::Vector2f oldCenter = oldPos + hb.half;
    sf::Vector2f center = hb.center;

    sf::Vector2f oldBL = sf::Vector2f(oldCenter.x - hb.half.x, oldCenter.y + hb.half.y) + sf::Vector2f(0,1) + sf::Vector2f(1,0);
    sf::Vector2f newBL = sf::Vector2f(center.x - hb.half.x, center.y + hb.half.y) + sf::Vector2f(0, 1) + sf::Vector2f(1, 0);

    int endY = level->getMapTileYAtPoint(newBL.y);
    int begY = std::fmax(level->getMapTileYAtPoint(oldBL.y) - 1, endY);
    int dist = std::fmax(std::abs(endY - begY), 1);

    int TIX; //tile index x
    for (int TIY = begY; TIY <= endY; ++TIY)
    {
        sf::Vector2f BL = lerpvec2(newBL, oldBL, float(std::abs(endY - TIY)));
        sf::Vector2f BR = sf::Vector2f(BL.x + hb.size.x - 2.0f, BL.y);

        for (sf::Vector2f chekedTile = BL; ; chekedTile.x += level->getTileSize().x)
        {
            chekedTile.x = std::fmin(chekedTile.x, BR.x);
            TIX = level->getMapTileXAtPoint(chekedTile.x);
            groundY = float(TIY * level->getTileSize().y);
            
            if (level->isGround(TIX, TIY))
            {

                st.states.at("on_platform") = false;
                if (level->isPlatform(TIX, TIY))
                {
                    st.states.at("on_platform") = true;
                    return true;
                }

                return true;
            }

            if (chekedTile.x >= BR.x)
            {
                break;
            }
                
        }
    }


    return false;
}

bool SYS::PhysicsSystem::hasCeil(const sf::Vector2f& oldPos, const COM::Hitbox& hb, const COM::RigidBody& rb, float& ceilY)
{

    sf::Vector2f oldCenter = oldPos + hb.half;
    sf::Vector2f center = hb.center;

    sf::Vector2f oldTL = sf::Vector2f(oldCenter.x - hb.half.x, oldCenter.y - hb.half.y) - sf::Vector2f(0, 1) + sf::Vector2f(1, 0);
    sf::Vector2f newTL = sf::Vector2f(center.x - hb.half.x, center.y - hb.half.y) - sf::Vector2f(0, 1) + sf::Vector2f(1, 0);

    int endY = level->getMapTileYAtPoint(newTL.y);
    int begY = std::fmin(level->getMapTileYAtPoint(oldTL.y) + 1, endY);
    int dist = std::fmax(std::abs(endY - begY), 1);

    int TIX; //tile index x
    for (int TIY = begY; TIY >= endY; --TIY)
    {
        sf::Vector2f TL = lerpvec2(newTL, oldTL, float(std::abs(endY - TIY)));
        sf::Vector2f TR = sf::Vector2f((TL.x + hb.size.x) - 2.0f, TL.y);

        for (sf::Vector2f chekedTile = TL; ; chekedTile.x += level->getTileSize().x)
        {
            chekedTile.x = std::fmin(chekedTile.x, TR.x);
            TIX = level->getMapTileXAtPoint(chekedTile.x);
            if (level->isObstacle(TIX, TIY))
            {
                if (rb.velocity.y < 0)
                {
                    ceilY = float(TIY * level->getTileSize().y + level->getTileSize().y);
                }
                return true;
            }
            if (chekedTile.x >= TR.x)
                break;
        }
    }


    return false;
}
//*/
bool SYS::PhysicsSystem::hasLW(const sf::Vector2f& oldPos, const COM::Hitbox& hb, const COM::RigidBody& rb, float& wallL)
{
    sf::Vector2f oldCenter = oldPos + hb.half;
    sf::Vector2f center = hb.center;

    sf::Vector2f oldTL = sf::Vector2f(oldCenter.x - hb.half.x, oldCenter.y - hb.half.y) - sf::Vector2f(1, 0) + sf::Vector2f(0, 5);
    sf::Vector2f newTL = sf::Vector2f(center.x - hb.half.x, center.y - hb.half.y) - sf::Vector2f(1, 0) + sf::Vector2f(0, 5);

    int endX = level->getMapTileXAtPoint(newTL.x);
    int begX = std::fmax(level->getMapTileXAtPoint(oldTL.x) - 1, endX);
    int dist = std::fmax(std::abs(endX - begX), 1);

    int TIY;
    for (int TIX = begX; TIX >= endX; --TIX)
    {
        sf::Vector2f TL = lerpvec2(newTL, oldTL, (float)std::abs(endX - TIX));
        sf::Vector2f BL = sf::Vector2f(TL.x, TL.y + hb.size.y - 10);

        for (sf::Vector2f chekedTile = TL; ; chekedTile.y += level->getTileSize().y)
        {
            chekedTile.y = std::fmin(chekedTile.y, BL.y);
            TIY = level->getMapTileYAtPoint(chekedTile.y);

            if (level->isObstacle(TIX, TIY))
            {
                wallL = float(TIX * level->getTileSize().x + level->getTileSize().x);
                return true;
            }
            if (chekedTile.y >= BL.y)
            {
                break;
            }
        }
    }
    return false;
}

bool SYS::PhysicsSystem::hasRW(const sf::Vector2f& oldPos, const COM::Hitbox& hb, const COM::RigidBody& rb, float& wallR)
{
    sf::Vector2f oldCenter = oldPos + hb.half;
    sf::Vector2f center = hb.center;

    sf::Vector2f oldTR = sf::Vector2f(oldCenter.x + hb.half.x, oldCenter.y - hb.half.y) + sf::Vector2f(1, 0) + sf::Vector2f(0, 5);
    sf::Vector2f newTR = sf::Vector2f(center.x + hb.half.x, center.y - hb.half.y) + sf::Vector2f(1, 0) + sf::Vector2f(0, 5);

    int endX = level->getMapTileXAtPoint(newTR.x);
    int begX = std::fmin(level->getMapTileXAtPoint(oldTR.x) + 1, endX);
    int dist = std::fmax(std::abs(endX - begX), 1);

    int TIY;
    for (int TIX = begX; TIX <= endX; ++TIX)
    {
        sf::Vector2f TR = lerpvec2(newTR, oldTR, (float)std::abs(endX - TIX));
        sf::Vector2f BR = sf::Vector2f(TR.x, TR.y + hb.size.y - 10);

        for (sf::Vector2f chekedTile = TR; ; chekedTile.y += level->getTileSize().y)
        {
            chekedTile.y = std::fmin(chekedTile.y, BR.y);
            TIY = level->getMapTileYAtPoint(chekedTile.y);

            if (level->isObstacle(TIX, TIY))
            {
                wallR = float(TIX * level->getTileSize().x);
                return true;
            }
            if (chekedTile.y >= BR.y)
            {
                break;
            }
        }
    }
    return false;
}
//*/

float SYS::PhysicsSystem::clamp01(float value)
{
    if ((double)value < 0.0)
        return 0.0f;
    if ((double)value > 1.0)
        return 1.f;
    return value;
}

sf::Vector2f SYS::PhysicsSystem::lerpvec2(sf::Vector2f a, sf::Vector2f b, float t)
{
    t = clamp01(t);
    return sf::Vector2f(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
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