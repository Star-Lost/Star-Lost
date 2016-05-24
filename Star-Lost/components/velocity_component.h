#pragma once
#include <SFML/System/Vector2.hpp>

namespace ecs
{
	namespace components
	{
		struct velocity : public sf::Vector2f
		{
			velocity() = default;
			velocity(float x, float y);
		};
	}
}