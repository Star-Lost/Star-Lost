#pragma once

namespace ecs
{
	namespace systems
	{
		struct animation : public base_system
		{
			using required = mpl::type_list<
				components::animation,
				components::drawable
			>;

			void update(
				entity_index eid, 
				game_context &ctx, 
				components::animation &anim,
				components::drawable &spr
			);
		};
	}
}