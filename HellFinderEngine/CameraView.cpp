#include "CameraView.h"


void CameraView::Init(float X, float Y, float W, float H)
{
	accelerationX = 0;
	accelerationY = 0;
	speedH = 0;
	speedV = 0;
	posX = X;
	posY = Y;
	width = W;
	height = H;
	view.reset(sf::FloatRect(posX, posY, width, height));
	setCorners(width, height);
	for (int i = 0; i < 4; i++)
		collisionMap.push_back(false);
}

void CameraView::checkCollision(sf::FloatRect player)
{
	for (int i = 0; i < 4; i++)
		collisionMap[i] = false;
	leftCorner = posX - (CornerH / 2);
	rightCorner = posX + (CornerH / 2);
	upCorner = posY - (CornerV / 2);
	downCorner = posY + (CornerV / 2);
	if ((player.left) < leftCorner)
		collisionMap[0] = true;
	if ((player.left) > rightCorner)
		collisionMap[1] = true;
	if ((player.top) < upCorner)
		collisionMap[2] = true;
	if ((player.top) > downCorner)
		collisionMap[3] = true;
}

void CameraView::Update(float time, sf::FloatRect player)
{
	checkCollision(player);
	if (collisionMap[0])
	{
		speedH = pow2(abs((player.left) - leftCorner));
		accelerationX = -speedH;
	}
	if (collisionMap[1])
	{
		speedH = pow2(abs((player.left) - rightCorner));
		accelerationX = speedH;
	}
	if (collisionMap[2])
	{
		speedV = pow2(abs((player.top) - upCorner));
		accelerationY = -speedV;
	}
	if (collisionMap[3])
	{
		speedV = pow2(abs((player.top) - downCorner));
		accelerationY = speedV;
	}

	posX += (accelerationX / 500000) * time;
	posY += (accelerationY / 500000) * time;
	speedH = 0;
	speedV = 0;
	accelerationX = 0;
	accelerationY = 0;

	view.setCenter(posX, posY);
}

void CameraView::setCorners(int W, int H)
{
	CornerH = W * 0.f;
	CornerV = H * 0.f;
}

void CameraView::resetPosition(sf::Vector2f point)
{
	view.setCenter(point.x, point.y);
}

float CameraView::getPosX()
{
	return posX;
}

float CameraView::getPosY()
{
	return posY;
}

sf::View CameraView::getView()
{
	return view;
}