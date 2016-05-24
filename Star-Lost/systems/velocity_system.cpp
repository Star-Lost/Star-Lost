#include "../game_context.h"

using namespace ecs;

void systems::velocity_system::update(
	std::size_t entity_index, 
	components::position &pos, 
	components::velocity &vel
) const
{
	pos += vel;
}