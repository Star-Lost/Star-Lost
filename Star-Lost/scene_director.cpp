#pragma once
#include "scene_director.h"

scene_director::scene_director(sf::RenderWindow &win) :
	status(1),
	window(win),
	time(float(clock.getElapsedTime().asMilliseconds()))
{
}

void scene_director::update()
{
	delta_time = float(clock.getElapsedTime().asMilliseconds()) - time;
	time = float(clock.getElapsedTime().asMilliseconds());

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