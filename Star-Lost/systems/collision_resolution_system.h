#pragma once

namespace ecs
{
	namespace systems
	{
		struct collision_resolution : public base_system
		{
			using required = mpl::type_list<
				components::position,
				components::collision
			>;

			void update(
				entity_index eid,
				game_context &ctx,
				components::position &pos,
				components::collision &bbx
			) const;
		};
	}
}