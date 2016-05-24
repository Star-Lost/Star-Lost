#include "../game_context.h"

using namespace ecs;

void systems::velocity::update(
	std::size_t entity_index, 
	game_context &ctx,
	components::position &pos, 
	components::velocity &vel
) const
{
	pos += vel * ctx.get_delta();
}