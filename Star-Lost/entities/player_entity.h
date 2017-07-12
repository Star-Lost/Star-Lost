#pragma once
#include "base_entity.h"

namespace ecs
{
	namespace tags
	{
		struct player {};
	}

	namespace entities
	{
		using player_requirements = mpl::type_list<
			tags::player,
			components::position,
			components::velocity,
			components::collision,
			components::drawable,
			components::animation
		>;

		struct player : public entities::base<player_requirements>
		{
			player(game_context &ctx, entity_index eid);
			player(game_context &ctx);

			components::position &get_position() const;
		};
	}
}