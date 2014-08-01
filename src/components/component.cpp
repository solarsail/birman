#include "components/component.hpp"

Component::Component() {}

Component::~Component() {};

void Component::setEntity(GameEntityPtr entity)
{
    _entity = entity;
}

