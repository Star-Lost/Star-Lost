#include "../game_context.h"
#include "base_entity.h"
#include "player_entity.h"

using namespace ecs;

entities::player::player(game_context &ctx, entity_index eid) :
	base(ctx, eid)
{}

entities::player::player(game_context &ctx) :
	base(ctx)
{
	auto &char_model = *ctx.get_director().get_models().get_resource("character");

	// Set up the character entity
	ctx.add_tag<ecs::tags::player>(id);
	ctx.add_component<ecs::components::position>(id, 50.0f, 50.0f);
	ctx.add_component<ecs::components::velocity>(id);
	ctx.add_component<ecs::components::collision>(id, sf::FloatRect{ 2, 8, 12, 8 });
	auto &draw = ctx.add_component<ecs::components::drawable>(id);
	auto &anim = (ctx.add_component<ecs::components::animation>(id).anim);
	draw.texture = ctx.get_director().get_textures().get_resource("character.png");
	anim = char_model["idle_south"];
}

components::position &entities::player::get_position() const
{
	return ctx.get_component<components::position>(id);
}