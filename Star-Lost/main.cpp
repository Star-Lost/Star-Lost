#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "scenes/game_scene.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Star Lost");
	window.setFramerateLimit(60);

	sf::Clock clock;
	
	// Set the scene
	scene_director director(window);

	//director.add_scene(new game_scene());
	
	while (director.status != 0)
	{
		director.update();
	}

	return EXIT_SUCCESS;
}