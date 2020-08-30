#include "System.h"

class Image
{
protected:
	float _alpha;

	sf::String file;
	sf::Image	image;
	sf::Texture texture;
	sf::Sprite sprite;

	void update_alpha();
public:
	float alpha;
	float x;
	float y;
	int w;
	int h;

	Image();
	Image(sf::String filename);

	void data();

	void load(sf::String filename);

	void draw(sf::RenderWindow *window);

	float getPositionX(void);
	float getPositionY(void);

	void setPositionX(float x);
	void setPositionY(float y);
	void setPosition(float x, float y);

	void move(float dx, float dy);
	void move2(float distance, float angle);

	void setAlpha(float value_alpha);
	void setDAlpha(float value_alpha);
	float getAlpha();

	void setRotation(float angle);
	void setRotation(sf::String str, float angle);
	void rotate(float angle);
	float getRotation();

	void setScale(float factorX, float factorY);
	void scale(float factor);
	void scale(float factorX, float factorY);

	float getScale();
	float getScaleX();
	float getScaleY();

	float getSizeX(void);
	float getSizeY(void);

	float getSizeXcurr();
	float getSizeYcurr();

	void setOriginNum(int number);

	sf::Sprite getSprite();

	void coutPosition(void);

	void flipHorizontally();
	void flipVertically();

	sf::Image getImage();
	void setImage(sf::Image image);

	void setPixel(unsigned int x, unsigned int y, const sf::Color color);
	sf::Color getPixel(unsigned int x, unsigned int y) const;
	int getAlphaPixel(unsigned int x, unsigned int y) const;
};