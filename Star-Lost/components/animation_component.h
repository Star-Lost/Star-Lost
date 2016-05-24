#pragma once
#include "../animation.h"

namespace ecs
{
	namespace components
	{
		struct animation
		{
			const model::animation *anim;
		};
	}
}