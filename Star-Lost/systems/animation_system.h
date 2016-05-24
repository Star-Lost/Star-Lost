#pragma once

namespace ecs
{
	namespace systems
	{
		struct animation
		{
			using required = mpl::type_list<
				components::animation,
				components::sprite
			>;

			void update(std::size_t entity_index, game_context &ctx, components::animation &anim, components::sprite &spr);
		};
	}
}