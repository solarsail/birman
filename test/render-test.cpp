#include "context.hpp"
#include "components/position.hpp"
#include "componentfactory.hpp"
#include "entityfactory.hpp"
#include "systems/map.hpp"
#include "systems/render.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(192, 128), "Test Map");
    sf::View view(sf::FloatRect(0, 0, 192, 128));
    GameContext ctx { window, view };

	auto map = MapLoader::loadTestMap();
	auto player = GameEntityFactory::newEntity();
	auto pos = ComponentFactory::create<PositionComponent>();
	player->attachComponent(pos);
    player->setProperty(Property::WorldPosition, sf::Vector2f(256, 128));

    RenderSystem& renderer = RenderSystem::get();
    renderer.setMap(map);
    renderer.init(ctx, player);

	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				sf::Vector2f pos = player->getProperty(Property::WorldPosition);
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
				player->setProperty(Property::WorldPosition, pos);
			}
		}

        renderer.process(ctx);
	}

	return 0;
}

