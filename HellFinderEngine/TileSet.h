#include "System.h"
#include "Image.h"

#ifndef DSL_TILESET_H
#define DSL_TILESET_H

class Tileset : public Image
{
protected:
	bool flag1;
	bool flag2;
	bool flag3;

	int numFrameWcur;
	int numFrameHcur;
	int numFrameWmax;
	int numFrameHmax;

	int numFrameWmax2;
	int numFrameHmax2;
	int frameW;
	int frameH;

	int numFrame;
public:
	Tileset();
	Tileset(sf::String filename);
	void data_frames(int number_frame_width, int number_frame_height);
	void data_frames_blackboard(int number_frame_width, int number_frame_height);
	void draw(sf::RenderWindow *window);
	void data();
	void update_frame();
	void setNumFrameWcur(int number);
	void setNumFrameHcur(int number);
	int getNumFrameWcur();
	int getNumFrameHcur();
	void setFlag1(bool flag); 
	void setFlag3(bool flag); 
	bool getFlag1();
	bool getFlag3();
};

#endif DSL_TILESET_H