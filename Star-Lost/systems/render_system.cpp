#include "../game_context.h"

using namespace ecs;

void systems::render::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::sprite &spr
) const {
	spr.setPosition(pos);
	ctx.get_render_target().draw(spr);
}