#include "Entity.h"



Entity::Entity(std::string imageName, sf::Vector2f position, sf::Vector2i size, sf::IntRect textureRect, float scale = 1.0f) :
    position(position),
    size(size),
    textureRect(textureRect),
    scale(scale)
{
    std::string imgPath = "res/img/"+imageName;

    image.loadFromFile(imgPath);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);
}


Entity::~Entity()
{

}

void Entity::init()
{

}

void Entity::update()
{
    
}

void Entity::processInput()
{

}

bool Entity::AABB(sf::Vector2i position)
{
    if (getPosition().x                             < position.x &&
        getPosition().x + getSize().x * getScale()  > position.x &&
        getPosition().y                             < position.y &&
        getPosition().y + getSize().y * getScale()  > position.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Entity::AABB(Entity entity)
{
    if (getPosition().x                             < entity.getPosition().x &&
        getPosition().x + getSize().x * getScale()  > entity.getPosition().x &&
        getPosition().y                             < entity.getPosition().y &&
        getPosition().y + getSize().y * getScale()  > entity.getPosition().y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

sf::Vector2i Entity::getSize()
{
    return size;
}

sf::Vector2f Entity::getPosition()
{
    return position;
}

float Entity::getScale()
{
    return scale;
}


