#include "../game_context.h"
#include "base_entity.h"
#include "tent_entity.h"

using namespace ecs;

entities::tent::tent(game_context &ctx, entity_index eid) :
	base(ctx, eid)
{}

entities::tent::tent(game_context &ctx) :
	base(ctx)
{
	auto &tent_model = *ctx.get_director().get_models().get_resource("green_tent");

	ctx.add_component<ecs::components::timer>(id);
	ctx.add_component<ecs::components::position>(id, 100.0f, 80.0f);
	ctx.add_component<ecs::components::collision>(id, components::collision::static_mass, sf::FloatRect{ 0, 0, 31, 16 });
	auto &tdrw = ctx.add_component<ecs::components::drawable>(id);
	tdrw.texture = ctx.get_director().get_textures().get_resource("Spritesheet/roguelikeSheet_magenta.png");
	tdrw.frame = &(*tent_model["idle"])[0];
}