#include "Player.h"



Player::Player(std::string imageName, sf::Vector2f position, sf::Vector2i size, sf::IntRect textureRect, float scale) :
    Entity(imageName, position, size, textureRect, scale)
{

}


Player::~Player()
{
}
