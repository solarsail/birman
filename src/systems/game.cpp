#include "context.hpp"
#include "systems/game.hpp"
#include "systems/render.hpp"

Game::Game(const Configuration& conf, GameEntityPtr player) :
	_window(sf::VideoMode(conf.get(ConfigItem::WindowWidth),
						  conf.get(ConfigItem::WindowHeight)),
		   	conf.get(ConfigItem::WindowTitle).as<std::string>()),
	_mainView(sf::FloatRect(0, 0, 
							conf.get(ConfigItem::WindowWidth).as<unsigned>(),
							conf.get(ConfigItem::WindowHeight).as<unsigned>())),
	_player(player)
{
	std::string mapName = conf.get(ConfigItem::MapName);
	if (mapName == "TestMap")
		_map = MapLoader::loadTestMap();
	else
		_map = MapLoader::load(mapName);

}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event)) {
		if(event.type == sf::Event::Closed)
			_window.close();
		else if (event.type == sf::Event::KeyPressed) {
			sf::Vector2f pos = _player->getProperty(Property::WorldPosition);
			switch (event.key.code) {
				case sf::Keyboard::W:
					pos.y -= 5;
					break;
				case sf::Keyboard::S:
					pos.y += 5;
					break;
				case sf::Keyboard::A:
					pos.x -= 5;
					break;
				case sf::Keyboard::D:
					pos.x += 5;
					break;
				default:
					break;
			}
			_player->setProperty(Property::WorldPosition, pos);
		}
	}

}

int Game::run()
{
	GameContext ctx = { _window, _mainView, _map };
	RenderSystem& renderer = RenderSystem::get();
	renderer.init(ctx, _player);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const auto TimePerFrame = sf::seconds(1.f / 60.f);

	while (_window.isOpen()) {
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
		}

		renderer.process(ctx);
	}

	return 0;
}

