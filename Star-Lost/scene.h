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

	sf::RenderWindow *window;
	sf::Clock clock;
	resource<model> models;
	resource<sf::Texture> textures;
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
	void virtual update(scene_director *director) = 0;
};

class game_scene : public scene
{
public:
	game_scene(scene_director *director);
	void virtual update(scene_director *director) override;

	game_context ctx;
};

class pause_scene : public scene
{
public:
	pause_scene(scene_director *director);
	void virtual update(scene_director *director) override;
};
