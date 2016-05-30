#include "../game_context.h"

using namespace ecs;

void systems::tent::initialize(game_context &ctx)
{
	sound.setBuffer(*ctx.get_director().get_soundbuffers().load_resource("toot.wav"));
}

void systems::tent::update(
	entity_index eid, 
	game_context &ctx, 
	components::collision &cols,
	components::timer &timers)
{
	auto &timer = timers.timers["fart_sound"];
	if (cols.collisions.size() > 0 && timer.getElapsedTime().asSeconds() > 1)
	{
		timer.restart();
		sound.play();		
	}
}