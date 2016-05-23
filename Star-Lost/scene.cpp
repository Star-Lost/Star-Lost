#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resources.h"
#include "animation.h"
#include "scene.h"

scene::scene(scene_director *dir)
{
	director = dir;
	colour = sf::Color::Black;
	status = 1;
}

int scene::update(double dt, int update_parent)
{
	return 1; // This scene executed correctly
}

void scene::render(sf::RenderWindow *window)
{
	// Draw the scene here
	window->clear(colour);
	window->display();
}

game_scene::game_scene(scene_director *dir) : scene(dir)
{
	colour = sf::Color::Red;

	sf::Sprite character;
	auto char_tex = director->textures.load_resource("character.png");
	if (char_tex == nullptr)
	{
		printf("Failed to load character :(\n");
		(*director).status = -1;
	}
	
	model char_model{
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
		}),
	};


	// Draw the character
	const model::animation *anim = char_model["stand_south"];
	// Character animation stuff ends here
}

int game_scene::update(double dt, int update_next)
{
	if (update_next)
	{
		static_cast<scene*>(this)->update(dt, 0);
	}

	return 1;
}

void game_scene::render(sf::RenderWindow *window)
{
	window->clear(colour);
	window->display();
}

pause_scene::pause_scene(scene_director *dir) : scene(dir)
{
	colour = sf::Color::Green;
}

int pause_scene::update(double dt, int update_next)
{
	if (update_next)
	{
		// We want the pause scene to render the game behind it
		static_cast<scene*>(this)->update(dt, 1);
	}

	return 1;
}

void pause_scene::render(sf::RenderWindow *window)
{
	window->clear(colour);
	window->display();
}

scene_director::scene_director()
{
	status = 1;

	scenes.push_back(new game_scene(this));
}

int scene_director::update(double dt)
{
	std::vector<scene*>::reverse_iterator rit = scenes.rbegin();
	for (rit; rit != scenes.rend(); ++rit)
	{
		status = (*rit)->update(dt, 1);
	}

	return status;
}

void scene_director::render(sf::RenderWindow *window)
{
	std::vector<scene*>::reverse_iterator rit = scenes.rbegin();
	for (rit; rit != scenes.rend(); ++rit)
	{
		(*rit)->render(window);
	}
}
