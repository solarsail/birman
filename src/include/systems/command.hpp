#pragma once
#include <functional> 
#include <queue>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <bitset>

class GameEntity;

struct Command
{
	Command();
	std::function<void(GameEntity&,sf::Time)> action;
	unsigned int category;
};

class CommandQueue
{
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;
private:
	std::queue<Command> mQueue;
};