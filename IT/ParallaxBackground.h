#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct parallax_layer
{
    int width = 0;
    sf::Vector2f position = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f size = sf::Vector2f(0.0f,0.0f);
    //float parallax = 0.0f;
    sf::Vector2f parallax = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f);
    sf::Texture* texture = nullptr;
    sf::Sprite sprite;
};

class ParallaxBackground : public sf::Drawable
{
private:
    std::vector<parallax_layer> layers; 
    sf::Vector2f current_target = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f maxSize = sf::Vector2f(0.0f, 0.0f);
public:

    void add_layer(parallax_layer pBackground, bool tiled, bool bottom);
    void setTarget(sf::Vector2f cur_targ);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

