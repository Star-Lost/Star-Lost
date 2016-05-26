
#include "../game_context.h"

using namespace ecs;

using collideable = mpl::type_list<
	components::position,
	components::collision
>;

sf::FloatRect operator+(const sf::FloatRect &rect, const sf::Vector2f &vec)
{
	return sf::FloatRect{ rect.left + vec.x, rect.top + vec.y, rect.width, rect.height };
}

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
	auto newbox = bbx.bbox + newpos;

	// Check if our boxes will intersect
	ctx.for_entities<collideable>([&pos, &vel, &bbx, &ctx, eid, newbox](entity_index otherid)
	{
		if (otherid == eid)
			return;

		auto obox =
			ctx.get_component<components::collision>(otherid).bbox
			+ ctx.get_component<components::position>(otherid);

		if (newbox.intersects(obox))
		{
			// Time to resolve!
			vel.x = 0;
			vel.y = 0;
		}
	});	

}