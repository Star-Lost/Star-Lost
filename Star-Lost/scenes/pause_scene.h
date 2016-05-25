#pragma once
#include "../scene_director.h"

class pause_scene : public scene
{
public:
	void virtual update(scene_director &director) override;
};
