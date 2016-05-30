#pragma once

namespace ecs
{
	namespace tags
	{
		struct tent {};
	}

	namespace systems
	{
		struct tent : public base_system
		{
			using required = mpl::type_list<
				components::collision,
				components::timer,
				tags::tent
			>;

			sf::Sound sound;

			void initialize(game_context &ctx);

			void update(
				entity_index eid,
				game_context &ctx,
				components::collision &cls,
				components::timer &timers
			);
		};
	}
}