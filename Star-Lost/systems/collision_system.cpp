
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

	auto delta = ctx.get_delta();
	auto newpos = pos + vel * delta;
	// Where our bounding box is gonna be, 
	// should we continue along our current trajectory
	auto newbox = bbx.bbox + newpos;

	// Check if our boxes will intersect
	ctx.for_entities<collideable>([&pos, &vel, &bbx, &ctx, eid, newpos, newbox](entity_index otherid)
	{
		if (otherid == eid)
			return;

		auto obox =
			ctx.get_component<components::collision>(otherid).bbox
			+ ctx.get_component<components::position>(otherid);

		if (newbox.intersects(obox))
		{
			float x = std::max(newbox.left, obox.left);
			float y = std::max(newbox.top, obox.top);
			// Calculate the union of the two boxes (the overlapping area)
			sf::FloatRect overlap{
				x,
				y,
				std::min(newbox.left + newbox.width, obox.left + obox.width) - x,
				std::min(newbox.top + newbox.height, obox.top + obox.height) - y
			};

			float signx = std::abs(vel.x)/vel.x;
			float signy = std::abs(vel.y)/vel.y;

			if(overlap.width > overlap.height)
				pos.y = newpos.y - overlap.height*signy;
			else
				pos.x = newpos.x - overlap.width*signx;
		}
	});	

}