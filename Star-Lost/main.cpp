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
	ctx.add_component<ecs::components::position>(ent, 1.0f, 2.0f);
	ctx.add_component<ecs::components::velocity>(ent);

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