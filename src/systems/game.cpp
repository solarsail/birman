#include "log/easylogging++.h"
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
#ifdef WITHOUT_COMMAND
        else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            Direction d = _player->getProperty(Property::Direction);
            int pressed = (event.type == sf::Event::KeyPressed)? 1 : -1;
#if !defined NDEBUG || defined _DEBUG
            const char* state = (event.type == sf::Event::KeyPressed)? "Pressed": "Released";
#endif
            switch (event.key.code) {
                case sf::Keyboard::W:
                    LOG(DEBUG) << "Event - Key " << state << ": W";
                    d.setNS(-pressed);
                    break;
                case sf::Keyboard::S:
                    LOG(DEBUG) << "Event - Key " << state << ": S";
                    d.setNS(pressed);
                    break;
                case sf::Keyboard::A:
                    LOG(DEBUG) << "Event - Key " << state << ": A";
                    d.setWE(-pressed);
                    break;
                case sf::Keyboard::D:
                    LOG(DEBUG) << "Event - Key " << state << ": D";
                    d.setWE(pressed);
                    break;
                default:
                    break;
            }
            _player->setProperty(Property::Direction, d);
        }
#else
		_cmdsystem.HandleEvent(event);
#endif
    }

}

void Game::update(sf::Time timeDelta)
{
    Direction d = _player->getProperty(Property::Direction);
    float speed = _player->getProperty(Property::Speed);
    sf::Vector2f v(0.f, 0.f);
    v.y += d.NS() * speed;
    v.x += d.WE() * speed;
    // 归一化
    v *= speed * util::invSqrt(v.x * v.x + v.y * v.y);

    if (d.code() != 0) {
        _player->setProperty(Property::AniIndex, d.code());
        _player->setProperty(Property::AniState, AniState::Play);
    } else {
        _player->setProperty(Property::AniState, AniState::Stop);
    }

    _player->setProperty(Property::AniPlayedTime, timeDelta);
    _player->setProperty(Property::Velocity, v);
    _player->setProperty(Property::MovementTime, timeDelta);
}

int Game::run()
{
    GameContext ctx = { _window, _mainView, _map };
    RenderSystem& renderer = RenderSystem::get();
    renderer.init(ctx, _player);
    renderer.registerObject(_player);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const auto TimePerFrame = sf::seconds(1.f / 60.f);

    while (_window.isOpen()) {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
#ifndef WITHOUT_COMMAND
			_cmdsystem.ProcessCmdQueue(_player);
#endif
            processEvents();
            update(TimePerFrame);
        }
        renderer.process(ctx);
    }

    return 0;
}

