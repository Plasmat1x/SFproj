#include "Button.h"

Button::Button(std::string imageName, sf::Vector2f position, sf::Vector2i size, sf::IntRect textureRect, float scale) :
    Entity(imageName, position, size, textureRect, scale),
    signal(false),
    hover(false)
{ 
    prevState = IDLE;
    curState = IDLE;

    std::string imgPath = "res/img/" + imageName;
    image.loadFromFile(imgPath);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(position);
    sprite.setScale(scale, scale);
}

Button::~Button()
{

}

void Button::initText(std::string fontName, sf::Vector2f txtPos,  std::string text = "", int fntSize = 16)
{
    this->textPos.x = txtPos.x + position.x;
    this->textPos.y = txtPos.y + position.y;

    std::string fntPath = "res/fonts/" + fontName;
    font.loadFromFile(fntPath);

    this->text.setString(text);
    this->text.setFont(font);
    this->text.setCharacterSize(fntSize);
    this->text.setPosition(textPos);


}

void Button::update()
{
    signal = false;
    if (hover && prevState == PRESS && curState == RELEASE && !signal)
    {
        btChangeState(IDLE);
        state = PRESS;
        signal = true;
    }

    switch (state)
    {
    case IDLE:
        sprite.setTextureRect(sf::IntRect(textureRect.left * 0, textureRect.top, textureRect.width, textureRect.height));
        text.setFillColor(sf::Color::White);
        break;
    case HOVER:
        sprite.setTextureRect(sf::IntRect(textureRect.left * 0, textureRect.top, textureRect.width, textureRect.height));
        text.setFillColor(sf::Color::Green);
        break;
    case PRESS && HOVER:
        sprite.setTextureRect(sf::IntRect(textureRect.left * 1, textureRect.top, textureRect.width, textureRect.height));
        text.setFillColor(sf::Color::Red);
        break;
    case RELEASE:
        sprite.setTextureRect(sf::IntRect(textureRect.left * 0, textureRect.top, textureRect.width, textureRect.height));
        text.setFillColor(sf::Color::White);
        break;
    };
}

void Button::processInput()
{

}

void Button::action()
{
    state = PRESS;
    btChangeState(PRESS);
}

void Button::deaction()
{
    state = RELEASE;
    btChangeState(RELEASE);
}

bool Button::AABB(sf::Vector2i position)
{
    if (getPosition().x                             < position.x &&
        getPosition().x + getSize().x * getScale()  > position.x &&
        getPosition().y                             < position.y &&
        getPosition().y + getSize().y * getScale()  > position.y)
    {     
        state = HOVER;
        hover = true;
        return true;
    }
    else
    {   
        state = IDLE;
        btChangeState(IDLE);
        hover = false;
        return false;
    }
}

void Button::btChangeState(btState state)
{
    prevState = curState;
    curState = state;
}
