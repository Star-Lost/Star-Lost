#pragma once

namespace ecs
{
	namespace components
	{
		struct timer
		{
			std::map<std::string, sf::Clock> timers;
		};
	}
}