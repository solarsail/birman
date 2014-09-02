#include "components/animated-sprite.hpp"

AnimatedSpriteComponent::AnimatedSpriteComponent(sf::Time frameTime, bool paused, bool looped) :
        _currentAni(nullptr), _frameTime(frameTime), _currentFrame(0),
        _paused(paused), _looped(looped), _texture(nullptr)
{ }

void AnimatedSpriteComponent::addAnimation(unsigned index, const AnimationData& ani)
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
    sf::IntRect rect = _currentAni->getFrame(frame);

    _vertices[0].position = sf::Vector2f(0.f, 0.f);
    _vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
    _vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
    _vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

    float left = static_cast<float>(rect.left) + 0.0001f;
    float right = left + static_cast<float>(rect.width);
    float top = static_cast<float>(rect.top);
    float bottom = top + static_cast<float>(rect.height);

    _vertices[0].texCoords = sf::Vector2f(left, top);
    _vertices[1].texCoords = sf::Vector2f(left, bottom);
    _vertices[2].texCoords = sf::Vector2f(right, bottom);
    _vertices[3].texCoords = sf::Vector2f(right, top);
}

void AnimatedSpriteComponent::setState(AniState s)
{
    if (s == AniState::Play) {
        _currentFrame = 0;
        _currentTime = sf::Time::Zero;
        setFrame(0);
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
	_texture = t;
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

void AnimatedSpriteComponent::useAnimation(unsigned index)
{
    _currentAni = &(_animations.at(index));
}

sf::FloatRect AnimatedSpriteComponent::getLocalBounds() const
{
    sf::IntRect rect = _currentAni->getFrame(_currentFrame);

    float width = static_cast<float>(std::abs(rect.width));
    float height = static_cast<float>(std::abs(rect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSpriteComponent::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void AnimatedSpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_currentAni && _texture)
    {
        states.transform *= getTransform();
        states.texture = _texture.get();
        target.draw(_vertices, 4, sf::Quads, states);
    }
}

void AnimatedSpriteComponent::registerProperties()
{
    _entity->provideProperty(Property::Drawable, [this]() { return static_cast<sf::Drawable*>(this); }, nullptr);
    _entity->provideProperty(Property::AniState, nullptr, [this](Any v) { setState(v); });
    _entity->provideProperty(Property::AniIndex, nullptr, [this](Any v) { useAnimation(v); });
	_entity->provideProperty(Property::ObjectTexture, nullptr, [this](Any v) { setTexture(v); });
}

void AnimatedSpriteComponent::bindListeners()
{
    _entity->listen(Property::WorldPosition, [this](sf::Vector2f pos){ setPosition(pos); });
}
