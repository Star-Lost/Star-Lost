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

	game_context ctx;

	auto ent = ctx.create_entity();
	//ctx.add_tag<player_tag>(ent);
	ctx.add_component<ecs::components::position>(ent, 1.0f, 2.0f);
	ctx.add_component<ecs::components::velocity>(ent);

	// Character animation stuff goes here
	/*sf::Sprite character;
	auto char_tex = textures.load_resource("character.png");
	if (char_tex == nullptr)
	{
		printf("Failed to load character :(\n");
		return EXIT_FAILURE;
	}*/

	sf::Clock clock;
	double time = 0;
	double delta_time;
	
	// Set the scene
	scene_director director;

	while (director.status != 0)
	{
		ctx.update(float(clock.getElapsedTime().asMilliseconds()) / 1000.0f);

		sf::Event event;
		while (window.pollEvent(event))
		{
			delta_time = clock.getElapsedTime().asMilliseconds() - time;

			director.update(delta_time);
			director.render(&window);
		}
		
		// check all the window's events that were triggered since the last iteration of the loop
		//sf::Event event;
		//while (window.pollEvent(event))
		//{
		//	switch (event.type)
		//	{
		//	case sf::Event::Closed:	window.close(); break;

		//	case sf::Event::KeyPressed:
		//	{
		//		switch(event.key.code)
		//		{
		//			case sf::Keyboard::W: anim = char_model["walk_north"]; break;
		//			case sf::Keyboard::A: anim = char_model["walk_west"]; break;
		//			case sf::Keyboard::S: anim = char_model["walk_south"]; break;
		//			case sf::Keyboard::D: anim = char_model["walk_east"]; break;
		//			default: break;
		//		}
		//		break;
		//	}

		//	case sf::Event::KeyReleased:
		//	{
		//		switch (event.key.code)
		//		{
		//		case sf::Keyboard::W: anim = char_model["stand_north"]; break;
		//		case sf::Keyboard::A: anim = char_model["stand_west"]; break;
		//		case sf::Keyboard::S: anim = char_model["stand_south"]; break;
		//		case sf::Keyboard::D: anim = char_model["stand_east"]; break;
		//		default: break;
		//		}
		//		break;
		//	}

		//	default: break;
		//	}
		//}

		//// clear the window with black color
		//window.clear(sf::Color::Black);

		//// Then get the current frame of the animation
		//const model::animation::frame &curframe =
		//	(*anim)[clock.getElapsedTime().asMilliseconds() / 100];
		//
		//character.setTexture(*curframe.get_texture());
		//character.setTextureRect(curframe.get_subtexture());
		//character.setPosition(sf::Vector2f(20.0f, 20.0f)); // +(clock.getElapsedTime().asMilliseconds() % 5000) / 50.0f));
		//window.draw(character);

		//// end the current frame
		//window.display();
	}

	return EXIT_SUCCESS;
}