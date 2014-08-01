#include <SFML/Graphics.hpp>
#include "components/texture.hpp"

TextureComponent::TextureComponent(TexturePtr texture)
    : _texture(texture)
{ }

TexturePtr TextureComponent::getUpdatedTexture()
{
    sf::Vector2f pos = _entity->getProperty("ScreenPosition");
    _texture->setPosition(pos);
    return _texture;
}

void TextureComponent::registerProperty()
{
    _entity->provideProperty("Texture", [this]() {
            return this->getUpdatedTexture();
            });
}
