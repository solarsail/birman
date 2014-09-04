#include <iostream>
#include "systems/eventkey.hpp"
#include "systems/command.hpp"

Systemkeys::Systemkeys()
{
	MyKeys key;
	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::A;
	key.myMouseButton = 0;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("moveleftpressed"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyReleased;
	key.myKeyCode = sf::Keyboard::A;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("moveleftreleased"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::D;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("moverightpressed"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyReleased;
	key.myKeyCode = sf::Keyboard::D;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("moverightreleased"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::W;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("moveuppressed"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyReleased;
	key.myKeyCode = sf::Keyboard::W;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("moveupreleased"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::S;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("movedownpressed"));
	};
	Keys[*(int*)&(key)] = tmpaction;

	key.myInputType = InputType::KeyboardInput;
	key.myEventType = sf::Event::KeyReleased;
	key.myKeyCode = sf::Keyboard::S;
	tmpaction = [](CommandQueue& queue, CommandSet& set)
	{
		queue.push(set.getCommand("movedownreleased"));
	};
	Keys[*(int*)&(key)] = tmpaction;

}


void Systemkeys::HandleEvent(sf::Event e,CommandQueue& queue,CommandSet& set)
{
	MyKeys tmp;
	std::map<int, std::function<void(CommandQueue&, CommandSet&)>>::iterator it;
	if ((e.type == sf::Event::KeyPressed) || (e.type == sf::Event::KeyReleased))
	{
		tmp.myEventType = e.type;
		tmp.myInputType = InputType::KeyboardInput;
		tmp.myKeyCode = e.key.code;
		tmp.myMouseButton = 0;
		it = Keys.find(*(int*)(&tmp));
		if (it != Keys.end())
		{
			it->second(queue,set);
		}
	}

	if ((e.type == sf::Event::MouseButtonPressed) || (e.type == sf::Event::MouseButtonReleased))
	{
		 
	}
}

std::map<int, std::function<void(CommandQueue&, CommandSet&)>> Keys;