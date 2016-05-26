#include "../scene_director.h"
#include "../game_context.h"

#include <SFML/Window/Event.hpp>

using namespace ecs;

static const float player_speed = 0.05f;

systems::control::control() :
	change_anim(nullptr),
	target_vel(0, 0)
{

}

void systems::control::update(
	entity_index eid,
	game_context &ctx,
	components::velocity &vel,
	components::animation &anim
) {
	// Slowly approach the target velocity
	vel += (target_vel - vel) * 0.1f;

	// If we have a new animation lined up, apply it.
	if (change_anim == nullptr)
		return;
	
	// If we're already using this animation, don't restart it
	if (anim.anim != change_anim)
	{
		anim.anim = change_anim;
		anim.runtime = 0;
	}
	change_anim = nullptr;
}

void systems::control::handle_event(scene_director &director, const sf::Event &evt)
{
	if (evt.type != sf::Event::KeyPressed && evt.type != sf::Event::KeyReleased)
		return;

	auto &mdl = *director.get_models().get_resource("char_model");

	switch (evt.type)
	{
	case sf::Event::KeyPressed:
	{
		switch (evt.key.code)
		{
		case sf::Keyboard::W: change_anim = mdl["walk_north"]; target_vel = { 		  0.0f,  -player_speed	}; break;
		case sf::Keyboard::A: change_anim = mdl["walk_west"];  target_vel = { -player_speed,  0.0f			}; break;
		case sf::Keyboard::S: change_anim = mdl["walk_south"]; target_vel = {		   0.0f,  player_speed	}; break;
		case sf::Keyboard::D: change_anim = mdl["walk_east"];  target_vel = {  player_speed,  0.0f			}; break;
		default: break;
		}
		break;
	}

	case sf::Event::KeyReleased:
	{
		switch (evt.key.code)
		{
		case sf::Keyboard::W: change_anim = mdl["stand_north"]; target_vel = { 0.0f, 0.0f };  break;
		case sf::Keyboard::A: change_anim = mdl["stand_west"];  target_vel = { 0.0f, 0.0f };  break;
		case sf::Keyboard::S: change_anim = mdl["stand_south"]; target_vel = { 0.0f, 0.0f };  break;
		case sf::Keyboard::D: change_anim = mdl["stand_east"];  target_vel = { 0.0f, 0.0f }; break;
		default: break;
		}

		break;
	}
	}
}