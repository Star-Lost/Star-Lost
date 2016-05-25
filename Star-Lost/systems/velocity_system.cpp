#include "../game_context.h"

using namespace ecs;

void systems::velocity::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos, 
	components::velocity &vel
) const
{
	pos += vel * ctx.get_delta();
}