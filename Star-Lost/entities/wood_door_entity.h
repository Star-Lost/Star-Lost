#pragma once
#include "base_entity.h"
#include "tent_entity.h"

namespace ecs
{
	namespace entities
	{
		using wood_door_requirements = mpl::type_list<
			tags::structure,
			components::position,
			components::collision,
			components::drawable
		>;

		struct wood_door : public entities::base<wood_door_requirements>
		{
			wood_door(game_context &ctx, entity_index eid);
			wood_door(game_context &ctx, const char *frame, float x, float y);
		};
	}
}