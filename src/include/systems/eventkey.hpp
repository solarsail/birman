#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class CommandQueue;
class CommandSet;

enum InputType
{
    KeyboardInput,
    MouseInput
};

struct MyKeys
{
    unsigned char myInputType;
    unsigned char myEventType;
    unsigned char myKeyCode;
    unsigned char myMouseButton;
};

class Systemkeys
{
public:
    Systemkeys();
    void HandleEvent(sf::Event, CommandQueue &, CommandSet &);
private:
    std::function<void(CommandQueue &, CommandSet &)> tmpaction;
    std::map<int, std::function<void(CommandQueue &, CommandSet &)>> Keys;
};