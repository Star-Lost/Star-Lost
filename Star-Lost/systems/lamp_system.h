#pragma once

namespace ecs
{
	namespace tags
	{
		struct lamp {};
	}

	namespace systems
	{
		struct lamp : public base_system
		{
			using required = mpl::type_list<
				components::collision,
				tags::tent
			>;

			void initialize(game_context &ctx);

			void update(
				entity_index eid,
				game_context &ctx,
				components::collision &cls
			);
		};
	}
}