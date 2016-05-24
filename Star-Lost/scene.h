#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resources.h"
#include "animation.h"

#include "game_context.h"

class scene;

class scene_director
{
public:
	scene_director(sf::RenderWindow *window);
	void update();
	void render();

	sf::RenderWindow *window;
	sf::Clock clock;
	resource<sf::Texture> textures;
	resource<model> models;
	resource<sf::SoundBuffer> sounds;
	std::vector<scene*> scenes;

	int status; // If this is less than zero then we exit the game
	float time; // Right now
	float delta_time; // What time it was last time
};

class scene
{
public:
	scene(scene_director *director);
	void virtual update(scene_director *director);
	void virtual render(scene_director *director);
	
	game_context ctx;

	sf::Color colour;
};

class game_scene : public scene
{
public:
	game_scene(scene_director *director);
	void virtual update(scene_director *director);
	void virtual render(scene_director *director);
};

class pause_scene : public scene
{
public:
	pause_scene(scene_director *director);
	void virtual update(scene_director *director);
	void virtual render(scene_director *director);
};
