#pragma once
#include "base_entity.h"

namespace ecs
{
	namespace entities
	{
		using tent_requirements = mpl::type_list<
			components::position,
			components::collision,
			components::drawable
		>;

		struct tent : public entities::base<tent_requirements>
		{
			tent(game_context &ctx, entity_index eid);
			tent(game_context &ctx);
		};
	}
}