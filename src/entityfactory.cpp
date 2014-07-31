#include "entity.hpp"
#include "entityfactory.hpp"

std::shared_ptr<GameEntity> newEntity()
{
    return std::make_shared<GameEntity>();
}

