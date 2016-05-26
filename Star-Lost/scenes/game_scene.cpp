#include "game_scene.h"

// Prototypes
void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models);

game_scene::game_scene(scene_director &director) :
	ctx(director.get_window())
{
	create_models(director.get_textures(), director.get_models());

	auto &char_model = *director.get_models().get_resource("char_model");
	auto &tent_model = *director.get_models().get_resource("green_tent");

	// Set up the character entity
	auto ply = ctx.create_entity();
	ctx.add_tag<ecs::tags::player>(ply);

	ctx.add_component<ecs::components::position>(ply, 50.0f, 50.0f);
	ctx.add_component<ecs::components::velocity>(ply);
	auto &draw = ctx.add_component<ecs::components::drawable>(ply);
	auto &anim = (ctx.add_component<ecs::components::animation>(ply).anim);
	draw.texture = director.get_textures().get_resource("character.png");
	anim = char_model["idle_south"];

	// Create a tent entity
	auto tnt = ctx.create_entity();
	ctx.add_component<ecs::components::position>(tnt, 100.0f, 80.0f);
	auto &tdrw = ctx.add_component<ecs::components::drawable>(tnt);
	tdrw.texture = director.get_textures().get_resource("Spritesheet/roguelikeSheet_magenta.png");
	tdrw.frame = &(*tent_model["idle"])[0];
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

	director.get_window().display();
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
		model::named_animation{std::string{"idle_south"},	animation{ frame{ layer{ sf::IntRect{  0,  0, 16, 16 } } } }},
		model::named_animation{std::string{"idle_north"},	animation{ frame{ layer{ sf::IntRect{ 16,  0, 16, 16 } } } }},
		model::named_animation{std::string{"idle_west"},	animation{ frame{ layer{ sf::IntRect{ 32,  0, 16, 16 } } } }},
		model::named_animation{std::string{"idle_east"},	animation{ frame{ layer{ sf::IntRect{ 48,  0, 16, 16 } } } }},

		model::named_animation{std::string{"walk_south"}, animation{
			frame{ layer{ sf::IntRect{0, 16, 16, 16} } },
			frame{ layer{ sf::IntRect{0, 32, 16, 16} } },
			frame{ layer{ sf::IntRect{0,  0, 16, 16} } },
			frame{ layer{ sf::IntRect{0, 48, 16, 16} } },
			frame{ layer{ sf::IntRect{0, 64, 16, 16} } },
			frame{ layer{ sf::IntRect{0,  0, 16, 16} } }
		} },

		model::named_animation{ std::string{ "walk_north" }, animation{
			frame{ layer{ sf::IntRect{16, 16, 16, 16} } },
			frame{ layer{ sf::IntRect{16, 32, 16, 16} } },
			frame{ layer{ sf::IntRect{16,  0, 16, 16} } },
			frame{ layer{ sf::IntRect{16, 48, 16, 16} } },
			frame{ layer{ sf::IntRect{16, 64, 16, 16} } },
			frame{ layer{ sf::IntRect{16,  0, 16, 16} } }
		} },

		model::named_animation{ std::string{ "walk_west" }, animation{
			frame{ layer{ sf::IntRect{ 32, 16, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 32, 32, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 32,  0, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 32, 48, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 32, 64, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 32,  0, 16, 16 } } }
		} },

		model::named_animation{ std::string{ "walk_east" }, animation{
			frame{ layer{ sf::IntRect{ 48, 16, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 48, 32, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 48,  0, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 48, 48, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 48, 64, 16, 16 } } },
			frame{ layer{ sf::IntRect{ 48,  0, 16, 16 } } }
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
				// Frame 0, only one frame
				frame{
					// Layer 0 (bottom of the tent)
					layer{
						sf::IntRect{ 783, 187, 16, 16 },
						sf::IntRect{ 799, 187, 16, 16 }
					},
					// Layer 1 (top of the tent)
					layer{
						sf::IntRect{ 783, 170, 16, 16 },
						sf::IntRect{ 799, 170, 16, 16 }
					}
				} 
			}
		},
	} };

	models.set_resource("green_tent", tent_model);
}