#include "context.hpp"
#include "systems/game.hpp"
#include "systems/render.hpp"
#include "utility.hpp"

Game::Game(const Configuration& conf, GameEntityPtr player) :
	_window(sf::VideoMode(conf.get(ConfigItem::WindowWidth),
						  conf.get(ConfigItem::WindowHeight)),
		   	conf.get(ConfigItem::WindowTitle).as<std::string>()),
	_mainView(sf::FloatRect(0, 0, 
							conf.get(ConfigItem::WindowWidth).as<unsigned>(),
							conf.get(ConfigItem::WindowHeight).as<unsigned>())),
	_player(player)
{
	std::string mapName = conf.get(ConfigItem::MapName).as<std::string>();
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
		//else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
         //   Direction d = _player->getProperty(Property::Direction);
		//	switch (event.key.code) {
		//		case sf::Keyboard::W:
  //                  d.up = (event.type == sf::Event::KeyPressed);
		//			break;
		//		case sf::Keyboard::S:
  //                  d.down = (event.type == sf::Event::KeyPressed);
		//			break;
		//		case sf::Keyboard::A:
  //                  d.left = (event.type == sf::Event::KeyPressed);
		//			break;
		//		case sf::Keyboard::D:
  //                  d.right = (event.type == sf::Event::KeyPressed);
		//			break;
		//		default:
		//			break;
		//	}
		//	_player->setProperty(Property::Direction, d);
		//}
		_systemkey.HandleEvent(event,_cmdqueue,_cmdset);
	}

}

float InvSqrt (float x) {
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i>>1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf*x*x);
    return x;
}

void Game::update(sf::Time timeDelta)
{
    Direction d = _player->getProperty(Property::Direction);
    float speed = _player->getProperty(Property::Speed);
    sf::Vector2f v(0.f, 0.f);
    if (d.up)
        v.y -= speed;
    if (d.down)
        v.y += speed;
    if (d.left)
        v.x -= speed;
    if (d.right)
        v.x += speed;
    // 归一化
    v *= speed * InvSqrt(v.x * v.x + v.y * v.y);

    _player->setProperty(Property::Velocity, v);
    _player->setProperty(Property::MovementTime, timeDelta);
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
            update(TimePerFrame);
        }
		if(!_cmdqueue.isEmpty())
		{
			while(!_cmdqueue.isEmpty())
			{
				Command tmp = _cmdqueue.pop();
				_player->onCommand(tmp);
			}	
		}
        renderer.process(ctx);
    }

    return 0;
}

