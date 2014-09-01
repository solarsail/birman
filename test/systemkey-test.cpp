#include "context.hpp"
#include "components/position.hpp"
#include "componentfactory.hpp"
#include "entityfactory.hpp"
#include "systems/map.hpp"
#include "systems/render.hpp"
#include "systems/command.hpp"
#include "systems/eventkey.hpp"

int main()
{

	sf::RenderWindow window(sf::VideoMode(480, 320), "Test Map");
    sf::View view(sf::FloatRect(0, 0, 480, 320));
    GameContext ctx = { window, view };


	auto map = MapLoader::loadTestMap();
	auto player = GameEntityFactory::newEntity();
	auto pos = ComponentFactory::create<PositionComponent>();
	player->attachComponent(pos);
    player->setProperty(Property::WorldPosition, sf::Vector2f(1600, 1600));
	player->setCategory(Category::Windowview);

    RenderSystem& renderer = RenderSystem::get();
    renderer.setMap(map);
    renderer.init(ctx, player);

	Systemkeys systemkey;
	CommandQueue cmdqueue;
	CommandSet cmdset;

	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			systemkey.HandleEvent(event,cmdqueue,cmdset);
		}

		if(!cmdqueue.isEmpty())
		{
			while(!cmdqueue.isEmpty())
			{
				Command tmp = cmdqueue.pop();
				player->onCommand(tmp);
			}	
		}
        renderer.process(ctx);
	}

	return 0;
}

