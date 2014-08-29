#pragma once
#include <SFML/Graphics.hpp>


enum InputType
{
    KeyboardInput,
    MouseInput
};

struct MyKeys
{
    InputType myInputType;
    sf::Event::EventType myEventType;
    sf::Keyboard::Key myKeyCode;
    sf::Mouse::Button myMouseButton;
};

class Systemkeys
{
	public:
		Systemkeys();
		std::map<std::string,MyKeys> Keys;
		MyKeys key;
};