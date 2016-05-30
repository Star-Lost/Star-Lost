
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

sf::Vector2f center(const sf::FloatRect &rect)
{
	return{ rect.left + rect.width / 2, rect.top + rect.height / 2 };
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

			auto oc = center(obox);
			auto nc = center(newbox);
			
			float signx = std::copysign(1.0f, oc.x - nc.x);
			float signy = std::copysign(1.0f, oc.y - nc.y);

			if (overlap.width > overlap.height)
			{
				pos.y = newpos.y - overlap.height*signy;
				vel.y = 0;
			}
			else
			{
				pos.x = newpos.x - overlap.width*signx;
				vel.x = 0;
			}
		}
	});	

}