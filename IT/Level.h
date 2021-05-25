#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <tinyxml/tinyxml.h>

//https://github.com/Izaron/Platformer

enum class TileType
{
    EMPTY,
    BLOCK,
    PLATFORM,
};

struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level : public sf::Drawable
{
private:
    int firstTileID;

    sf::Vector2f tileSize;
    sf::Vector2f mapTiles;
    sf::Vector2i tilesetArray;

    sf::Rect<float> drawingBounds;
    sf::Texture* tileSet;
    std::vector<Layer> layers;
    std::vector<std::vector<TileType>> tiles;
    sf::Vector3f mapPosition;

    sf::Texture* texture;

    bool physic_layer = true;

public:
    Level(std::string path, sf::Texture* texture, sf::Vector2i arr_size)
    {
        init(path, texture, arr_size);
    }
    Level() {}

    sf::Vector2i getMapAtPoint(sf::Vector2f point);
    int getMapTileYAtPoint(float y);
    int getMapTileXAtPoint(float x);
    sf::Vector2f getMapTilePosition(sf::Vector2i tileCoords);
    sf::Vector2f getMapTilePosition(int tIndexX, int tIndexY);
    sf::Vector2f getTileSize();
    sf::Vector3f getMapPos();
    sf::Vector2f getMapSize();

    TileType getTile(int x, int y);
    bool isObstacle(int x, int y);
    bool isGround(int x, int y);
    bool isPlatform(int x, int y);
    bool isEmpty(int x, int y);



    void init(std::string path, sf::Texture* texture, sf::Vector2i arr_size);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
};

