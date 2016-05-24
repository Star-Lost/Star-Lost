#include "../game_context.h"

using namespace ecs;

void systems::render::update(
	std::size_t entity_index,
	game_context &ctx,
	components::position &pos,
	components::sprite &spr
) const {
	spr.setPosition(pos);
	ctx.get_render_target().draw(spr);
}