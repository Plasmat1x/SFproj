#pragma once
#include <SFML/Graphics.hpp>

namespace COM
{
    struct Position
    {
        float x;
        float y;
    };

    struct Size
    {
        float x;
        float y;
    };

    struct Velocity
    {
        float x;
        float y;

        float _ACCELERATION;
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
}
