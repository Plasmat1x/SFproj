
#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "./System.h"
#include "./StateBase.h"
#include "./Image.h"

class StateIntro : public StateBase
{
public:
	void Init(System* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(System* game);
	void Update(System* game,float Time);
	void Render(System* game);

	static StateIntro* Instance() {
		return &m_StateIntro;
	}

protected:
	StateIntro() { }

private:
	static StateIntro m_StateIntro;

	int Timer = 0;

	Image img;

	sf::Image Image;
	sf::Texture Texture;
	sf::Sprite Sprite;
};

#endif

