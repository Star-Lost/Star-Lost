#pragma once

namespace ecs
{
	namespace systems
	{
		struct velocity : public base_system
		{
			using required = mpl::type_list<
				components::position,
				components::velocity
			>;

			void update(
				entity_index eid, 
				game_context &ctx, 
				components::position &pos, 
				components::velocity &vel
			) const;
		};
	}
}