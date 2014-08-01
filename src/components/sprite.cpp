#include <SFML/Graphics.hpp>
#include "components/sprite.hpp"

SpriteComponent::SpriteComponent(SpritePtr sprite)
    : _sprite(sprite)
{ }

sf::Sprite SpriteComponent::getUpdatedSpirte()
{
    sf::Vector2f pos = _entity->getProperty("ScreenPosition");
    _sprite->setPosition(pos);
    return *_sprite;
}

void SpriteComponent::registerProperty()
{
    _entity->provideProperty("Spirte", [this]() {
            return this->getUpdatedSprite();
            });
}
