#include"Keyboard.h"

Keyboard::Keyboard()
{
	data();
}
Keyboard::~Keyboard() {}
void Keyboard::data()
{
	for (int i = 0; i < 101; i++)
		mass[i] = false;
}
int Keyboard::getEventButton(sf::Keyboard::Key key)
{
	bool isPressed = sf::Keyboard::isKeyPressed(key);
	bool isPressed2 = mass[key];

	if (isPressed2 != isPressed)
	{
		if (isPressed2 == true)
		{
			mass[key] = false;
			return 3;
		}
		else
		{
			mass[key] = true;
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