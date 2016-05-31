#include "game_scene.h"

using namespace ecs;

// Prototypes
void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models);
void create_player(game_context &ctx, scene_director &director);
void create_tent(game_context &ctx, scene_director &director);
void create_lamp(game_context &ctx, scene_director &director);

game_scene::game_scene(scene_director &director) :
	ctx(director)
{
	create_models(director.get_textures(), director.get_models());

	create_player(ctx, director);
	create_tent(ctx, director);
	create_lamp(ctx, director);

	// Create a view
	ctx.for_entities<ecs::tags::player>([this](ecs::entity_index eid) {
		this->camera.setCenter(
			this->ctx.get_component<components::position>(eid).x,
			this->ctx.get_component<components::position>(eid).y);
	}); 
	
	camera.setSize(
		static_cast<float>(director.get_window().getSize().x),
		static_cast<float>(director.get_window().getSize().y)
	);

	director.get_window().setView(camera);
}

void game_scene::handle_event(scene_director &director, const sf::Event &evt)
{
	switch (evt.type)
	{
	case sf::Event::Closed: director.get_window().close(); exit(EXIT_SUCCESS); break;
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		ctx.get_system<ecs::systems::control>().handle_event(director, evt);
		break;
	}
}

void game_scene::update(scene_director &director, float dt)
{
	director.get_window().clear(sf::Color(100, 149, 237));

	director.get_window().setView(camera);

	ctx.update(dt);

	sf::VertexArray quad(sf::Quads, 4);

	quad[0].position = sf::Vector2f(0.0f, 0.0f);
	quad[1].position = sf::Vector2f(10.0f, 0.0f);
	quad[2].position = sf::Vector2f(10.0f, 10.0f);
	quad[3].position = sf::Vector2f(0.0f, 10.0f);

	director.get_window().draw(quad);

	ctx.get_system<ecs::systems::render>().draw(director, director.get_window());

	ctx.for_entities<ecs::tags::player>([this](ecs::entity_index eid) {
		this->camera.setCenter(
			this->ctx.get_component<components::position>(eid).x,
			this->ctx.get_component<components::position>(eid).y);
	});

	director.get_window().display();
}

void create_player(game_context &ctx, scene_director &director)
{
	auto &char_model = *director.get_models().get_resource("character");

	// Set up the character entity
	auto ply = ctx.create_entity();
	ctx.add_tag<ecs::tags::player>(ply);

	ctx.add_component<ecs::components::position>(ply, 50.0f, 50.0f);
	ctx.add_component<ecs::components::velocity>(ply);
	ctx.add_component<ecs::components::collision>(ply, sf::FloatRect{ 2, 8, 12, 8 });
	auto &draw = ctx.add_component<ecs::components::drawable>(ply);
	auto &anim = (ctx.add_component<ecs::components::animation>(ply).anim);
	draw.texture = director.get_textures().get_resource("character.png");
	anim = char_model["idle_south"];
}

void create_tent(game_context &ctx, scene_director &director)
{
	auto &tent_model = *director.get_models().get_resource("green_tent");

	// Create a tent entity
	auto tnt = ctx.create_entity();
	ctx.add_tag<ecs::tags::tent>(tnt);
	ctx.add_component<ecs::components::timer>(tnt);
	ctx.add_component<ecs::components::position>(tnt, 100.0f, 80.0f);
	ctx.add_component<ecs::components::collision>(tnt, sf::FloatRect{ 0, 0, 31, 16 });
	auto &tdrw = ctx.add_component<ecs::components::drawable>(tnt);
	tdrw.texture = director.get_textures().get_resource("Spritesheet/roguelikeSheet_magenta.png");
	tdrw.frame = &(*tent_model["idle"])[0];
}

void create_lamp(game_context &ctx, scene_director &director) 
{
	auto &lamp_model = *director.get_models().get_resource("lamp");

	// Create the lamp
	auto lmp = ctx.create_entity();
	ctx.add_tag<ecs::tags::lamp>(lmp);
	ctx.add_component<ecs::components::position>(lmp, 200.0f, 200.0f);
	ctx.add_component<ecs::components::collision>(lmp, sf::FloatRect{ 3, 3, 8, 9 });
	auto &tdrw = ctx.add_component<ecs::components::drawable>(lmp);
	tdrw.texture = director.get_textures().get_resource("furniture.png");
	tdrw.frame = &(*lamp_model["idle"])[0];
}

void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models)
{
	models.set_resource("character", create_player_model(textures));
	models.set_resource("green_tent", create_tent_model(textures));
	models.set_resource("lamp", create_lamp_model(textures));
}
