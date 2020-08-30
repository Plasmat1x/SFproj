#include "Image.h"
#include "myMath.h"

void Image::update_alpha()
{
	if (alpha < 0)   _alpha = alpha = 0;
	if (alpha > 255) _alpha = alpha = 255;
	sprite.setColor(sf::Color(255, 255, 255, alpha));
}

Image::Image()
{
	data();
}
Image::Image(sf::String filename)
{
	data();
	load(filename);
	w = image.getSize().x;
	h = image.getSize().y;
}
void Image::data()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	setAlpha(255);
}
void Image::load(sf::String filename)
{
	image.loadFromFile(filename);

	texture.loadFromImage(image);
	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(0, 0, getSizeX(), getSizeY()));
	setOriginNum(5);

	w = image.getSize().x;
	h = image.getSize().y;
}
void Image::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
}

float Image::getPositionX(void)
{
	return sprite.getPosition().x;
}
float Image::getPositionY(void)
{
	return sprite.getPosition().y;
}

void Image::setPositionX(float x)
{
	float y = sprite.getPosition().y;
	sprite.setPosition(x, y);
}
void Image::setPositionY(float y)
{
	float x = sprite.getPosition().x;
	sprite.setPosition(x, y);
}
void Image::setPosition(float x, float y)
{
	//sprite.setPosition(x, y);
	this->x = x;
	this->y = y;
	sprite.setPosition(this->x, this->y);
}

void Image::move(float dx, float dy)
{
	//sprite.move(dx, dy);
	x += dx;
	y += dy;
	sprite.setPosition(x, y);
}
void Image::move2(float distance, float angle)
{
	//float dx = distance * mySin(angle);
	//float dy = -1 * distance * myCos(angle);
	//move(dx, dy);
}

void Image::setAlpha(float value_alpha)
{
	alpha = value_alpha;
	update_alpha();
}
void Image::setDAlpha(float value_alpha)
{
	alpha += value_alpha;
	update_alpha();
}
float Image::getAlpha()
{
	return alpha;
}

void Image::setRotation(float angle)
{
	sprite.setRotation(angle);
}
void Image::setRotation(sf::String str, float angle)
{
	/*
	int number;
	if(str == "x")
		number = 1;
	else if(str == "y")
		number = 2;
	else if(str == "z")
		number = 3;
	else
		number = 0;

	switch(number)
	{
	case 1:
		angleX += angle;
		break;
	case 2:
		angleY += angle;
		break;
	case 3:
		angleZ += angle;
		break;
	}
	update_rotation();
	*/
}

void Image::rotate(float angle)
{
	sprite.rotate(angle);
}
float Image::getRotation()
{
	return sprite.getRotation();
}

void Image::setScale(float factorX, float factorY)
{
	sprite.setScale(factorX, factorY);
}
void Image::scale(float factor)
{
	sprite.scale(factor, factor);
}
void Image::scale(float factorX, float factorY)
{
	sprite.scale(factorX, factorY);
}

float Image::getScale()
{
	float scaleX = sprite.getScale().x;
	float scaleY = sprite.getScale().y;

	if (scaleX == scaleY)
		return scaleX; // or scaleY
	else
		return 0;
}
float Image::getScaleX()
{
	return sprite.getScale().x;
}
float Image::getScaleY()
{
	return sprite.getScale().y;
}

float Image::getSizeX(void)
{
	return image.getSize().x;
}
float Image::getSizeY(void)
{
	return image.getSize().y;
}

float Image::getSizeXcurr()
{
	float width = image.getSize().x;
	float scaleX = sprite.getScale().x;
	return width * scaleX;
}

float Image::getSizeYcurr()
{
	float height = image.getSize().y;
	float scaleY = sprite.getScale().y;
	return height * scaleY;
}

void Image::setOriginNum(int number)
{
	int width = image.getSize().x;
	int height = image.getSize().y;

	switch (number)
	{
	case 1: sprite.setOrigin(0, 0); break;
	case 2: sprite.setOrigin(float(width) / 2, 0); break;
	case 3: sprite.setOrigin(width, 0); break;
	case 4: sprite.setOrigin(0, float(height) / 2); break;
	case 5: sprite.setOrigin(float(width) / 2, float(height) / 2); break;
	case 6: sprite.setOrigin(width, float(height) / 2); break;
	case 7: sprite.setOrigin(0, height); break;
	case 8: sprite.setOrigin(float(width) / 2, height); break;
	case 9: sprite.setOrigin(width, height); break;
	default:
		std::cout << "Image::setOriginNum(1~9);" << std::endl;
	}
}

sf::Sprite Image::getSprite()
{
	return sprite;
}

void Image::coutPosition(void)
{
	std::cout << getPositionX() << ":" << getPositionY() << std::endl;
}

void Image::flipHorizontally()
{
	image.flipHorizontally();
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}
void Image::flipVertically()
{
	image.flipVertically();
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}
sf::Image Image::getImage()
{
	return image;
}
void Image::setImage(sf::Image image)
{
	this->image = image;
	w = image.getSize().x;
	h = image.getSize().y;
	texture.loadFromImage(image);
	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(0, 0, getSizeX(), getSizeY()));
}

void Image::setPixel(unsigned int x, unsigned int y, const sf::Color color)
{
	image.setPixel(x, y, color);
}
sf::Color Image::getPixel(unsigned int x, unsigned int y) const
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return sf::Color(0, 0, 0, 0);
	else
		return image.getPixel(x, y);
}
int Image::getAlphaPixel(unsigned int x, unsigned int y) const
{
	return image.getPixel(x, y).a;
}