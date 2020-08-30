#ifndef STATEGAME_H
#define STATEGAME_H

#include "System.h"
#include "StateBase.h"
#include "Entity.h"
#include "CameraView.h"
#include "Map.h"

class StateGame : public StateBase
{
public:
	void Init(System* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(System* game);
	void Update(System* game,float Time);
	void Render(System* game);

	static StateGame* Instance() {
		return &m_StateGame;
	}

protected:
	StateGame() { }

private:
	Map map;
	CameraView camera;
	sf::Vector2f playerPosition;
	sf::Vector2f playerSize;
	static StateGame m_StateGame;
	Entity Player;
};

#endif