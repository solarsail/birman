#include "components/component.hpp"
#include "systems/command.hpp"
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
	auto listeners = std::get<2>(found->second);
	auto getter = std::get<0>(found->second);
	for (ValueConsumer& func : listeners) {
		func(getter());
	}
}

void GameEntity::listen(const std::string& id, ValueConsumer function)
{
	std::get<2>(_bindings[id]).push_back(function);
}

Any GameEntity::getProperty(const std::string& id)
{
	assert(!_bindings.empty());
	auto found = _bindings.find(id);
	assert(found != _bindings.end());
	return std::get<0>(found->second)();
}

void GameEntity::setProperty(const std::string& id, Any value)
{
	assert(!_bindings.empty());
	auto found = _bindings.find(id);
	assert(found != _bindings.end());
	auto setter = std::get<1>(found->second);
	assert(setter);
	setter(value);
}

void GameEntity::provideProperty(const std::string& id, ValueProvider getter, ValueConsumer setter)
{
	auto found = _bindings.find(id);
    if (found == _bindings.end())
	    _bindings.insert(std::make_pair(id, std::make_tuple(getter, setter, std::vector<ValueConsumer>())));
    else {
        std::get<0>(found->second) = getter;
        std::get<1>(found->second) = setter;
    }
}

void GameEntity::onCommand(Command& command)
{
	if(command.categoryMask.hasType(_category))
	{
		command.action(*this);
	} 
}

void GameEntity::setCategory(Category::Type type)
{
	_category = type;
}
