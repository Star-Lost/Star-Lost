#include "../game_context.h"

using namespace ecs;

void systems::collision_resolution::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::collision &bbx
) const
{
	// If we don't have a velocity component, we're static
	// So just do nothing
	if (!ctx.has_component<components::velocity>(eid))
	{
		bbx.collisions.clear();
		return;
	}

	using col_edge = components::collision::collision_edge;

	auto &vel = ctx.get_component<components::velocity>(eid);
	auto dt = ctx.get_delta();

	for (auto &evt : bbx.collisions)
	{
		float mass_ratio = ctx.get_component<components::collision>(evt.aid).mass / ctx.get_component<components::collision>(evt.bid).mass;

		if (evt.aid == eid)
		{				
			if (mass_ratio == 0) // we've hit a static object
			{
				switch (evt.edge)
				{
				case col_edge::south: 
				case col_edge::north: vel.y = 0; break;
				case col_edge::west:
				case col_edge::east: vel.x = 0; break;
				}
			}
			else
			{
				vel.x += (evt.force.x) * (1.0f/mass_ratio);
				vel.y += (evt.force.y) * (1.0f/mass_ratio);
			}
		}
		else
		{
			vel.x += evt.force.x;
			vel.y += evt.force.y;
		}

	}

	bbx.collisions.clear();
}