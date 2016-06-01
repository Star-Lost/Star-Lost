#include "../game_context.h"

using namespace ecs;

void systems::friction::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::velocity &vel
) const
{
	vel *= 0.95f;

	if (std::abs(vel.x) < std::numeric_limits<float>::epsilon() * 100.0f)
		vel.x = 0;

	if (std::abs(vel.y) < std::numeric_limits<float>::epsilon() * 100.0f)
		vel.y = 0;
}