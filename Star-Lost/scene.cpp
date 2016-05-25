#pragma once
#include "scene.h"

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

	std::vector<scene*>::iterator it = scenes.begin();
	for (it; it != scenes.end(); it++)
	{
		(*it)->update(*this);
	}
}
