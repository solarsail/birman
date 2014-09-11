#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "configuration.hpp"
#include "entity.hpp"
#include "systems/map.hpp"
#include "systems/eventkey.hpp"
#include "command.hpp"
#include "systems/resources.hpp"

class Game {
	public:
		Game(const Configuration& conf, GameEntityPtr player);
		void setPlayer(GameEntityPtr player);
		int run();

	private:
		// FIXME: 应被事件处理系统取代
		void processEvents();
		void update(sf::Time t);

		sf::RenderWindow _window;
		sf::View _mainView;
		Map _map;
		GameEntityPtr _player;
		CommandSystem _cmdsystem;
};
