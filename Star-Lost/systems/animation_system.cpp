#include "../game_context.h"
#include <iostream>

using namespace ecs;

void systems::animation::update(
	std::size_t entity_index, 
	game_context &ctx,
	components::animation &anim, 
	components::sprite &spr
) {
	anim.runtime += ctx.get_delta();
	spr.setTextureRect((*anim.anim)[int(anim.runtime) / 50].get_subtexture());
}