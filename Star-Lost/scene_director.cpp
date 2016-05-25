#pragma once
#include "scene_director.h"

scene_director::scene_director(sf::RenderWindow &win) :
	is_alive(true),
	window(win)
{ }

void scene_director::update()
{
	delta_time = float(clock.getElapsedTime().asMicroseconds()) / 1000.0f;
	clock.restart();

	std::vector<std::unique_ptr<scene>>::iterator it = scenes.begin();
	for (it; it != scenes.end(); it++)
	{
		(*it)->update(*this);
	}
}

void scene_director::add_scene(std::unique_ptr<scene> &&new_scene)
{
	scenes.emplace_back(std::move(new_scene));
}