
#include "../game_context.h"

using namespace ecs;

using collideable = mpl::type_list<
	components::position,
	components::collision
>;

void systems::collision::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::velocity &vel,
	components::collision &bbx
) const
{
	auto newpos = pos + vel * ctx.get_delta();

	// Where our bounding box is gonna be, 
	// should we continue along our current trajectory
	auto newbox = sf::FloatRect{ bbx.bbox.left + pos.x, bbx.bbox.top + pos.y, bbx.bbox.width, bbx.bbox.height };

	// Check if our boxes will intersect
	ctx.for_entities<collideable>([&pos, &vel, &bbx, &ctx, newbox](entity_index otherid)
	{
		auto obox = ctx.get_component<components::collision>(otherid).bbox;

		if (newbox.intersects(obox))
		{
			// Time to resolve!
			vel = {};
		}
	});	
}