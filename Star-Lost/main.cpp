#include "scenes/game_scene.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Star Lost");
	window.setFramerateLimit(60);
	
	// Set the scene
	scene_director director(window);

	director.add_scene(std::make_unique<game_scene>(director));
	
	while (director.get_is_alive())
	{
		director.update();
	}

	return EXIT_SUCCESS;
}