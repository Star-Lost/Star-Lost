#pragma once

class scene_director;

namespace ecs
{
	namespace tags
	{
		struct interact {};
	}

	namespace systems
	{
		struct interaction : public base_system
		{
			using required = mpl::type_list<
				tags::interact
			>;

			void update(
				entity_index eid,
				game_context &ctx
			);
		};
	}
}