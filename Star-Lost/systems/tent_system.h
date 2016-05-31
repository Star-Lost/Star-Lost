#pragma once
#include "../entities/tent_entity.h"

namespace ecs
{
	namespace systems
	{
		struct tent : public base_system
		{
			using required = mpl::type_list<
				components::collision,
				components::timer,
				tags::structure
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