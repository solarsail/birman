#include "components/component.hpp"
#include "entity.hpp"


GameEntity::GameEntity() { }

void GameEntity::attachComponent(std::shared_ptr<Component> c)
{
    _components.insert(c);
    c->setEntity(shared_from_this());
    c->registerProperty();
}

Any GameEntity::getProperty(const std::string& id)
{
    assert(!_map.empty());
    auto found = _map.find(id);
    assert(found != _map.end());
    return found->second();
}

void GameEntity::provideProperty(const std::string& id, PropertyCallback callback)
{
    auto result = _map.insert(std::make_pair(id, callback));
    assert(result.second);  // 保证新值被插入而不是返回原有值
}

