#include "systems/map.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(128, 128), "Test Map");

	auto map = MapLoader::loadTestMap();
	MapSlice slice(8, 8, map);
	slice.buildDrawable(0, 0);

	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		// draw the map
		window.clear();
		window.draw(slice);
		window.display();
	}

	return 0;
}
