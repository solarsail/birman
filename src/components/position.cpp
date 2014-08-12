#include "components/position.hpp"

void PositionComponent::setWorldPos(float x, float y)
{
    this->setWorldPos(sf::Vector2f(x, y));
}

void PositionComponent::setWorldPos(const sf::Vector2f& pos)
{
    _world_pos = pos;
    _entity->notify("WorldPos", _world_pos);
    _entity->notify("ScreenPos", getScreenPos());
}

sf::Vector2f PositionComponent::getWorldPos() const
{
    return _world_pos;
}

sf::Vector2f PositionComponent::getScreenPos() const
{
    sf::Vector2f screen_pos = this->world2screen(_world_pos);
    screen_pos.y -= _z;
    return screen_pos;
}

void PositionComponent::setWorldZ(float z)
{
    _z = z;
    _entity->notify("WorldZ", _z);
}

float PositionComponent::getWorldZ() const
{
    return _z;
}

// Function to convert a world position to a screen (view) position
// ScreenX = 2*WorldX - 2*WorldY
// ScreenY = WorldX + WorldY
sf::Vector2f PositionComponent::world2screen(const sf::Vector2f& v)
{
    return sf::Vector2f(2.0f*v.x - 2.0f*v.y, v.x + v.y);
}

// Function to convert a screen (view) position to a world position
// WorldX = (ScreenX + 2*ScreenY)/4
// WorldY = (2*ScreenY - ScreenX)/4
sf::Vector2f PositionComponent::screen2world(const sf::Vector2f& v)
{
    return sf::Vector2f((v.x + 2.0f*v.y)/4.0f, (2.0f*v.y - v.x)/4.0f);
}
