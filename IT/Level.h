#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level : public sf::Drawable
{
private:
    int tileWidth;
    int tileHeight;
    int width;
    int height;
    int firstTileID;

    sf::Rect<float> drawingBounds;
    sf::Texture* tileSet;
    std::vector<Layer> layers;

public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state);
};

