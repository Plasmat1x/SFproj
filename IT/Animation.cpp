#include "Animation.h"
#include <iostream>

void AnimationManager::load_animation(std::string anim_name, sf::Vector2f size, int line, int frames, bool flipp)
{
	AnimationPlaylist playlist;
	for (int i = 0; i < frames; i++)
	{
		sf::IntRect rect;
		rect.top = line * size.y;
		rect.height = size.y;
		if (!flipp)
		{
			rect.left = size.x * i;
			rect.width = size.x;
		}
		else
		{
			rect.left = size.x * i + size.x;
			rect.width = -size.x;
		}

		playlist.frames.push_back(rect);
	}

	animations.emplace(anim_name, playlist);
}

AnimationPlaylist AnimationManager::getAnimation(std::string anim_name)
{
	return animations.at(anim_name);
}

const std::map<std::string, AnimationPlaylist>& AnimationManager::getAnimMap()
{
	return animations;
}

void Animation::init(float speed)
{
	this->speed = speed;
	this->frame = 0;
}

void Animation::play(sf::Sprite* sprite, AnimationPlaylist animation)
{
	if (frame >= animation.frames.size() - 1)
	{
		frame = 0;
	}
	frame += speed;
	sprite->setTextureRect(animation.frames[int(frame)]);
}

void Animation::reset()
{
	frame = 0;
}