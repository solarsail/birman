#include "entity.hpp"
#include "entityfactory.hpp"

std::shared_ptr<GameEntity> GameEntityFactory::newEntity()
{
    return std::make_shared<GameEntity>();
}

