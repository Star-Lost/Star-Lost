#include "../game_context.h"
#include "base_entity.h"
#include "wood_door_entity.h"

using namespace ecs;

entities::wood_door::wood_door(game_context &ctx, entity_index eid) :
	base(ctx, eid)
{}

entities::wood_door::wood_door(game_context &ctx, const char *frame, float x, float y) :
	base(ctx)
{
	auto &wood_door_model = *ctx.get_director().get_models().get_resource("wood_door");

	ctx.add_tag<ecs::tags::structure>(id);
	ctx.add_component<ecs::components::position>(id, x, y);
	ctx.add_component<ecs::components::collision>(id, components::collision::static_mass, sf::FloatRect{ 0, 0, 16, 16 });
	//ctx.add_component<ecs::components::color>(id, 255, 0, 0, 255);

	auto &tdrw = ctx.add_component<ecs::components::drawable>(id);
	tdrw.texture = ctx.get_director().get_textures().get_resource("Spritesheet/roguelikeSheet_magenta.png");
	tdrw.frame = &(*wood_door_model[frame])[0];
}