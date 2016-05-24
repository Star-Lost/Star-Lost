#pragma once

namespace ecs
{
	namespace systems
	{
		struct animation
		{
			using required = mpl::type_list<
				components::animation
			>;

			void update(std::size_t entity_index, components::animation &anim);
		};
	}
}