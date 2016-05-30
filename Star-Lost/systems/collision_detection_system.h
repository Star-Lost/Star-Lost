#pragma once

namespace ecs
{
	namespace systems
	{
		struct collision_detection
		{
			using required = mpl::type_list<
				components::position,
				components::velocity,
				components::collision
			>;

			void update(
				entity_index eid,
				game_context &ctx,
				components::position &pos,
				components::velocity &vel,
				components::collision &bbx
			) const;
		};
	}
}