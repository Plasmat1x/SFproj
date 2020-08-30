#include "System.h"

class Map {

public:
	void Init(std::string path);
	void Render(System *game);
	void Update(System *game);


private:
	int x;
	int y;
	int tWidth;
	int tHeight;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	std::string map[10]={
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	"00000000000000000",
	};

};