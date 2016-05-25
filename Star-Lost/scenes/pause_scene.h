#pragma once
#include "../scene.h"

class pause_scene : public scene
{
public:
	void virtual update(scene_director &director) override;
};
