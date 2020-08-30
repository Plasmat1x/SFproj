#ifndef STATEMENU_H
#define STATEMENU_H

#include "System.h"
#include "StateBase.h"
#include "StateGame.h"
#include "Button.h"

class StateMenu : public StateBase
{
public:
    std::vector<Button> buttons;

	void Init(System* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(System* game);
	void Update(System* game, float Time);
	void Render(System* game);

	static StateMenu* Instance() {
		return &m_StateMenu;
	}

protected:
	StateMenu() { }

private:
	sf::View view;
	static StateMenu m_StateMenu;
	sf::Image image;
	sf::Texture texture;
	Button Start;
	Button Options;
	Button Exit;

	sf::Text text;
	sf::Font font;
};

class StateOptions : public StateBase
{
public:
    std::vector<Button> buttons;

	void Init(System* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(System* game);
	void Update(System* game, float Time);
	void Render(System* game);

	static StateOptions* Instance() {
		return &m_StateOptions;
	}

protected:
	StateOptions() { }

private:
	static StateOptions m_StateOptions;
	sf::Image image;
	sf::Texture texture;
	Button Save;
	Button Return;
};

#endif