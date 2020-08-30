#include "AnimationManager.h"

AnimationManager::AnimationManager() : m_texture(NULL)
{

}

void AnimationManager::addFrame(sf::IntRect rect)
{
	m_frames.push_back(rect);
}

void AnimationManager::setSpriteSheet(const sf::Texture& texture)
{
	m_texture = &texture;
}

const sf::Texture* AnimationManager::getSpriteSheet() const
{
	return m_texture;
}

std::size_t AnimationManager::getSize() const
{
	return m_frames.size();
}

const sf::IntRect& AnimationManager::getFrame(std::size_t n) const
{
	return m_frames[n];
}