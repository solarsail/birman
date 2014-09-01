#include "components/movable.hpp"

MovableComponent::MovableComponent() :
    _speed(0),
    _velocity(0, 0),
    _timeDelta(sf::Time::Zero)
{ }

void MovableComponent::setSpeed(float pixels)
{
    _speed = pixels;
    _entity->notify(Property::Speed);
}

void MovableComponent::setDirection(Direction d)
{
    _direction = d;
    _entity->notify(Property::Direction);
}

void MovableComponent::setVelocity(sf::Vector2f v)
{
    _velocity = v;
    _entity->notify(Property::Velocity);
}

void MovableComponent::setMovementTime(sf::Time t)
{
    _timeDelta = t;
    _entity->notify(Property::MovementTime);
}

float MovableComponent::getSpeed()
{
    return _speed;
}

Direction MovableComponent::getDirection()
{
    return _direction;
}

sf::Vector2f MovableComponent::getVelocity()
{
    return _velocity;
}

sf::Time MovableComponent::getMovementTime()
{
    return _timeDelta;
}

void MovableComponent::registerProperties()
{
    _entity->provideProperty(Property::Speed, [this]() { return getSpeed(); }, [this](Any v) { this->setSpeed(v); });
    _entity->provideProperty(Property::Direction, [this]() { return getDirection(); }, [this](Any v) { this->setDirection(v); });
    _entity->provideProperty(Property::Velocity, [this]() { return getVelocity(); }, [this](Any v) { this->setVelocity(v); });
    _entity->provideProperty(Property::MovementTime, [this]() { return getMovementTime(); }, [this](Any v) { this->setMovementTime(v); });
}
