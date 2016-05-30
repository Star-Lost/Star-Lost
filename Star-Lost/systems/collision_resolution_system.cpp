#include "../game_context.h"

using namespace ecs;

void systems::collision_resolution::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::velocity &vel,
	components::collision &bbx
) const
{
	using coledge = components::collision::collision_edge;

	auto dt = ctx.get_delta();

	for (auto &evt : bbx.collisions)
	{
		switch (evt.edge)
		{
		case coledge::north:
		{
			pos.y += vel.y * dt - evt.overlap.height;
			vel.y = 0;
			break;
		}
		case coledge::south:
		{
			pos.y += vel.y * dt + evt.overlap.height;
			vel.y = 0;
			break;
		}
		case coledge::west:
		{
			pos.x += vel.x * dt - evt.overlap.width;
			vel.x = 0;
			break;
		}
		case coledge::east:
		{
			pos.x += vel.x * dt + evt.overlap.width;
			vel.x = 0;
			break;
		}

		}
	}

	bbx.collisions.clear();
}