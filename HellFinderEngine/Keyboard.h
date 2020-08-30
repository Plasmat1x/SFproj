#include <SFML/Graphics.hpp>

class Keyboard
{
private:
	bool mass[101];
	void data();
public:
	Keyboard();
	~Keyboard();
	int getEventButton(sf::Keyboard::Key key);
};