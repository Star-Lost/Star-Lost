#pragma once
#include <SFML/Graphics.hpp>

class scene
{
public:
	scene();
	int update(double dt, int update_next);
	void render(sf::RenderWindow *window);
	
	sf::Color colour;

	int status;
private:
};

class game_scene : public scene
{
public:
	game_scene();
	int update(double dt, int update_next);
	void render(sf::RenderWindow *window);
};

class pause_scene : public scene
{
public:
	pause_scene();
	int update(double dt, int update_next);
	void render(sf::RenderWindow *window);
};

class scene_director
{
public:
	scene_director();
	int update(double dt);
	void render(sf::RenderWindow *window);

	std::vector<scene*> scenes;
	int status; // If this is zero then we exit the game
private:
};
