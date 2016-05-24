#pragma once
#include "../animation.h"

namespace ecs
{
	namespace components
	{
		struct animation
		{
			std::string cur_model;
			std::string cur_anim;
		};
	}
}