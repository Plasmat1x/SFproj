#pragma once
#include <SFML/Graphics.hpp>

namespace COM
{
    class Hitbox
    {
    public:
        //old
        //sf::Vector2f position;
        //sf::Vector2f size;
        //sf::Vector2f center;
        //sf::Vector2f offset;
        //sf::RectangleShape shape;

        //new
        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2f offset;
        sf::RectangleShape shape;
        bool draw = false;
        sf::Vector2f center = sf::Vector2f(0, 0);
        sf::Vector2f half = sf::Vector2f(0, 0);
        sf::Vector2f TL = sf::Vector2f(0, 0); // top left
        sf::Vector2f ML = sf::Vector2f(0, 0); // mid left
        sf::Vector2f BL = sf::Vector2f(0, 0); // bottom left
        sf::Vector2f TR = sf::Vector2f(0, 0); // top right
        sf::Vector2f MR = sf::Vector2f(0, 0); // mid right
        sf::Vector2f BR = sf::Vector2f(0, 0); // bottom right

        void initHitbox()
        {
            // A - shape - base sprite size pos 
            sf::Vector2f bPosA = shape.getPosition();
            sf::Vector2f bSizeA = shape.getSize();
            sf::Vector2f bCenterA = shape.getSize() * 0.5f;

            sf::Vector2f hSizeA = bSizeA * 0.5f;

            // B - hitbox end size pos 
            sf::Vector2f bPosB = position;
            sf::Vector2f bSizeB = size;
            sf::Vector2f bCenterB = size * 0.5f;

            sf::Vector2f hSizeB = bSizeB * 0.5f;

            //calc params
            offset.x += hSizeA.x - hSizeB.x;
            offset.y += bSizeA.y - bSizeB.y;

            half = hSizeB;
            TL = center - half;
            ML = sf::Vector2f(center.x - half.x, center.y);
            BL = sf::Vector2f(center.x - half.x, center.y + half.y);
            TR = sf::Vector2f(center.x + half.x, center.y - half.y);
            MR = sf::Vector2f(center.x + half.x, center.y);
            BR = center + half;

            center = bCenterB + bPosB;

            shape.setSize(size);

        }

        void update(float x, float y)
        {
            position = sf::Vector2f(x + offset.x, y + offset.y);
            center = sf::Vector2f(position.x + size.x * 0.5f, position.y + size.y * 0.5f);
            TL = center - half;
            ML = sf::Vector2f(center.x - half.x, center.y);
            BL = sf::Vector2f(center.x - half.x, center.y + half.y);
            TR = sf::Vector2f(center.x + half.x, center.y - half.y);
            MR = sf::Vector2f(center.x + half.x, center.y);
            BR = center + half;
            shape.setPosition(sf::Vector2f(position.x, position.y));
        }
    };
}


