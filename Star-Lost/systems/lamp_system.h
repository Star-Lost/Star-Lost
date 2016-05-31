#pragma once
#include "../entities/lamp_entity.h"

namespace ecs
{
	namespace systems
	{
		struct lamp : public base_system
		{
			using required = mpl::type_list<
				components::collision,
				tags::furniture
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