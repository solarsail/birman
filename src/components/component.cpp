#include "components/component.hpp"

Component::Component() {}

void Component::registerProperty(std::shared_ptr<GameEntity> entity)
{
    _entity = entity;
}

Component::~Component() {};

