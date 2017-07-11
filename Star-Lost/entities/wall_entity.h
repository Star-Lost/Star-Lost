#pragma once
#include "../entities/base_entity.h"
#include "../entities/tent_entity.h"

namespace ecs
{
	namespace entities
	{
		using wall_requirements = mpl::type_list<
			tags::structure,
			components::position,
			components::collision,
			components::drawable
		>;

		struct wall : public entities::base<wall_requirements>
		{
			wall(game_context &ctx, entity_index eid);
			wall(game_context &ctx, const char *frame, float x, float y);
		};
	}
}