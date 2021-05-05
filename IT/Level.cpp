#include "Level.h"

void Level::init(std::string path, sf::Texture* texture, sf::Vector2i arr_size)
{
    row = arr_size.y;
    col = arr_size.x;

    TiXmlDocument file;
    if (!file.LoadFile(path.c_str()))
    {
        return;
    }

    TiXmlElement* map = file.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    TiXmlElement* tileset = map->FirstChildElement("tileset");
    firstTileID =  atoi(tileset->Attribute("firstgid"));
    int margin = atoi(tileset->Attribute("margin"));
    int spacing = atoi(tileset->Attribute("spacing"));

    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < col; x++)
        {
            sf::Rect<int> rect;

            rect.top    = int(margin + ( spacing + tileHeight) * y);
            rect.height = int(tileHeight);
            rect.left   = int(margin + (spacing + tileWidth) * x);
            rect.width  = int(tileWidth);

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
                sf::Sprite sprite;
                sprite.setTexture(*texture);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));
                layer.tiles.push_back(sprite);
            }

            etile = etile->NextSiblingElement("tile");

            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if (y >= height)
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
