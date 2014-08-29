#include "systems/eventkey.hpp"

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