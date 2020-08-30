#ifndef STATEBASE_H
#define STATEBASE_H

#include "System.h"

class StateBase
{
public:
    sf::Vector2i c_position;

	virtual void Init(System* game) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(System* game) = 0;
	virtual void Update(System* game, float Time) = 0;
	virtual void Render(System* game) = 0;

	void ChangeState(System* game, StateBase* state) {
		game->ChangeState(state);
	}

protected:
	StateBase() { }
	
};

#endif

