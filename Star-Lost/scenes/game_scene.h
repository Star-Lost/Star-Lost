#pragma once
#include "../scene.h"

class game_scene : public scene
{
public:
	game_scene(scene_director *director);
	void virtual update(scene_director *director) override;

	game_context ctx;
};