#include "game_scene.h"

using namespace ecs;

// Prototypes
void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models);
void create_player(game_context &ctx, scene_director &director);
void create_tent(game_context &ctx, scene_director &director);

game_scene::game_scene(scene_director &director) :
	ctx(director)
{
	create_models(director.get_textures(), director.get_models());

	create_player(ctx, director);
	create_tent(ctx, director);

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
	case sf::Event::Closed: director.get_window().close(); break;
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
		ctx.get_system<ecs::systems::control>().handle_event(director, evt);
		break;
	}

}

void game_scene::update(scene_director &director, float dt)
{
	director.get_window().clear(sf::Color(100, 149, 237));

	ctx.update(dt);
	ctx.get_system<ecs::systems::render>().draw(director, director.get_window());

	ctx.for_entities<ecs::tags::player>([this](ecs::entity_index eid) {
		this->camera.move(
			this->ctx.get_component<components::position>(eid).x,
			this->ctx.get_component<components::position>(eid).y);
	});
	
	director.get_window().display();
}

void create_player(game_context &ctx, scene_director &director)
{
	auto &char_model = *director.get_models().get_resource("char_model");

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

void create_character_model(resource<sf::Texture> &textures, resource<rendering::model> &models);
void create_tent_model(resource<sf::Texture> &textures, resource<rendering::model> &models);

void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models)
{
	create_character_model(textures, models);
	create_tent_model(textures, models);
}

void create_character_model(resource<sf::Texture> &textures, resource<rendering::model> &models)
{
	using namespace rendering;

	auto char_tex = textures.load_resource("character.png");

	auto char_model = rendering::model{ char_tex, {
		model::named_animation{ std::string{ "idle_south" },	animation{ frame{ layer{ row{ sf::IntRect{ 0,	0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_north" },	animation{ frame{ layer{ row{ sf::IntRect{ 16,  0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_west" },		animation{ frame{ layer{ row{ sf::IntRect{ 32,  0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_east" },		animation{ frame{ layer{ row{ sf::IntRect{ 48,  0, 16, 16 } } } } } },

		model::named_animation{ std::string{ "idle_nw" },		animation{ frame{ layer{ row{ sf::IntRect{ 64,   0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_ne" },		animation{ frame{ layer{ row{ sf::IntRect{ 80,   0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_sw" },		animation{ frame{ layer{ row{ sf::IntRect{ 96,   0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_se" },		animation{ frame{ layer{ row{ sf::IntRect{ 112,  0, 16, 16 } } } } } },
		
		model::named_animation{std::string{"walk_south"}, animation{
			frame{ layer{ row{ sf::IntRect{0, 16, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{0, 32, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{0,  0, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{0, 48, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{0, 64, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{0,  0, 16, 16} } } }
		} },

		model::named_animation{ std::string{ "walk_north" }, animation{
			frame{ layer{ row{ sf::IntRect{16, 16, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{16, 32, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{16,  0, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{16, 48, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{16, 64, 16, 16} } } },
			frame{ layer{ row{ sf::IntRect{16,  0, 16, 16} } } }
		} },

		model::named_animation{ std::string{ "walk_west" }, animation{
			frame{ layer{ row{ sf::IntRect{ 32, 16, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 32, 32, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 32,  0, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 32, 48, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 32, 64, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 32,  0, 16, 16 } } } }
		} },

		model::named_animation{ std::string{ "walk_east" }, animation{
			frame{ layer{ row{ sf::IntRect{ 48, 16, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 48, 32, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 48,  0, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 48, 48, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 48, 64, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 48,  0, 16, 16 } } } }
		} },

		model::named_animation{ std::string{ "walk_nw" }, animation{
			frame{ layer{ row{ sf::IntRect{ 64, 16, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 64, 32, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 64,  0, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 64, 48, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 64, 64, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 64,  0, 16, 16 } } } }
		} },

		model::named_animation{ std::string{ "walk_ne" }, animation{
			frame{ layer{ row{ sf::IntRect{ 80, 16, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 80, 32, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 80,  0, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 80, 48, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 80, 64, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 80,  0, 16, 16 } } } }
		} },

		model::named_animation{ std::string{ "walk_sw" }, animation{
			frame{ layer{ row{ sf::IntRect{ 96, 16, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 96, 32, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 96,  0, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 96, 48, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 96, 64, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 96,  0, 16, 16 } } } }
		} },

		model::named_animation{ std::string{ "walk_se" }, animation{
			frame{ layer{ row{ sf::IntRect{ 112, 16, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 112, 32, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 112,  0, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 112, 48, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 112, 64, 16, 16 } } } },
			frame{ layer{ row{ sf::IntRect{ 112,  0, 16, 16 } } } }
		} }
	} };

	models.set_resource("char_model", char_model);
}

void create_tent_model(resource<sf::Texture> &textures, resource<rendering::model> &models)
{
	using namespace rendering;

	auto tent_tex = textures.load_resource("Spritesheet/roguelikeSheet_magenta.png");

	auto tent_model = rendering::model{ tent_tex,{
		model::named_animation{
			std::string{"idle"},
			animation{ 
				// Frame 0 - only one frame
				frame{
					// Layer 0 - bottom of the tent
					layer{
						// Row 0 - front row
						row{
							sf::IntRect{ 783, 187, 15, 16 },
							sf::IntRect{ 799, 187, 16, 16 }
						}
					},
					// Layer 1 - top of the tent 
					layer{
						row{
							sf::IntRect{ 783, 170, 15, 16 },
							sf::IntRect{ 799, 170, 16, 16 }
						}
					}
				} 
			}
		},
	} };

	models.set_resource("green_tent", tent_model);
}