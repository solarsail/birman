#include <SFML/Graphics.hpp>
#include "components/sprite.hpp"

SpriteComponent::SpriteComponent(SpritePtr sprite)
    : _sprite(sprite)
{
    auto bounds = _sprite->getLocalBounds();
    _sprite->setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

sf::Vector2f SpriteComponent::getCenter()
{
    return _sprite->getPosition();
}

void SpriteComponent::bindListeners()
{
    _entity->listen("ScreenPos", [this](sf::Vector2f pos){ this->_sprite->setPosition(pos); });
}

void SpriteComponent::registerProperties()
{
    _entity->provideProperty(Property::Sprite, [this]() { return _sprite; }, nullptr);
}

bool operator <(const SpriteComponent::SpritePtr& a, const SpriteComponent::SpritePtr& b)
{
    auto thispos = a->getPosition();
    auto otherpos = b->getPosition();
    return thispos.x + thispos.y < otherpos.x + otherpos.y;
}
