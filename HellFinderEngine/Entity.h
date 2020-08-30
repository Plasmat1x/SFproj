#ifndef ENTITY_H
#define ENTITY_H

#include "System.h"
#include "AnimatedSprite.h"

class Entity {
protected:
	int defaultNumbersOfFrames;
	float posX, posY, width, height, accelerationX, accelerationY, speedH, speedV, scaleW, scaleH, frameTime;
	enum MoveDirection { NONE, LEFT, RIGHT, UP, DOWN };
	MoveDirection doMoveH , doMoveV;
	sf::Texture texture;
	AnimationManager walkingAnimationLeft, walkingAnimationRight, walkingAnimationUp, walkingAnimationDown, IDLEAnimation;
	AnimationManager* currentAnimation;
	AnimatedSprite sprite;
	sf::Vector2i defaultFrameSize, defaultSPOSS;
public:
	Entity();
	virtual void Init(std::string imageFileName, float x, float y, float w, float h);
	virtual void SetAnimation(AnimationManager &animation, sf::Texture &spriteSheet, int numpersOfFrames, sf::Vector2i frameSize, sf::Vector2i startPositionOnSpriteSheet);
	virtual void Update(System* game, float Time);
	virtual inline void HandleEvents(System* game);
	virtual void Draw(System* game);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f position);
};
#endif