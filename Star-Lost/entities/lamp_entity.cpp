#include "../game_context.h"
#include "base_entity.h"
#include "lamp_entity.h"

using namespace ecs;

entities::lamp::lamp(game_context &ctx, entity_index eid) :
	base(ctx, eid)
{}

entities::lamp::lamp(game_context &ctx) :
	base(ctx)
{
	auto &lamp_model = *ctx.get_director().get_models().get_resource("lamp");

	ctx.add_tag<ecs::tags::furniture>(id);
	ctx.add_component<ecs::components::position>(id, 200.0f, 200.0f);
	ctx.add_component<ecs::components::collision>(id, sf::FloatRect{ 3, 3, 8, 9 });
	auto &tdrw = ctx.add_component<ecs::components::drawable>(id);
	tdrw.texture = ctx.get_director().get_textures().get_resource("furniture.png");
	tdrw.frame = &(*lamp_model["idle"])[0];
}