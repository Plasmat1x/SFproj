#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Entity
{
public:

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2i size;
    sf::IntRect textureRect;
    float scale;


    Entity(std::string path, sf::Vector2f position, sf::Vector2i size, sf::IntRect textureRect, float scale);
    ~Entity();

    void init();
    void update();
    void processInput();

    bool AABB(sf::Vector2i pos);
    bool AABB(Entity entity);
    sf::Vector2i getSize();
    sf::Vector2f getPosition();
    float getScale();

};

