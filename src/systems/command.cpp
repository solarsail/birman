#include "systems/command.hpp"
#include "entity.hpp"
#include "components/component.hpp"

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
		sf::Vector2f pos = entity.getProperty(Property::WorldPosition);
		pos.y -= 5;
		entity.setProperty(Property::WorldPosition, pos);
	};
	setCommand("moveup",cmd);
}

std::queue<Command> CommandQueue::_mQueue;
std::map<std::string,Command> CommandSet::_commandset;

