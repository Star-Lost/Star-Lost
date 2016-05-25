#pragma once
#include "../scene_director.h"

class pause_scene : public scene
{
public:
	virtual void handle_event(const sf::Event &evt) override;
	virtual void update(scene_director &director) override;
};
