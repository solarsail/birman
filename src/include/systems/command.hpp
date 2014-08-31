#pragma once
#include <functional> 
#include <queue>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "category.hpp"

class GameEntity;

struct Command
{
	typedef std::function<void(GameEntity&)> Action;

	//Command();
	//Command(Category::Type type, Action a);
	//Command(const CategorySet& types, Action a);

	Action action;
	CategorySet categoryMask;
};

class CommandQueue
{
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;
private:
	static std::queue<Command> _mQueue;
};

class CommandSet
{
public:
	CommandSet();
	void setCommand(std::string,Command);
private:
	Command cmd;
	static std::map<std::string,Command> _commandset;
};