#pragma once
#include <SFML/Graphics.hpp>

class CommandQueue;
class CommandSet;

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
		void HandleEvent(sf::Event,CommandQueue&,CommandSet&);
private:
		bool TestEvent(MyKeys k,sf::Event e);
		static std::map<std::string,MyKeys> Keys;
		MyKeys key;
};