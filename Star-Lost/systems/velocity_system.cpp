#include "../game_context.h"

using namespace ecs;

void systems::velocity::update(
	std::size_t entity_index, 
	float dt,
	components::position &pos, 
	components::velocity &vel
) const
{
	pos += vel * dt;
}