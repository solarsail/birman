#include "context.hpp"
#include "components/position.hpp"
#include "componentfactory.hpp"
#include "configuration.hpp"
#include "entityfactory.hpp"
#include "systems/game.hpp"
#include "systems/map.hpp"
#include "systems/render.hpp"

GameEntityPtr loadPlayer()
{
	auto player = GameEntityFactory::newEntity();
	auto pos = ComponentFactory::create<PositionComponent>();
	player->attachComponent(pos);
    player->setProperty(Property::WorldPosition, sf::Vector2f(1600, 1600));

	return player;
}

int main()
{
	Configuration conf;
	conf.set(ConfigItem::MapName, std::string("TestMap"));
	conf.set(ConfigItem::WindowWidth, 480U);
	conf.set(ConfigItem::WindowHeight, 320U);
	conf.set(ConfigItem::WindowTitle, std::string("Map Render Test"));

	Game game(conf, loadPlayer());
	return game.run();
}

