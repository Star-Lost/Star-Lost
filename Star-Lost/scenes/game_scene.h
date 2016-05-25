#pragma once
#include "../scene_director.h"
#include "../game_context.h"

class game_scene : public scene
{
public:
	game_scene(scene_director &director);

	virtual void handle_event(scene_director &director, const sf::Event &evt) override;
	virtual void update(scene_director &director) override;

	game_context ctx;
};