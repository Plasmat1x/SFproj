#include "TileSet.h"

Tileset::Tileset()
{
	data();
}
Tileset::Tileset(sf::String filename)
{
	data();
	load("tileset/" + filename);
}


void Tileset::data_frames(int number_frame_width, int number_frame_height)
{
	numFrame = number_frame_width * number_frame_height;

	numFrameWmax = number_frame_width;
	numFrameHmax = number_frame_height;
	data_frames_blackboard(numFrameWmax, numFrameHmax);
	numFrameWcur = 1;
	numFrameHcur = 1;

	int width = getSizeX();
	int height = getSizeY();

	if (number_frame_width > 1)  frameW = int(width / number_frame_width);   else frameW = width;
	if (number_frame_height > 1) frameH = int(height / number_frame_height); else frameH = height;
	sprite.setOrigin(width / numFrameWmax - frameW / 2, height / numFrameHmax - frameH / 2);
	sprite.setTextureRect(sf::IntRect((numFrameWcur - 1)*frameW, (numFrameHcur - 1)*frameH, frameW, frameH));
}
void Tileset::data_frames_blackboard(int number_frame_width, int number_frame_height)
{
	numFrameWmax2 = number_frame_width;
	numFrameHmax2 = number_frame_height;
}

void Tileset::draw(sf::RenderWindow *window)
{
	window->draw(sprite);
}


void Tileset::data()
{
	flag1 = false;
	flag2 = false;
	flag3 = false;

	numFrame = 1;

	numFrameWcur = 1;
	numFrameHcur = 1;
	numFrameWmax = 1;
	numFrameHmax = 1;

	frameW = getSizeX();
	frameH = getSizeY();
}

void Tileset::update_frame()
{
	if (flag1 == true)
	{
		if (flag2 == true)
		{
			numFrameWcur--;
			if (numFrameWcur < 1)
			{
				flag2 = false;
				numFrameWcur = 2;
			}
		}
		else
		{
			numFrameWcur++;
			if (numFrameWcur > numFrameWmax2)
			{
				flag2 = true;
				numFrameWcur = numFrameWmax2 - 1;
			}
		}
	}
	else
	{
		numFrameWcur++;
		if (numFrameWcur > numFrameWmax2)
			numFrameWcur = 1;
	}

	sprite.setTextureRect(sf::IntRect((numFrameWcur - 1)*frameW, (numFrameHcur - 1)*frameH, frameW, frameH));
}

void Tileset::setNumFrameWcur(int number)
{
	if (number > numFrameWmax)
		numFrameWcur = numFrameWmax;
	else if (number < 1)
		numFrameWcur = 1;
	else
		numFrameWcur = number;
	sprite.setTextureRect(sf::IntRect((numFrameWcur - 1)*frameW, (numFrameHcur - 1)*frameH, frameW, frameH));
}

void Tileset::setNumFrameHcur(int number)
{
	if (number > numFrameHmax)
		numFrameHcur = numFrameHmax;
	else if (number < 1)
		numFrameHcur = 1;
	else
		numFrameHcur = number;
	sprite.setTextureRect(sf::IntRect((numFrameWcur - 1)*frameW, (numFrameHcur - 1)*frameH, frameW, frameH));
}

int Tileset::getNumFrameWcur()
{
	return numFrameWcur;
}

int Tileset::getNumFrameHcur()
{
	return numFrameHcur;
}

void Tileset::setFlag1(bool flag)
{
	flag1 = flag;
}
void Tileset::setFlag3(bool flag)
{
	flag3 = flag;
}