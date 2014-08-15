#include "components/component.hpp"
#include "entity.hpp"


GameEntity::GameEntity() { }

void GameEntity::attachComponent(std::shared_ptr<Component> c)
{
    _components.insert(c);
    c->setEntity(shared_from_this());
    c->registerProperties();
    c->bindListeners();
}

void GameEntity::notify(const std::string& id)
{
    assert(!_bindings.empty());
    auto found = _bindings.find(id);
    for (ValueConsumer& func : found->second.second) {
        func(found->second.first());
    }
}

void GameEntity::listen(const std::string& id, ValueConsumer function)
{
    _bindings[id].second.push_back(function);
}

Any GameEntity::getProperty(const std::string& id)
{
    assert(!_bindings.empty());
    auto found = _bindings.find(id);
    assert(found != _bindings.end());
    return found->second.first();
}

void GameEntity::provideProperty(const std::string& id, ValueProvider callback)
{
    auto result = _bindings.insert(std::make_pair(id, std::make_pair(callback, std::vector<ValueConsumer>())));
    assert(result.second);  // 确认插入成功，防止重复插入
}
