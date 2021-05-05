#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <tinyxml/tinyxml.h>

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

    int row;
    int col;

    sf::Rect<float> drawingBounds;
    sf::Texture* tileSet;
    std::vector<Layer> layers;

    sf::Texture* texture;

public:
    Level(std::string path, sf::Texture* texture, sf::Vector2i arr_size)
    {
        init(path, texture, arr_size);
    }
    Level() {}

    void init(std::string path, sf::Texture* texture, sf::Vector2i arr_size);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};

