#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Entity.h"

class Button :
    public Entity
{
public:
    enum btState
    {
        IDLE,
        PRESS,
        RELEASE,
        HOVER
    };

    bool hover;
    bool signal;

    btState prevState;
    btState curState;
    btState state;

    sf::Font font;
    sf::Text text;
    sf::Vector2f textPos;
    
    Button(std::string imageName, sf::Vector2f position, sf::Vector2i size, sf::IntRect textureRect, float scale = 1.0f);
    ~Button();

    void initText(std::string fontName, sf::Vector2f txtPos, std::string text, int fntSize);
    void update();
    void processInput();

    void action();
    void deaction();

    bool AABB(sf::Vector2i pos);

    void btChangeState(btState state);
};

