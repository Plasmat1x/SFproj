#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

namespace COM
{
    class Input
    {
    public:
        std::vector<sf::Keyboard::Key> KeyList{};
    };
}

