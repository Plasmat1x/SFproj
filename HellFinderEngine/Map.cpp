#include"Map.h"

void Map::Init(std::string path){
	image.loadFromFile(path);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	tWidth = 32;
	tHeight = 32;
}

void Map::Update(System *game) {

}

void Map::Render(System *game){
	for (int i = 0; i < 10 ; i++)
		for (int j = 0; j < 10; j++)
		{
			x = j * tWidth;
			y = i * tHeight;

			if (map[i][j] == '0') sprite.setTextureRect(sf::IntRect(0, 0, tWidth, tHeight));
			sprite.setPosition(x, y);
			game->GetWindow().draw(sprite);
		}
}

