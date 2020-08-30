#include "Entity.h"

Entity::Entity()
{
	defaultNumbersOfFrames = 0;
	defaultFrameSize.x = 0;
	defaultFrameSize.y = 0;
	defaultSPOSS.x = 0;
	defaultSPOSS.y = 0;
	width = 0;
	height = 0;
	posX = 0 - width / 2;
	posY = 0 - height / 2;
	accelerationX = 0;
	accelerationY = 0;
	speedH = 0.08;
	speedV = 0.08;
	scaleH = 1;
	scaleW = 1;
	doMoveH = NONE;
	doMoveV = NONE;
	frameTime = 500;
	currentAnimation = &IDLEAnimation;
}

void Entity::Init(std::string imageFileName, float x, float y, float w, float h)
{
	defaultNumbersOfFrames = 4;
	defaultFrameSize.x = w;
	defaultFrameSize.y = h;
	defaultSPOSS.x = 0;
	defaultSPOSS.y = 0;
	posX = x;
	posY = y;
	width = w;
	height = h;
	texture.loadFromFile("./res/img/" + imageFileName);
	sprite.setFrameTime(sf::seconds(frameTime));
	sprite.setLooped(true);
	sprite.play();
	sprite.setPosition(sf::Vector2f(posX, posY));
	SetAnimation(walkingAnimationDown, texture, defaultNumbersOfFrames, defaultFrameSize, defaultSPOSS);
	SetAnimation(IDLEAnimation, texture, 1, defaultFrameSize, defaultSPOSS);
	SetAnimation(walkingAnimationLeft, texture, defaultNumbersOfFrames, defaultFrameSize, sf::Vector2i(0,64));
	SetAnimation(walkingAnimationRight, texture, defaultNumbersOfFrames, defaultFrameSize, sf::Vector2i(0, 192));
	SetAnimation(walkingAnimationUp, texture, defaultNumbersOfFrames, defaultFrameSize, sf::Vector2i(0, 128));
}

void Entity::SetAnimation(AnimationManager & animation, sf::Texture & spriteSheet, int numpersOfFrames, sf::Vector2i frameSize,sf::Vector2i startPositionOnSpriteSheet)
{
	animation.setSpriteSheet(spriteSheet);
	int currentPosition = startPositionOnSpriteSheet.x;
	for (int i = 0; i < numpersOfFrames; i++)
	{
		animation.addFrame(sf::IntRect(currentPosition, startPositionOnSpriteSheet.y, frameSize.x, frameSize.y));
		currentPosition += frameSize.x;
	}
}

void Entity::Update(System * game, float time)
{
	HandleEvents(game);
	currentAnimation = &IDLEAnimation;

	if (doMoveH == LEFT)
	{
		accelerationX = -speedV;
		currentAnimation = &walkingAnimationLeft;
	}
	if (doMoveH == RIGHT)
	{
		accelerationX = speedV;
		currentAnimation = &walkingAnimationRight;
	}
	if (doMoveV == UP)
	{
		accelerationY = -speedV;
		currentAnimation = &walkingAnimationUp;
	}
	if (doMoveV == DOWN)
	{
		accelerationY = speedV;
		currentAnimation = &walkingAnimationDown;
	}

	if (doMoveH != NONE && doMoveV != NONE)
	{
		accelerationX = accelerationX * 0.75;
		accelerationY = accelerationY * 0.75;
	}

	posX += accelerationX * time;
	posY += accelerationY * time;
	accelerationX = 0;
	accelerationY = 0;
	sprite.play(*currentAnimation);
	sprite.setPosition(posX, posY);
	sprite.update(sf::seconds(time));
}

void Entity::HandleEvents(System * game)
{
	doMoveH = NONE;
	doMoveV = NONE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		doMoveV = UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		doMoveV = DOWN;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		doMoveH = LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		doMoveH = RIGHT;

	//exceptions
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		doMoveV = NONE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		doMoveH = NONE;
}

void Entity::Draw(System * game)
{
	game->GetWindow().draw(sprite);
}

sf::Vector2f Entity::getPosition()
{
	return sf::Vector2f(posX + width / 2, posY + height / 2);
}

sf::Vector2f Entity::getSize()
{
	return sf::Vector2f(width, height);
}

void Entity::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position.x - width / 2, position.y - height / 2);
}
