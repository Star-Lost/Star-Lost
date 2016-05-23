#include "scene.h"

scene_director::scene_director()
{
	status = 1;

	scenes.push_back(new game_scene());
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

scene::scene()
{
	colour = sf::Color::Black;
	status = 0;
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

game_scene::game_scene() : scene()
{
	colour = sf::Color::Red;
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

pause_scene::pause_scene() : scene()
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