#include "game_context.h"

game_context::game_context(scene_director &dir) :
	director(dir)
{
	initialize_systems(*this);
}

void game_context::update(float dt)
{
	delta_time = dt;
	context::update(*this);
}

scene_director &game_context::get_director()
{
	return director;
}

float game_context::get_delta() const
{
	return delta_time;
}