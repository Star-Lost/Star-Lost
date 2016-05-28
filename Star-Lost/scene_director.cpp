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
		scenes.back()->handle_event(*this, evt);
	}

	scenes.back()->update(*this, delta_time);
}

void scene_director::add_scene(std::unique_ptr<scene> &&new_scene)
{
	scenes.emplace_back(std::move(new_scene));
}

sf::Clock scene_director::get_clock()
{
	return clock;
}

sf::RenderWindow& scene_director::get_window()
{
	return window;
}

resource<rendering::model> &scene_director::get_models()
{
	return models;
}

resource<sf::Texture> &scene_director::get_textures()
{
	return textures;
}

resource<sf::SoundBuffer> &scene_director::get_soundbuffers()
{
	return sounds;
}

resource<sf::Font> &scene_director::get_fonts()
{
	return fonts;
}

bool scene_director::get_is_alive()
{
	return is_alive;
}