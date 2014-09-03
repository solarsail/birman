#include "systems/command.hpp"
#include "entity.hpp"
#include "components/component.hpp"
#include "utility.hpp"

void CommandQueue::push(const Command& command)
{
	_mQueue.push(command);
}

Command CommandQueue::pop()
{
	Command tmp = _mQueue.front();
	_mQueue.pop();
	return tmp;
}

bool CommandQueue::isEmpty()
{
	return _mQueue.empty();
}

void CommandSet::setCommand(std::string str,Command command)
{
	_commandset[str] = command;
}

Command CommandSet::getCommand(std::string name)
{
	return _commandset[name];
}

CommandSet::CommandSet()
{
	cmd.categoryMask.addType(Category::Windowview);
	cmd.action =  [](GameEntity& entity)
	{
		Direction d = entity.getProperty(Property::Direction);
		d.setNS(-1);
		entity.setProperty(Property::Direction, d);
	};
	setCommand("moveup",cmd);

	cmd.categoryMask.addType(Category::Windowview);
	cmd.action =  [](GameEntity& entity)
	{
		Direction d = entity.getProperty(Property::Direction);
		d.setNS(1);
		entity.setProperty(Property::Direction, d);
	};
	setCommand("movedown",cmd);

	cmd.categoryMask.addType(Category::Windowview);
	cmd.action =  [](GameEntity& entity)
	{
		Direction d = entity.getProperty(Property::Direction);
		d.setWE(1);
		entity.setProperty(Property::Direction, d);
	};
	setCommand("moveright",cmd);

	cmd.categoryMask.addType(Category::Windowview);
	cmd.action =  [](GameEntity& entity)
	{
		Direction d = entity.getProperty(Property::Direction);
		d.setWE(-1);
		entity.setProperty(Property::Direction, d);
	};
	setCommand("moveleft",cmd);
}

std::queue<Command> CommandQueue::_mQueue;
std::map<std::string,Command> CommandSet::_commandset;

