#include "../scene_director.h"
#include "../game_context.h"

#include <SFML/Window/Event.hpp>
#include <math.h>

using namespace ecs;

static const float player_speed = 0.1f;

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
	// Handle controls
	target_vel.x = (keyboard.isKeyPressed(keyboard.D) ? player_speed : 0.0f) - (keyboard.isKeyPressed(keyboard.A) ? player_speed : 0.0f);
	target_vel.y = (keyboard.isKeyPressed(keyboard.S) ? player_speed : 0.0f) - (keyboard.isKeyPressed(keyboard.W) ? player_speed : 0.0f);

	// Slowly approach the target velocity
	vel += (target_vel - vel) * 0.1f;

	// Update the direction we're facing based on velocity
	auto &mdl = *ctx.get_director().get_models().get_resource("char_model");
	std::string stance = "idle";
	std::string direction = "south";


	if (abs(vel.x) > abs(vel.y))
	{
		direction = vel.x <= 0.0f ? "west" : "east";
	}
	else
	{
		direction = vel.y <= 0.0f ? "north" : "south";
	}

	if (abs(vel.x) + abs(vel.y) > player_speed / 5.0f)
	{
		stance = "walk";
	}
	else
	{
		stance = "idle";
	}

	change_anim = mdl[stance + "_" + direction];

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

void systems::control::handle_event(
	scene_director &director, 
	const sf::Event &evt)
{
	if (evt.type != sf::Event::KeyPressed && evt.type != sf::Event::KeyReleased)
		return;
}