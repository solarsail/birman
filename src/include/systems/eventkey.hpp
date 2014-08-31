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
		void HandleEvent(sf::Event e);
private:
		bool TestEvent(MyKeys k,sf::Event e);
		static std::map<std::string,MyKeys> Keys;
		MyKeys key;
};