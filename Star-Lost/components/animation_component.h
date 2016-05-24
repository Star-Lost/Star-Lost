#pragma once
#include "../animation.h"

namespace ecs
{
	namespace components
	{
		struct animation
		{
			animation();

			float runtime;
			const model::animation *anim;
		};
	}
}