#include "log/easylogging++.h"
#include "animation.hpp"
#include "context.hpp"
#include "components/position.hpp"
#include "components/movable.hpp"
#include "components/animated-sprite.hpp"
#include "componentfactory.hpp"
#include "configuration.hpp"
#include "entityfactory.hpp"
#include "systems/game.hpp"
#include "systems/map.hpp"
#include "systems/render.hpp"
#include "systems/command.hpp"
#include "systems/eventkey.hpp"
#include "utility.hpp"

_INITIALIZE_EASYLOGGINGPP

GameEntityPtr loadPlayer()
{
	auto& textures = TextureHolder::get();
	auto player = GameEntityFactory::newEntity();
	auto pos = ComponentFactory::create<PositionComponent>();
	auto mov = ComponentFactory::create<MovableComponent>();
//	auto sprite = ComponentFactory::create<SpriteComponent>();
	auto sprite = ComponentFactory::create<AnimatedSpriteComponent>();
	auto playerTexture = textures.get(TextureID::TestPlayer);
	playerTexture->setSmooth(true);
    // 构建动画�?
    AnimationData south({{32, 0, 32, 32}, {64, 0, 32, 32}, {32, 0, 32, 32}, {0, 0, 32, 32}});
    AnimationData west({{32, 32, 32, 32}, {64, 32, 32, 32}, {32, 32, 32, 32}, {0, 32, 32, 32}});
    AnimationData east({{32, 64, 32, 32}, {64, 64, 32, 32}, {32, 64, 32, 32}, {0, 64, 32, 32}});
    AnimationData north({{32, 96, 32, 32}, {64, 96, 32, 32}, {32, 96, 32, 32}, {0, 96, 32, 32}});
    AnimationData sw({{128, 0, 32, 32}, {160, 0, 32, 32}, {128, 0, 32, 32}, {96, 0, 32, 32}});
    AnimationData nw({{128, 32, 32, 32}, {160, 32, 32, 32}, {128, 32, 32, 32}, {96, 32, 32, 32}});
    AnimationData se({{128, 64, 32, 32}, {160, 64, 32, 32}, {128, 64, 32, 32}, {96, 64, 32, 32}});
    AnimationData ne({{128, 96, 32, 32}, {160, 96, 32, 32}, {128, 96, 32, 32}, {96, 96, 32, 32}});
    sprite->addAnimation(Direction::SOUTH, south);
    sprite->addAnimation(Direction::WEST , west);
    sprite->addAnimation(Direction::NORTH, north);
    sprite->addAnimation(Direction::EAST , east);
    sprite->addAnimation(Direction::SW   , sw);
    sprite->addAnimation(Direction::NW   , nw);
    sprite->addAnimation(Direction::NE   , ne);
    sprite->addAnimation(Direction::SE   , se);

	player->attachComponent(pos);
	player->attachComponent(mov);
	player->attachComponent(sprite);
	player->setCategory(Category::Windowview);
	// 务必最先初始化材质
	player->setProperty(Property::ObjectTexture, playerTexture);
	player->setProperty(Property::AniIndex, /*Direction::SOUTH*/(unsigned char)0x10U);
    player->setProperty(Property::WorldPosition, sf::Vector2f(1600, 1600));
	player->setProperty(Property::Speed, 64.f);

	return player;
}

void logSetup()
{
    el::Configurations defaultConf;
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime [%levshort] [%func|%fbase:%line] %msg");
    el::Loggers::reconfigureLogger("default", defaultConf);
}

int main()
{
    logSetup();
	Configuration conf;
	conf.set(ConfigItem::MapName, std::string("TestMap"));
	conf.set(ConfigItem::WindowWidth, 480U);
	conf.set(ConfigItem::WindowHeight, 320U);
	conf.set(ConfigItem::WindowTitle, std::string("Map Render Test"));

	auto& textures = TextureHolder::get();
	textures.load(TextureID::TestPlayer, "../assets/textures/player.png");

	Game game(conf, loadPlayer());
	return game.run();
}

