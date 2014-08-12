#include "components/component.hpp"
#include "entity.hpp"


GameEntity::GameEntity() { }

void GameEntity::attachComponent(std::shared_ptr<Component> c)
{
    _components.insert(c);
    c->setEntity(shared_from_this());
    c->bindListeners();
}

void GameEntity::notify(const std::string& id, Any value)
{
    for (ValueConsumer& func : _bindings[id]) {
        func(value);
    }
}

void GameEntity::listen(const std::string& id, ValueConsumer function)
{
    _bindings[id].push_back(function);
}
