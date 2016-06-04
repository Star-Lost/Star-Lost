#pragma once

namespace ecs
{
	namespace systems
	{
		struct static_collision_resolution : public base_system
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

		struct dynamic_collision_resolution : public base_system
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