#pragma once

namespace ecs
{
	namespace systems
	{
		struct velocity
		{
			using required = mpl::type_list<
				components::position,
				components::velocity
			>;

			void update(std::size_t entity_index, float dt, components::position &pos, components::velocity &vel) const;
		};
	}
}