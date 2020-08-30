#ifndef SYSTEM_H
#define SYSTEM_H 
#define magic(x) #x

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>
#include <cstdlib>

#include"Mouse.h"
#include"Keyboard.h"

class StateBase;

class System{
public:

	Mouse mouse;
	Keyboard keyboard;

	bool isGame = false;
	void Init();
	sf::RenderWindow& GetWindow();
	sf::Event& GetEvent();
	void ChangeState(StateBase* state);
	void PushState(StateBase* state);
	void PopState();
	void SetTitle(std::string Name);
	float GetTime() { return fTime; }
	sf::Vector2u GetWindowSize() { return window.getSize(); }
	sf::Time getTime() { return time; }
    sf::Vector2i getCursorPosition();

private:

	int iWindowWidth = 1280;
	int iWindowHeight = 1024;
	int iFrameLimit = 0;

	float fGameSpeed = 300.f;
	float fGameTick = 40.f;
	float fTime = 0.f;
	
	bool bFullscreen = false;

	std::string sWindowName = "InfinityTrails";

//---------------------------------------//

	sf::Event event;
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Image icon;
	sf::Image cImage;
	sf::Cursor cursor;
	sf::Time time;
	
	void CreateWindow(int Width, int Height, std::string Title);
	inline void Render(sf::RenderWindow& window);
	void MainLoop(StateBase& state);
	inline void Update(float time);
	inline void HandleEvents(sf::Event event);

	std::vector<StateBase*> states;
	inline void Clock();

};
#endif