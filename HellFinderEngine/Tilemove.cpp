#include "Tilemove.h"

Tilemovi::Tilemovi(void)
{
	data();
}
Tilemovi::Tilemovi(sf::String filename)
{
	data();
	load("tileset/" + filename);
}
Tilemovi::~Tilemovi(void)
{

}
void Tilemovi::data(void)
{
	data_time_frame(0.25);
}
void Tilemovi::shift_frame(float time)
{
	if (numFrame > 1)
	{
		timeFrameCur += time;
		if (timeFrameCur >= timeFrameMax)
		{
			update_frame();
			timeFrameCur -= timeFrameMax;
		}
	}
}

void Tilemovi::data_time_frame(float time_shift_frame)
{
	timeFrameCur = 0;                
	timeFrameMax = time_shift_frame;
}