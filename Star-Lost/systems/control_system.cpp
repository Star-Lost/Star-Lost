#include "../scene_director.h"
#include "../game_context.h"

#include <SFML/Window/Event.hpp>
#include <math.h>

using namespace ecs;

static const float player_speed = 0.1f;
static const float pi = 3.14159265358979323846f;

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

	// By adding epsilon here (the smallest value a float can have),
	// we make sure that magnitude is never 0, 
	// which would make player_speed/magnitude = inf
	// and send the guy to the fucking moon.
	// We *could* check if magnitude is zero with an if, 
	// but this way we can achieve the same effect without branching
	float magnitude = (std::pow(target_vel.x, 2) + std::pow(target_vel.y, 2)) + std::numeric_limits<float>::epsilon();
	target_vel *= std::pow(player_speed, 2) / magnitude;

	// Slowly approach the target velocity
	vel += (target_vel - vel) * 0.1f;

	// Update the direction we're facing based on velocity
	auto &mdl = *ctx.get_director().get_models().get_resource("character");

	float angle = std::atan2f(vel.y, vel.x);
	// Get a range of [0..1] instead of [-pi..pi]
	float range = (angle + pi) / (2 * pi);
	// Offset it by 1/16th so it corresponds to our animations:
	float offset = range + (1.0f / 16.0f);
	// Calculate the index in our array:
	int index = static_cast<int>(std::floor(offset * 8.0f)) % 8;

	std::string directions[] = {
		"west",
		"nw",
		"north",
		"ne",
		"east",
		"se",
		"south",
		"sw"
	};

	std::string direction = directions[index];
	std::string stance = (magnitude > std::numeric_limits<float>::epsilon()) ? "walk_" : "idle_";

	change_anim = mdl[stance + direction];
	
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