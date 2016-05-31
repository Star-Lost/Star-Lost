#pragma once
#include "../entities/base_entity.h"

namespace ecs
{
	namespace tags
	{
		struct furniture {};
	}

	namespace entities
	{
		using lamp_requirements = mpl::type_list<
			tags::furniture,
			components::position,
			components::velocity,
			components::collision,
			components::drawable,
			components::animation
		>;

		struct lamp : public entities::base<lamp_requirements>
		{
			lamp(game_context &ctx, entity_index eid);
			lamp(game_context &ctx);
		};
	}
}