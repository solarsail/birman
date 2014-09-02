#include <SFML/Graphics.hpp>
#include "components/sprite.hpp"

SpriteComponent::SpriteComponent()
{ }

void SpriteComponent::setTexture(TexturePtr t)
{
	_sprite.setTexture(*t, true);
    auto bounds = _sprite.getLocalBounds();
    _sprite.setOrigin(bounds.width / 2.f, bounds.height);
	_entity->notify(Property::Drawable);
}

sf::Vector2f SpriteComponent::getPosition() const
{
    return _sprite.getPosition();
}

void SpriteComponent::bindListeners()
{
    _entity->listen(Property::WorldPosition, [this](sf::Vector2f pos){ _sprite.setPosition(pos); });
}

void SpriteComponent::registerProperties()
{
	_entity->provideProperty(Property::Drawable, [this]() { return static_cast<sf::Drawable*>(&_sprite); }, nullptr);
	_entity->provideProperty(Property::ObjectTexture, nullptr, [this](Any v) { setTexture(v); });
}

bool operator <(const SpriteComponent& a, const SpriteComponent& b)
{
    auto thispos = a.getPosition();
    auto otherpos = b.getPosition();
    return thispos.y < otherpos.y;
}
