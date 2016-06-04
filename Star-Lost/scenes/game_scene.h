#pragma once
#include "../scene_director.h"
#include "../game_context.h"

rendering::model create_player_model(resource<sf::Texture> &textures);
rendering::model create_tent_model(resource<sf::Texture> &textures);
rendering::model create_lamp_model(resource<sf::Texture> &textures);

class game_scene : public scene
{
public:
	game_scene(scene_director &director);

	virtual void handle_event(scene_director &director, const sf::Event &evt) override;
	virtual void update(scene_director &director, float dt) override;

	game_context ctx;
	sf::View camera;
	sf::Font font;
};