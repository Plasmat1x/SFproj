#include "Mouse.h"
#include <iostream>

Mouse::Mouse()
{
	data();
}
Mouse::~Mouse() {}
void Mouse::data()
{
	posX = 0;
	posY = 0;
	for (int i = 0; i < 5; i++)
		mass[i] = false;
}

bool Mouse::setWindow(sf::RenderWindow *RenderWindow)
{
	try
	{
		window = RenderWindow;
	}
	catch (...)
	{
		std::cout << "Error Mouse::setWindow";
		return false;
	}
	return true;
}

void Mouse::behavior()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	sf::Vector2f pos = (*window).mapPixelToCoords(pixelPos);
	posX = pos.x;
	posY = pos.y;
}
int Mouse::getX()
{
	return posX;
}
int Mouse::getY()
{
	return posY;
}

int Mouse::getEventButton(sf::Mouse::Button button)
{
	bool isPressed = sf::Mouse::isButtonPressed(button);
	bool isPressed2 = mass[button];

	if (isPressed2 != isPressed)
	{
		if (isPressed2 == true)
		{
			mass[button] = false;
			return 3;
		}
		else
		{
			mass[button] = true;
			return 1;
		}
	}
	else
	{
		if (isPressed2 == true)
			return 2;
		else
			return 0;
	}
}