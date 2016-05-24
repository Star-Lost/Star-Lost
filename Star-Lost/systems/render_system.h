#pragma once

namespace ecs
{
	namespace systems
	{
		struct render
		{
			using required = mpl::type_list<
				components::position,
				components::sprite
			>;

			void update(std::size_t entity_index, game_context &ctx, components::position &pos, components::sprite &spr) const;
		};
	}
}