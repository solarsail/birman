#pragma once

#include <SFML/Graphics.hpp>
#include "systems/map.hpp"

struct GameContext {
    sf::RenderWindow& window;
    sf::View& mainView;
	Map& map;
};
