#include "MultiTileObject.h"
/* work code part for object from 9 sprites scaleable withoud deformation

    [0] [1]_[2]

    [3] [4]_[5]
     |   |   |
    [6] [7]_[8]

    | - y dependices
    _ - x dependices
*
* 
* 
    sf::Vector2i size(4, 8);
    sf::Vector2f scale(1, 1);
    sf::Vector2f addscale(120, 50);
    sf::Vector2f position(20, 20);
    int index = 0;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            sprites.push_back(
                sf::Sprite(*ResourceManager::getTexture("meta_button"),
                    sf::IntRect(
                        (size.x * j),
                        (size.y * i),
                        size.x, size.y)));

            sprites[index].setScale(scale);
            sprites[index].setPosition(position.x + (j * size.x * scale.x), position.y + (i * size.y * scale.y));

            // XY dependices
            if (index == 8)
            {
                sprites[index].setPosition(
                    position.x + ((j - 1) * size.x * scale.x) + (size.x * (scale.x * addscale.x)),
                    position.y + ((i - 1) * size.y * scale.y) + (size.y * (scale.y * addscale.y)));
            }
            // Y dependices
            if (index == 6 || index == 7)
            {
                sprites[index].setPosition(
                    position.x + (j * size.x * scale.x),
                    position.y + ((i - 1) * size.y * scale.y) + (size.y * (scale.y * addscale.y)));
            }
            // X dependices
            if (index == 2 || index == 5)
            {
                sprites[index].setPosition(
                    position.x + ((j - 1) * size.x * scale.x) + (size.x * (scale.x * addscale.x)),
                    position.y + (i * size.y * scale.y));
            }


            // XY scale dependices
            if (index == 4)
            {
                sprites[index].setScale(scale.x * addscale.x, scale.y * addscale.y);
            }
            // Y scale dependices
            if (index == 3 || index == 5)
            {
                sprites[index].setScale(scale.x, scale.y * addscale.y);
            }
            // X scale dependices
            if (index == 1 || index == 7)
            {
                sprites[index].setScale(scale.x * addscale.x, scale.y);
            }

            ++index;
        }
    }
*/

void MultiTileObject::calcBounds()
{
    int x = this->position.x - origin.y;
    int y = this->position.y - origin.y;

    int w = (this->sprites[0].getLocalBounds().width * this->scale.x) +
        (this->sprites[2].getLocalBounds().width * this->scale.x) +
        (this->sprites[1].getLocalBounds().width * (this->scale.x * addscale.x));

    int h = (this->sprites[0].getLocalBounds().height * this->scale.y) +
        (this->sprites[3].getLocalBounds().height * this->scale.y) +
        (this->sprites[6].getLocalBounds().height * (this->scale.y * addscale.y));

    this->globalbounds = sf::IntRect(x, y, w, h);
}

void MultiTileObject::shater()
{
    for (int i = 0; i < arr_size.y; i++)
    {
        for (int j = 0; j < arr_size.x; j++)
        {
            this->sprites.push_back(
                sf::Sprite(*this->texture,
                    sf::IntRect(
                        int((padding + size.x) * j), 
                        int((padding + size.y) * i),
                        int(size.x),
                        int(size.y))));
                    
        }
    }
}

void MultiTileObject::buildDepends()
{
    int index = 0;

    sf::Vector2f position = sf::Vector2f(this->position.x - origin.x,this->position.y - origin.y);

    for (int i = 0; i < this->arr_size.y; i++)
    {
        for (int j = 0; j < this->arr_size.x; j++)
        {
            this->sprites[index].setScale(scale);
            this->sprites[index].setPosition(int(position.x + (j * (size.x * scale.x))), int(position.y + (i * (size.y * scale.y))));

            // XY dependices
            if (index == 8)
            {
                this->sprites[index].setPosition(
                    int(position.x + ((j - 1) * (size.x * scale.x)) + (size.x * (scale.x * addscale.x))),
                    int(position.y + ((i - 1) * (size.y * scale.y)) + (size.y * (scale.y * addscale.y))));
            }
            // Y dependices
            if (index == 6 || index == 7)
            {
                this->sprites[index].setPosition(
                    int(position.x + (j * size.x * scale.x)),
                    int(position.y + ((i - 1) * (size.y * scale.y)) + (size.y * (scale.y * addscale.y))));
            }
            // X dependices
            if (index == 2 || index == 5)
            {
                this->sprites[index].setPosition(
                    int(position.x + (((j - 1) * (size.x * scale.x)) + (size.x * (scale.x * addscale.x)))),
                    int(position.y + (i * size.y * scale.y)));
            }


            // XY scale dependices
            if (index == 4)
            {
                this->sprites[index].setScale(int(scale.x * addscale.x), int(scale.y * addscale.y));
            }
            // Y scale dependices
            if (index == 3 || index == 5)
            {
                this->sprites[index].setScale(int(scale.x), int(scale.y * addscale.y));
            }
            // X scale dependices
            if (index == 1 || index == 7)
            {
                this->sprites[index].setScale(int(scale.x * addscale.x), int(scale.y));
            }

            ++index;
        }
    }
}

int MultiTileObject::getSpriteAt(sf::Vector2f mousePos)
{
    if (sprites.size() == 0) return -1;
    //if (!this->visible) return -1;

    for (int i = 0; i < this->sprites.size(); ++i)
    {
        sf::Vector2f point = mousePos;
        point += this->sprites[i].getOrigin();
        point -= this->sprites[i].getPosition();

        if (point.x < 0 || point.x > this->sprites[i].getScale().x * this->get_in_size().x) continue;
        if (point.y < 0 || point.y > this->sprites[i].getScale().y * this->get_in_size().y) continue;
        return i;
    }

    return -1;
}

sf::Sprite* MultiTileObject::getSprite(int index)
{
    return &this->sprites[index];
}

sf::Sprite* MultiTileObject::getSprite(sf::Vector2f mousePos)
{
    return &sprites[getSpriteAt(mousePos)];
}

sf::Vector2f MultiTileObject::getaddscale()
{
    return this->addscale;
}
sf::Vector2i MultiTileObject::get_in_size()
{
    return this->size;
}

sf::IntRect MultiTileObject::getGloablBounds()
{
    return globalbounds;
}

void MultiTileObject::setPosition(sf::Vector2f position)
{
    this->position = position;
    buildDepends();
    calcBounds();
}

void MultiTileObject::setCenter(sf::Vector2i center)
{
    
}

void MultiTileObject::setSize(sf::Vector2f size)
{
    /*
    sf::Vector2f(
    (this->dimension.x - (entry.mto.get_in_size().x * 2)) / (entry.mto.get_in_size().x),
    (this->dimension.y - (entry.mto.get_in_size().y * 2)) / (entry.mto.get_in_size().y)
                */
    setAddscale(sf::Vector2f(
        ((size.x - (this->size.x * 2)) / this->size.x),
        ((size.y - (this->size.y * 2)) / this->size.y)
    ));
}

void MultiTileObject::setOrigin(sf::Vector2f origin)
{
    this->origin = origin;
    buildDepends();
    calcBounds();
}
void MultiTileObject::setScale(sf::Vector2f scale)
{
    this->scale = scale;
    buildDepends();
    calcBounds();
}
void MultiTileObject::setAddscale(sf::Vector2f addscale)
{
    this->addscale = addscale;
    buildDepends();
    calcBounds();
}

void MultiTileObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto spr : this->sprites)
    {
        target.draw(spr);
    }
}
