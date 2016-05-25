#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "resources.h"
#include "animation.h"

class scene;

class scene_director
{
public:
	scene_director(sf::RenderWindow &window);
	
	void update();

	void add_scene(std::unique_ptr<scene> &&new_scene);

	// All of this should probably be private, and use accessor functions.
	// You don't want, for instance, a system to change the delta time
	// halfway through a cycle.
	sf::Clock clock;
	resource<model> models;
	resource<sf::Texture> textures;
	resource<sf::SoundBuffer> sounds;

	int status; // If this is less than zero then we exit the game
	float time; // Right now
	float delta_time; // What time it was last time

	sf::RenderWindow &window;

private:
	std::vector<std::unique_ptr<scene>> scenes;
};

class scene
{
public:
	void virtual update(scene_director &director) = 0;
};