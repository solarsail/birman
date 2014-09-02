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
	auto& textures = TextureHolder::get();
	auto player = GameEntityFactory::newEntity();
	auto pos = ComponentFactory::create<PositionComponent>();
	auto mov = ComponentFactory::create<MovableComponent>();
	auto sprite = ComponentFactory::create<SpriteComponent>();
	auto playerTexture = textures.get(TextureID::TestPlayer);
	playerTexture->setSmooth(true);
	player->attachComponent(pos);
	player->attachComponent(mov);
	player->attachComponent(sprite);
	player->setCategory(Category::Windowview);
	player->setProperty(Property::SpriteTexture, playerTexture);
    player->setProperty(Property::WorldPosition, sf::Vector2f(1600, 1600));
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

	auto& textures = TextureHolder::get();
	textures.load(TextureID::TestPlayer, "../assets/textures/player.png", sf::IntRect(32, 0, 32, 32));

	Game game(conf, loadPlayer());
	return game.run();
}

