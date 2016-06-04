#include "../game_context.h"

using namespace ecs;

void systems::static_collision_resolution::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::collision &bbx
) const
{
	using col_edge = components::collision::collision_edge;

	auto &vel = ctx.get_component<components::velocity>(eid);

	for (auto &evt : bbx.collisions)
	{
		float mass_ratio = ctx.get_component<components::collision>(evt.aid).mass / ctx.get_component<components::collision>(evt.bid).mass;
		
		if (mass_ratio == 0) // we've hit a static object
		{
			switch (evt.edge)
			{
			case col_edge::south: 
			case col_edge::north: 
				vel.y = 0;
				//vel.x = 0;
				pos.y -= std::copysign(1.0f, evt.force.y) * evt.overlap.height; break;
			case col_edge::west:
			case col_edge::east: 
				vel.x = 0;
				//vel.y = 0;
				pos.x -= std::copysign(1.0f, evt.force.x) * evt.overlap.width; break;
			}
		}
	}
	bbx.collisions.clear();
}

void systems::dynamic_collision_resolution::update(
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

	sf::Vector2f apply_force[4] = {
		/* north */{ 0.0f, 1.0f },
		/* south */{ 0.0f, 1.0f },
		/* east	 */{ 1.0f, 0.0f },
		/* west  */{ 1.0f, 0.0f }
	};

	for (auto &evt : bbx.collisions)
	{
		float mass_ratio = ctx.get_component<components::collision>(evt.aid).mass / ctx.get_component<components::collision>(evt.bid).mass;
		float velocity_transfer = std::min(mass_ratio, 1.0f);

		if (evt.aid == eid)
		{
			if (mass_ratio != 0) // Make sure we're not hitting a static object
			{
				vel.x -= (evt.force.x) * apply_force[evt.edge].x * velocity_transfer;
				vel.y -= (evt.force.y) * apply_force[evt.edge].y * velocity_transfer;
			}
		}
		else
		{
			vel.x += (evt.force.x) * apply_force[evt.edge].x * velocity_transfer;
			vel.y += (evt.force.y) * apply_force[evt.edge].y * velocity_transfer;
		}
	
	}
}