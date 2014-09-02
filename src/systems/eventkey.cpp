#include <iostream>
#include "systems/eventkey.hpp"
#include "systems/command.hpp"

Systemkeys::Systemkeys()
{
	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::A;
	Keys["left"] = key;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::D;
	Keys["right"] = key;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::W;
	Keys["up"] = key;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::S;
	Keys["down"] = key;
}

bool Systemkeys::TestEvent(MyKeys k,sf::Event e)
{
	//handle mouse event
	if (k.myInputType == InputType::MouseInput &&
		k.myEventType == e.type && 
		k.myMouseButton == e.mouseButton.button)
	{
		return true;
	}
	
	//handle keyboard event
	if (k.myInputType == InputType::KeyboardInput &&
		k.myEventType == e.type &&
		k.myKeyCode == e.key.code)
	{
		return true;
	}

	return false;
}

void Systemkeys::HandleEvent(sf::Event e,CommandQueue& queue,CommandSet& set)
{
	if (TestEvent(Keys["left"],e))
	{
		queue.push(set.getCommand("moveleft"));
	}
	if (TestEvent(Keys["right"],e))
	{
		queue.push(set.getCommand("moveright"));
	}
	if (TestEvent(Keys["up"],e))
	{
		queue.push(set.getCommand("moveup"));
	}
	if (TestEvent(Keys["down"],e))
	{
		queue.push(set.getCommand("movedown"));
	}
}

std::map<std::string,MyKeys> Systemkeys::Keys;