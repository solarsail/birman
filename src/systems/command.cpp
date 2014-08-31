#include "systems/command.hpp"

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

bool CommandQueue::isEmpty() const
{
	return _mQueue.empty();
}

void CommandSet::setCommand(std::string str,Command command)
{
	_commandset[str] = command;
}

CommandSet::CommandSet()
{

}

std::queue<Command> CommandQueue::_mQueue;
std::map<std::string,Command> CommandSet::_commandset;

