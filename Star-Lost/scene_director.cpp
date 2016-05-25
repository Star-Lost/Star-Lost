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

	sf::Event evt;
	while (window.pollEvent(evt))
	{
		scenes.back()->handle_event(evt);
	}

	scenes.back()->update(*this);
}

void scene_director::add_scene(std::unique_ptr<scene> &&new_scene)
{
	scenes.emplace_back(std::move(new_scene));
}