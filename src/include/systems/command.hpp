#pragma once
#include <functional> 
#include <queue>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "category.hpp"
#include "eventkey.hpp"

class GameEntity;

struct Command
{
	typedef std::function<void(GameEntity&)> Action;
	Action action;
	CategorySet categoryMask;
};

class CommandQueue
{
public:
	static void push(const Command& command);
	static Command pop();
	static bool isEmpty();
private:
	static std::queue<Command> _mQueue;
};

class CommandSet
{
public:
	CommandSet();
	void setCommand(std::string,Command);
	Command getCommand(std::string);
private:
	Command cmd;
	static std::map<std::string,Command> _commandset;
};

class CommandSystem
{
public:
	void HandleEvent(sf::Event);
	void ProcessCmdQueue(GameEntityPtr);
private:
	Systemkeys _systemkey;
	CommandQueue _cmdqueue;
	CommandSet _cmdset;
};