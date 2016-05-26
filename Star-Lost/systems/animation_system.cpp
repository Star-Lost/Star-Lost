#include "../game_context.h"

using namespace ecs;

void systems::animation::update(
	entity_index eid, 
	game_context &ctx,
	components::animation &anim,
	components::drawable &frame
) {
	
	if (anim.anim == nullptr)
		return;

	anim.runtime += ctx.get_delta();
	frame.frame = &(*anim.anim)[int(anim.runtime) / 50];
}