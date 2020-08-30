#include <SFML/Graphics.hpp>

struct MouseKey
{
	bool isKeyPreesed;
};

class Mouse
{
private:
	int posX;
	int posY;
	bool mass[5];
	void data();
	sf::RenderWindow *window;

public:
	Mouse();
	~Mouse();

	bool setWindow(sf::RenderWindow *RenderWindow);
	void behavior();
	int getX();
	int getY();
	int getEventButton(sf::Mouse::Button button);
};