#pragma once
#include <SFML/Graphics.hpp>

#include "Animation.h"

namespace COM
{
    class c_position
    {
    public:
        float x;
        float y;
    };

    class c_velocity
    {
    public:
        float x;
        float y;

        float _ACCELERATION;
        float _MAXSPEED;
    };

    class c_sprite
    {
    public:
        sf::Sprite sprite;
    };

    class c_view
    {
    public:
        sf::View* view;
    };

    class c_input
    {
    public:
        std::vector<sf::Keyboard::Key> KeyList{};
    };

    class c_size
    {
    public:
        float x;
        float y;
    };

    class c_hitbox
    {
    public:
        sf::Vector2f size;
        sf::Vector2f offset;
        sf::RectangleShape shape;
        bool draw;

        void initHitbox()
        {
            shape.setSize(sf::Vector2f(size.x * 0.5f, size.y * 0.66f));
            //shape.setSize(sf::Vector2f(size.x, size.y));
            shape.setOrigin(sf::Vector2f(shape.getSize().x * 0.5f + offset.x, shape.getSize().x * 0.5f + offset.x));
        }

        void update(float x, float y)
        {
            //shape.setPosition(sf::Vector2f(x + offset.x, y + offset.y));
            shape.setPosition(sf::Vector2f(x, y));
        }
    };

    class c_animation
    {
    public:
        sf::Sprite* sprite;
        Animation _animation;
        AnimationManager anim_mgr;
    };

    class c_state
    {
    public:
        std::map<const char*, bool> anim_states{};
        std::map<const char*, bool> states{};
    };
}
