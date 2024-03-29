#pragma once
#include <SFML/Graphics.hpp>

namespace COM
{
    struct Position
    {
        float x;
        float y;
    };

    struct Velocity
    {
        float x;
        float y;

        float _ACCELERATION;
        float _MAXSPEED;
    };

    struct Sprite
    {
        sf::Sprite sprite;
    };

    struct View
    {
        sf::View* view;
    };

    struct InputComponent 
    {
        std::vector<sf::Keyboard::Key> KeyList{};
    };

    struct Size
    {
        float x;
        float y;
    };

    struct Hitbox
    {
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
}
