#include "../game_context.h"
#include "base_entity.h"
#include "wall_entity.h"

using namespace ecs;

entities::wall::wall(game_context &ctx, entity_index eid) :
	base(ctx, eid)
{}

entities::wall::wall(game_context &ctx, const char *frame, float x, float y) :
	base(ctx)
{
	auto &wall_model = *ctx.get_director().get_models().get_resource("wall");

	ctx.add_tag<ecs::tags::structure>(id);
	ctx.add_component<ecs::components::position>(id, x, y);
	ctx.add_component<ecs::components::collision>(id, components::collision::static_mass, sf::FloatRect{ 0, 0, 16, 16 });

	auto &tdrw = ctx.add_component<ecs::components::drawable>(id);
	tdrw.texture = ctx.get_director().get_textures().get_resource("Spritesheet/roguelikeSheet_magenta.png");
	tdrw.frame = &(*wall_model[frame])[0];
}