#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resources.h"
#include "animation.h"

class scene;

class scene_director
{
public:
	scene_director();
	int update(double dt);
	void render(sf::RenderWindow *window);

	resource<sf::Texture> textures;
	resource<sf::SoundBuffer> sounds;
	std::vector<scene*> scenes;

	int status; // If this is less than zero then we exit the game
};

class scene
{
public:
	scene(scene_director *dir);
	int update(double dt, int update_next);
	void render(sf::RenderWindow *window);
	
	sf::Color colour;
	scene_director *director; // We need this to create new scenes

	int status;
private:
};

class game_scene : public scene
{
public:
	game_scene(scene_director *dir);
	int update(double dt, int update_next);
	void render(sf::RenderWindow *window);
};

class pause_scene : public scene
{
public:
	pause_scene(scene_director *dir);
	int update(double dt, int update_next);
	void render(sf::RenderWindow *window);
};
