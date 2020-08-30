#include"System.h"
#define pow2(x) ((x)*(x))

class CameraView
{
private:
	float posX, posY, width, height, CornerV, CornerH, cameraSpeed, accelerationX, accelerationY, speedH, speedV;
	float leftCorner, rightCorner, upCorner, downCorner;
	std::vector<bool> collisionMap;
	sf::View view;
	enum Collision { NOCOLLISION, LEFT, RIGHT, UP, DOWN };
public:
	void Init(float X, float Y, float W, float H);
	void checkCollision(sf::FloatRect);
	void Update(float time, sf::FloatRect);
	void setCorners(int W, int H);
	void resetPosition(sf::Vector2f point);
	float getPosX();
	float getPosY();
	sf::View getView();
};

