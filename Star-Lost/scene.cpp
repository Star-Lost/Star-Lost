#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resources.h"
#include "animation.h"
#include "scene.h"

#include "game_context.h"

// Prototypes
void create_character_model(resource<sf::Texture> &textures, resource<model> &models);

scene::scene(scene_director *director) :
	ctx(*(*director).window)
{
	colour = sf::Color::Black;
}

void scene::update(scene_director *director)
{
	(*director).status = 1; // Everything is a-okay!
}

void scene::render(scene_director *director)
{
	sf::RenderWindow *window = director->window;

	window->clear(colour);

	// Draw the scene here

	window->display();
}

game_scene::game_scene(scene_director *director) : scene(director)
{
	colour = sf::Color::Red;


	game_context ctx(*(*director).window);

	create_character_model((*director).textures, (*director).models);
	auto &char_model = *(*director).models.get_resource("char_model");
	auto ply = ctx.create_entity();

	ctx.add_component<ecs::components::position>(ply, 50.0f, 50.0f);
	ctx.add_component<ecs::components::velocity>(ply);
	ctx.add_component<ecs::components::sprite>(ply).setTexture(*(*director).textures.get_resource("character.png"));
	auto &anim = (ctx.add_component<ecs::components::animation>(ply).anim);
	anim = char_model["stand_south"];
}

void game_scene::update(scene_director *director)
{
	ctx.update(float((*director).clock.getElapsedTime().asMilliseconds()) / 1000.0f);
	(*director).status = 1;
}

void game_scene::render(scene_director *director)
{
	sf::RenderWindow *window = director->window;

	window->clear(colour);

	ctx.update(float((*director).clock.getElapsedTime().asMilliseconds()) / 1000.0f);
	// Draw the scene here

	window->display();
}

pause_scene::pause_scene(scene_director *director) : scene(director)
{
	colour = sf::Color::Green;
}

void pause_scene::update(scene_director *director)
{
	(*director).status = -1;
}

void pause_scene::render(scene_director *director)
{
	sf::RenderWindow *window = director->window;

	window->clear(colour);

	// Draw the scene here

	window->display();
}

scene_director::scene_director(sf::RenderWindow *win)
{
	status = 1;

	window = win;
	scenes.push_back(new game_scene(this));
	
	time = float(clock.getElapsedTime().asMilliseconds());
}

void scene_director::update()
{
	delta_time = float(clock.getElapsedTime().asMilliseconds()) - time;
	time = float(clock.getElapsedTime().asMilliseconds());

	std::vector<scene*>::iterator it = scenes.begin();
	for (it; it != scenes.end(); it++)
	{
		(*it)->update(this);
	}
}

void scene_director::render()
{
	std::vector<scene*>::iterator it = scenes.begin();
	for (it; it != scenes.end(); it++)
	{
		(*it)->render(this);
	}
}

void create_character_model(resource<sf::Texture> &textures, resource<model> &models)
{
	auto char_tex = textures.load_resource("character.png");

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