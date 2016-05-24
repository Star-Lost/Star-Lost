#pragma once
#include <SFML/System/Vector2.hpp>

namespace ecs
{
	namespace components
	{
		struct position : public sf::Vector2f
		{
			position() = default;
			position(float x, float y);
		};
	}
}