#include <TGUI/TGUI.hpp>
#include <String>

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	tgui::Gui gui(window);

	// Load the font (you should check the return value to make sure that it is loaded)
	gui.setGlobalFont("DejaVuSans.ttf");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Pass the event to all the widgets (if there would be widgets)
			gui.handleEvent(event);
		}

		window.clear();

		// Draw all created widgets
		gui.draw();

		window.display();
	}

	return EXIT_SUCCESS;
}