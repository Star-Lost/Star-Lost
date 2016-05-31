#pragma once
#include "../entities/base_entity.h"

namespace ecs
{
	namespace tags
	{
		struct tent {};
	}

	namespace entities
	{
		using tent_requirements = mpl::type_list<
			tags::tent,
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