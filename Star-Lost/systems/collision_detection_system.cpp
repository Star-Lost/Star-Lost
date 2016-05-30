
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

void systems::collision_detection::update(
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
	ctx.for_entities<collideable>([&bbx, &ctx, eid, newbox](entity_index otherid)
	{
		if (otherid == eid)
			return;

		auto obstacle =
			ctx.get_component<components::collision>(otherid).bbox
			+ ctx.get_component<components::position>(otherid);

		if (newbox.intersects(obstacle))
		{
			float x = std::max(newbox.left, obstacle.left);
			float y = std::max(newbox.top, obstacle.top);

			// Calculate the union of the two boxes (the overlapping area)
			sf::FloatRect overlap{
				x,
				y,
				std::min(newbox.left + newbox.width, obstacle.left + obstacle.width) - x,
				std::min(newbox.top + newbox.height, obstacle.top + obstacle.height) - y
			};

			auto oc = center(obstacle);
			auto nc = center(newbox);

			float signx = std::copysign(1.0f, oc.x - nc.x);
			float signy = std::copysign(1.0f, oc.y - nc.y);

			components::collision::collision_edge edge;

			// up/do
			if (overlap.width > overlap.height)
			{
				edge = (signy > 0.0f)
					? components::collision::collision_edge::north
					: components::collision::collision_edge::south;
			}
			else
			{
				edge = (signx > 0.0f)
					? components::collision::collision_edge::west
					: components::collision::collision_edge::east;
			}

			bbx.collisions.emplace_back(
				eid,
				otherid,
				edge,
				overlap
			);
		}
	});	

}