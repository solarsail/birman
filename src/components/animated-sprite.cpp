#include "components/animated-sprite.hpp"

AnimatedSpriteComponent::AnimatedSpriteComponent(sf::Time frameTime, bool paused, bool looped) :
        _currentAni(nullptr), _frameTime(frameTime), _currentFrame(0),
        _paused(paused), _looped(looped)
{ }

void AnimatedSpriteComponent::addAnimation(Direction::CodeType index, const AnimationData& ani)
{
    auto result = _animations.insert(std::make_pair(index, ani));
    assert(result.second);
}

void AnimatedSpriteComponent::setLoop(bool loop)
{
    _looped = loop;
}

void AnimatedSpriteComponent::setFrameTime(sf::Time t)
{
    _frameTime = t;
}

void AnimatedSpriteComponent::setFrame(size_t frame)
{
    const sf::IntRect& rect = _currentAni->getFrame(frame);
    _sprite.setTextureRect(rect);
	_sprite.setOrigin(rect.width / 2, rect.height);
}

void AnimatedSpriteComponent::setState(AniState s)
{
    if (s == AniState::Play) {
        _paused = false;
        setFrame(_currentFrame);
    } else if (s == AniState::Pause) {
        _paused = true;
    } else {    // AniState::Stop
        _paused = true;
        _currentFrame = 0;
        _currentTime = sf::Time::Zero;
        setFrame(0);
    }
}

void AnimatedSpriteComponent::setTexture(std::shared_ptr<sf::Texture> t)
{
	_sprite.setTexture(*t);
	_entity->notify(Property::Drawable);
}

void AnimatedSpriteComponent::update(sf::Time deltaTime)
{
    if (!_paused && _currentAni) {
        _currentTime += deltaTime;
        if (_currentTime > _frameTime) {
            //_currentTime = sf::microseconds(_currentTime.asMicroseconds() % _frameTime.asMicroseconds());
            _currentTime -= _frameTime;
            ++_currentFrame;
            if (_currentFrame == _currentAni->frameCount()) {
                _currentFrame = 0;
                _paused = !_looped;
            }
            setFrame(_currentFrame);
        }
    }
}

void AnimatedSpriteComponent::useAnimation(Direction::CodeType index)
{
    _currentAni = &(_animations.at(index));
	setFrame(_currentFrame);
}

void AnimatedSpriteComponent::registerProperties()
{
    _entity->provideProperty(Property::Drawable, [this]() { return static_cast<sf::Drawable*>(&_sprite); }, nullptr);
    _entity->provideProperty(Property::AniState, nullptr, [this](Any v) { setState(v); });
    _entity->provideProperty(Property::AniIndex, nullptr, [this](Any v) { useAnimation(v); });
	_entity->provideProperty(Property::AniPlayedTime, nullptr, [this](Any v) { update(v); });
	_entity->provideProperty(Property::ObjectTexture, nullptr, [this](Any v) { setTexture(v); });
}

void AnimatedSpriteComponent::bindListeners()
{
    _entity->listen(Property::WorldPosition, [this](sf::Vector2f pos){ _sprite.setPosition(pos); });
}
