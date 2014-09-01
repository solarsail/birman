#include "components/position.hpp"

void PositionComponent::setWorldPos(float x, float y)
{
    this->setWorldPos(sf::Vector2f(x, y));
}

void PositionComponent::setWorldPos(const sf::Vector2f& pos)
{
    _world_pos = pos;
    _entity->notify(Property::WorldPosition);
}

sf::Vector2f PositionComponent::getWorldPos() const
{
    return _world_pos;
}

void PositionComponent::setWorldZ(float z)
{
    _z = z;
    _entity->notify(Property::WorldZ);
}

float PositionComponent::getWorldZ() const
{
    return _z;
}

void PositionComponent::registerProperties()
{
    _entity->provideProperty(Property::WorldPosition, [this]() { return getWorldPos(); }, [this](Any v) { this->setWorldPos(v); });
}

void PositionComponent::bindListeners()
{
    _entity->listen(Property::MovementTime, [this](sf::Time t) {
            auto pos = _world_pos;
            sf::Vector2f v = _entity->getProperty(Property::Velocity);
            pos += v * t.asSeconds();
            setWorldPos(pos);
    });
}
