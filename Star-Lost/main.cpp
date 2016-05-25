#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "resources.h"
#include "animation.h"
#include "scene.h"

#include "game_context.h"


int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Star Lost");
	window.setFramerateLimit(60);

	sf::Clock clock;
	
	// Set the scene
	scene_director director(&window);
	
	while (director.status != 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:	window.close(); break;

			/*case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W: anim = char_model["walk_north"]; break;
				case sf::Keyboard::A: anim = char_model["walk_west"]; break;
				case sf::Keyboard::S: anim = char_model["walk_south"]; break;
				case sf::Keyboard::D: anim = char_model["walk_east"]; break;
				default: break;
				}
				break;
			}

			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W: anim = char_model["stand_north"]; break;
				case sf::Keyboard::A: anim = char_model["stand_west"]; break;
				case sf::Keyboard::S: anim = char_model["stand_south"]; break;
				case sf::Keyboard::D: anim = char_model["stand_east"]; break;
				default: break;
				}
				break;
			}*/
			}
		}

		director.update();
		//director.render();
	}

	return EXIT_SUCCESS;
}