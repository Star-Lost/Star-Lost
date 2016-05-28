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

	// Accessors
	sf::Clock get_clock();
	sf::RenderWindow &get_window();
	resource<rendering::model> &get_models();
	resource<sf::Texture> &get_textures();
	resource<sf::SoundBuffer> &get_soundbuffers();
	resource<sf::Font> &get_fonts();
	bool get_is_alive();
private:
	std::vector<std::unique_ptr<scene>> scenes;
	sf::Clock clock;
	sf::RenderWindow &window;
	resource<rendering::model> models;
	resource<sf::Texture> textures;
	resource<sf::SoundBuffer> sounds;
	resource<sf::Font> fonts;

	float delta_time;
	bool is_alive;
};

class scene
{
public:
	virtual void handle_event(scene_director &director, const sf::Event &evt) = 0;
	virtual void update(scene_director &director, float dt) = 0;
};