#pragma once

namespace ecs
{
	namespace systems
	{
		struct render
		{
			using required = mpl::type_list<
				components::position,
				components::drawable
			>;

			void update(
				entity_index eid, 
				game_context &ctx, 
				components::position &pos, 
				components::drawable &drw
			) const;
		};
	}
}