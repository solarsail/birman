#include "context.hpp"
#include "components/position.hpp"
#include "components/movable.hpp"
#include "componentfactory.hpp"
#include "configuration.hpp"
#include "entityfactory.hpp"
#include "systems/game.hpp"
#include "systems/map.hpp"
#include "systems/render.hpp"
#include "systems/command.hpp"
#include "systems/eventkey.hpp"

GameEntityPtr loadPlayer()
{
	auto player = GameEntityFactory::newEntity();
	auto pos = ComponentFactory::create<PositionComponent>();
	auto mov = ComponentFactory::create<MovableComponent>();
	player->attachComponent(pos);
	player->attachComponent(mov);
    player->setProperty(Property::WorldPosition, sf::Vector2f(1600, 1600));
	player->setCategory(Category::Windowview);
	player->setProperty(Property::Speed, 64.f);

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

