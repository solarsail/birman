#include "animation.hpp"

AnimationData::AnimationData()
{ }

AnimationData::AnimationData(std::vector<sf::IntRect>&& frames)
{
    setFrames(std::move(frames));
}

void AnimationData::addFrame(sf::IntRect rect)
{
    _frames.push_back(rect);
}

void AnimationData::setFrames(std::vector<sf::IntRect>&& frames)
{
    _frames = frames;
}

/*
void AnimationData::setSpriteSheet(const sf::Texture& texture)
{
    _texture = &texture;
}

const sf::Texture* AnimationData::getSpriteSheet() const
{
    return _texture;
}
*/

std::size_t AnimationData::frameCount() const
{
    return _frames.size();
}

const sf::IntRect& AnimationData::getFrame(std::size_t n) const
{
    return _frames[n];
}
