#include "System.h"
#include "StateBase.h"
#include "StateIntro.h"
#include "Config.h"

void System::Init()
{	
	mouse.setWindow(&window);
	//err().rdbuf(NULL); // возможно эта параша вообще выключит вывод ошибок в консоль что хуево либо все придется выводить через if + cout
	icon.loadFromFile("res/img/icon.png");
	cImage.loadFromFile("res/img/cursor.png");
	cursor.loadFromPixels(cImage.getPixelsPtr(), sf::Vector2u(8, 16), sf::Vector2u(0, 0));
	//config
	Config config;
	iWindowHeight = config.getParam(magic(iWindowHeight));
	iWindowWidth = config.getParam(magic(iWindowWidth));
	iFrameLimit = config.getParam(magic(iFrameLimit));
	//end config
	CreateWindow(iWindowWidth,iWindowHeight,sWindowName);
	this->ChangeState(StateIntro::Instance());
	MainLoop(*states.back());
}

void System::CreateWindow(int Width, int Height, std::string Title)
{
	sf::VideoMode::getFullscreenModes();
	window.create(sf::VideoMode(Width,Height), Title, sf::Style::Close);
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(iFrameLimit);
	window.setActive(true);
	window.setIcon(32,32, icon.getPixelsPtr());
	window.setMouseCursor(cursor);
}

void System::MainLoop(StateBase& state)
{
	
	while(window.isOpen())
	{
		Clock();
		HandleEvents(event);
		Update(fTime);
		Render(window);
	}
	
}

inline void System::Render(sf::RenderWindow& window)
{
	states.back()->Render(this);
}

inline void System::Update(float time)
{
	states.back()->Update(this, time);
	mouse.behavior();
}

inline void System::HandleEvents(sf::Event event)
{
	while (window.pollEvent(event))
	{
		if (event.type == event.Closed) window.close();
		//if (event.type == event.Resized) { window.setSize(Vector2u(event.size.width, event.size.height)); }
	}
	states.back()->HandleEvents(this);
}

sf::RenderWindow& System::GetWindow()
{
	return window;
}

sf::Event& System::GetEvent()
{
	return event;
}

void System::ChangeState(StateBase* state)
{
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
	states.push_back(state);
	states.back()->Init(this);
}

void System::PushState(StateBase* state){
	if ( !states.empty() ) {
		states.back()->Pause();
	}
	states.push_back(state);
	states.back()->Init(this);
}

void System::PopState()
{
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}

void System::Clock()
{
	fTime = clock.getElapsedTime().asMicroseconds();
	time = clock.restart();

	fTime /= fGameSpeed;

	if (fTime > fGameTick )
		fTime = fGameTick;
}

void System::SetTitle(std::string Name) {
	window.setTitle(Name);
}

sf::Vector2i System::getCursorPosition()
{
    return sf::Mouse::getPosition(window);
}




