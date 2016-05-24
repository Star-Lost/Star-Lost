#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "resources.h"
#include "animation.h"
#include "scene.h"

#include "game_context.h"


void create_character_model(resource<sf::Texture> &textures, resource<model> &models);

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Star Lost");
	window.setFramerateLimit(60);

	sf::Clock clock;
	float time = 0;
	float delta_time;
	
	// Set the scene
	scene_director director;

	resource<model> models;
	create_character_model(director.textures, models);

	game_context ctx(window);


	auto &char_model = *models.get_resource("char_model");
	auto ply = ctx.create_entity();
	ctx.add_component<ecs::components::position>(ply, 50.0f, 50.0f);
	ctx.add_component<ecs::components::velocity>(ply);
	ctx.add_component<ecs::components::sprite>(ply).setTexture(*director.textures.get_resource("character.png"));
	auto &anim = (ctx.add_component<ecs::components::animation>(ply).anim);
	anim = char_model["stand_south"];

	while (director.status != 0)
	{
		ctx.update(float(clock.getElapsedTime().asMilliseconds()) / 1000.0f);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:	window.close(); break;

			case sf::Event::KeyPressed:
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
			}
			}
		}

		delta_time = clock.getElapsedTime().asMilliseconds() - time;
		time = float(clock.getElapsedTime().asMilliseconds());

		//director.update(delta_time);
		//director.render(&window);

		ctx.update(delta_time);

		window.display();
	}

	return EXIT_SUCCESS;
}

void create_character_model(resource<sf::Texture> &textures, resource<model> &models)
{
	auto char_tex = textures.get_resource("character.png");

	models.set_resource("char_model", model{
		// Standing still facing south animation
		std::make_pair(std::string{ "stand_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 0, 16, 16)}
		}),

		// Standing still facing north animation
		std::make_pair(std::string{ "stand_north" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(16, 0, 16, 16)}
		}),

		// Standing still facing west animation
		std::make_pair(std::string{ "stand_west" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(32, 0, 16, 16)}
		}),

		// Standing still facing east animation
		std::make_pair(std::string{ "stand_east" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(48, 0, 16, 16)}
		}),

		// Walk south animation
		std::make_pair(std::string{ "walk_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 16, 16, 16) },
			{ char_tex, sf::IntRect(0, 32, 16, 16) },
			{ char_tex, sf::IntRect(0,  0, 16, 16) },
			{ char_tex, sf::IntRect(0, 48, 16, 16) },
			{ char_tex, sf::IntRect(0, 64, 16, 16) },
			{ char_tex, sf::IntRect(0,  0, 16, 16) }
		}),

		// Walk north animation
		std::make_pair(std::string{ "walk_north" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(16, 16, 16, 16) },
			{ char_tex, sf::IntRect(16, 32, 16, 16) },
			{ char_tex, sf::IntRect(16,  0, 16, 16) },
			{ char_tex, sf::IntRect(16, 48, 16, 16) },
			{ char_tex, sf::IntRect(16, 64, 16, 16) },
			{ char_tex, sf::IntRect(16,  0, 16, 16) }
		}),

		// Walk west animation
		std::make_pair(std::string{ "walk_west" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(32, 16, 16, 16) },
			{ char_tex, sf::IntRect(32, 32, 16, 16) },
			{ char_tex, sf::IntRect(32,  0, 16, 16) },
			{ char_tex, sf::IntRect(32, 48, 16, 16) },
			{ char_tex, sf::IntRect(32, 64, 16, 16) },
			{ char_tex, sf::IntRect(32,  0, 16, 16) }
		}),

		// Walk east animation
		std::make_pair(std::string{ "walk_east" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(48, 16, 16, 16) },
			{ char_tex, sf::IntRect(48, 32, 16, 16) },
			{ char_tex, sf::IntRect(48,  0, 16, 16) },
			{ char_tex, sf::IntRect(48, 48, 16, 16) },
			{ char_tex, sf::IntRect(48, 64, 16, 16) },
			{ char_tex, sf::IntRect(48,  0, 16, 16) }
		})
	});
}