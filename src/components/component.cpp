#include "components/component.hpp"

Component::Component() {}

Component::~Component() {}

void Component::bindListeners() {}

void Component::registerProperties() {}

void Component::setEntity(GameEntityPtr entity)
{
    _entity = entity;
}

