#pragma once
#include "base_entity.h"
#include "tent_entity.h"

namespace ecs
{
	namespace entities
	{
		using wall_requirements = mpl::type_list<
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