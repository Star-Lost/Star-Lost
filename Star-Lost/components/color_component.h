#pragma once

namespace ecs
{
	namespace components
	{
		struct color : public sf::Color
		{
			color(
				unsigned char red = 0,
				unsigned char green = 0,
				unsigned char blue = 0,
				unsigned char alpha = 255
			);
		};
	}
}