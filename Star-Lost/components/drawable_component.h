#pragma once
#include "../animation.h"

namespace ecs
{
	namespace components
	{
		struct drawable
		{
			const rendering::frame *frame;
			const sf::Texture *texture;
		};
	}
}