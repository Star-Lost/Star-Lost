#pragma once

namespace ecs
{
	namespace systems
	{
		struct velocity_system
		{
			using required = mpl::type_list<
				components::position,
				components::velocity
			>;

			void update(std::size_t entity_index, components::position &pos, components::velocity &vel) const;
		};
	}
}