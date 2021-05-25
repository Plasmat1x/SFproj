#include "Level.h"

void Level::init(std::string path, sf::Texture* texture, sf::Vector2i arr_size)
{
    tilesetArray = arr_size;

    TiXmlDocument file;
    if (!file.LoadFile(path.c_str()))
    {
        return;
    }

    TiXmlElement* map = file.FirstChildElement("map");

    mapTiles.x = atoi(map->Attribute("width"));
    mapTiles.y = atoi(map->Attribute("height"));
    tileSize.x = atoi(map->Attribute("tilewidth"));
    tileSize.y = atoi(map->Attribute("tileheight"));

    TiXmlElement* tileset = map->FirstChildElement("tileset");
    firstTileID =  atoi(tileset->Attribute("firstgid"));
    int margin = atoi(tileset->Attribute("margin"));
    int spacing = atoi(tileset->Attribute("spacing"));

    tiles.resize(mapTiles.y);
    for (int i = 0; i < mapTiles.y; i++)
    {
        tiles[i].resize(mapTiles.x);
    }

    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < tilesetArray.y; y++)
    {
        for (int x = 0; x < tilesetArray.x; x++)
        {
            sf::Rect<int> rect;

            rect.top    = int(margin + ( spacing + tileSize.y) * y);
            rect.height = int(tileSize.y);
            rect.left   = int(margin + (spacing + tileSize.x) * x);
            rect.width  = int(tileSize.x);

            subRects.push_back(rect);
        }
    }

    TiXmlElement* elayer = map->FirstChildElement("layer");
    while (elayer)
    {
        Layer layer;

        if (elayer->Attribute("opacity") != NULL)
        {
            float opacity = strtod(elayer->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

        TiXmlElement* edata = elayer->FirstChildElement("data"); // proverOCHKA
        TiXmlElement* etile = edata->FirstChildElement("tile"); // proverOCHKA

        int x = 0;
        int y = 0;

        while (etile)
        {
            int tileGID = atoi(etile->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            if (subRectToUse >= 0)
            {
                //Костыль
                if (tileGID == 0)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 1)
                {
                    tiles[y][x] = (TileType::PLATFORM);
                }
                else if (tileGID == 2)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 3)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 4)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 5)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 6)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 7)
                {
                    tiles[y][x] = (TileType::BLOCK);
                }
                else if (tileGID == 8)
                {
                    tiles[y][x] = (TileType::EMPTY);
                }
                //конец костыля

                sf::Sprite sprite;
                sprite.setTexture(*texture);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileSize.x, y * tileSize.y);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
                layer.tiles.push_back(sprite);
            }

            etile = etile->NextSiblingElement("tile");

            x++;
            if (x >= mapTiles.x)
            {
                x = 0;
                y++;
                if (y >= mapTiles.y)
                {
                    y = 0;
                }
            }
        }
        layers.push_back(layer);
        elayer = elayer->NextSiblingElement("layer");
    }
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    for (auto l : layers)
    {
        for (auto s : l.tiles)
        {
            target.draw(s);
        }
    }
}

sf::Vector2i Level::getMapAtPoint(sf::Vector2f point)
{
    return sf::Vector2i(
    (int)((point.x - mapPosition.x + tileSize.x * 0.5f) / (float)tileSize.x),
    (int)((point.y - mapPosition.y + tileSize.y * 0.5f) / (float)tileSize.y)
    );
}

int Level::getMapTileYAtPoint(float y)
{
    return int(y / tileSize.y);
}

int Level::getMapTileXAtPoint(float x)
{
    return int(x / tileSize.x);
}

sf::Vector2f Level::getMapTilePosition(sf::Vector2i tileCoords)
{
    return getMapTilePosition(tileCoords.x, tileCoords.y);
}

sf::Vector2f Level::getMapTilePosition(int tIndexX, int tIndexY)
{
    return sf::Vector2f(
    float(tIndexX * tileSize.x + mapPosition.x),
    float(tIndexY * tileSize.y + mapPosition.y)
    );
}

sf::Vector2f Level::getTileSize()
{
    return sf::Vector2f(tileSize.x, tileSize.y);
}

sf::Vector3f Level::getMapPos()
{
    return mapPosition;
}

sf::Vector2f Level::getMapSize()
{
    return sf::Vector2f(mapTiles.x * tileSize.x, mapTiles.y * tileSize.y);
}

TileType Level::getTile(int x, int y)
{
    if (x < 0 || x >= mapTiles.x
        || y < 0 || y >= mapTiles.y)
        return TileType::BLOCK;
    return tiles[y][x];
}

bool Level::isObstacle(int x, int y)
{
    if (x < 0 || x >= mapTiles.x
        || y < 0 || y >= mapTiles.y)
        return true;
    return (tiles[y][x] == TileType::BLOCK);
}

bool Level::isGround(int x, int y)
{
    if (x < 0 || x >= mapTiles.x
        || y < 0 || y >= mapTiles.y)
        return false;
    return (tiles[y][x] == TileType::BLOCK || tiles[y][x] == TileType::PLATFORM);
}

bool Level::isPlatform(int x, int y)
{
    if (x < 0 || x >= mapTiles.x
        || y < 0 || y >= mapTiles.y)
        return false;
    return (tiles[y][x] == TileType::PLATFORM);
}

bool Level::isEmpty(int x, int y)
{
    if (x < 0 || x >= mapTiles.x
        || y < 0 || y >= mapTiles.y)
        return false;
    return (tiles[y][x] == TileType::EMPTY);
}
