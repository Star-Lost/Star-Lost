#pragma once

namespace ecs
{
	namespace systems
	{
		struct base_system
		{
			void initialize(game_context &ctx) const {}
		};
	}
}