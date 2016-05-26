#include "game_scene.h"

// Prototypes
void create_character_model(resource<sf::Texture> &textures, resource<model> &models);


game_scene::game_scene(scene_director &director) :
	ctx(director.get_window())
{
	create_character_model(director.get_textures(), director.get_models());
	auto &char_model = *director.get_models().get_resource("char_model");

	// Set up the character entity
	auto ply = ctx.create_entity();
	ctx.add_component<ecs::components::position>(ply, 50.0f, 50.0f);
	ctx.add_component<ecs::components::velocity>(ply);
	auto &sprt = ctx.add_component<ecs::components::sprite>(ply);
	auto &anim = (ctx.add_component<ecs::components::animation>(ply).anim);

	ctx.add_tag<ecs::tags::player>(ply);

	sprt.setTexture(*director.get_textures().get_resource("character.png"));
	anim = char_model["stand_south"];

	// Create a tent entity
	const sf::Texture *tex = director.get_textures().load_resource("Spritesheet/roguelikeSheet_magenta.png");

	// Build a tent from our spritesheet
	sf::Image sheet = tex->copyToImage();
	sf::Image tent;
	tent.create(31, 32);
	tent.copy(sheet,  0,  0, sf::IntRect{ 783, 170, 16, 16 });
	tent.copy(sheet, 15,  0, sf::IntRect{ 799, 170, 16, 16 });
	tent.copy(sheet,  0, 16, sf::IntRect{ 783, 187, 16, 16 });
	tent.copy(sheet, 15, 16, sf::IntRect{ 799, 187, 16, 16 });

	sf::Texture tent_tex;
	tent_tex.loadFromImage(tent);
	const sf::Texture *tent_final = director.get_textures().set_resource("green_tent", tent_tex);

	auto tnt = ctx.create_entity();
	ctx.add_component<ecs::components::position>(tnt, 100.0f, 80.0f);
	auto &tspr = ctx.add_component<ecs::components::sprite>(tnt);
	tspr.setTexture(*tent_final);
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


void create_character_model(resource<sf::Texture> &textures, resource<model> &models)
{
	auto char_tex = textures.load_resource("character.png");

	models.set_resource("char_model", model{
		// Standing still facing south animation
		std::make_pair(std::string{ "stand_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 0, 16, 16)}
		}),

		// Standing still facing north animation
		std::make_pair(std::string{ "stand_north" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(16, 0, 16, 16)}
		}),

		// Standing still facing west animation
		std::make_pair(std::string{ "stand_west" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(32, 0, 16, 16)}
		}),

		// Standing still facing east animation
		std::make_pair(std::string{ "stand_east" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(48, 0, 16, 16)}
		}),

		// Walk south animation
		std::make_pair(std::string{ "walk_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 16, 16, 16) },
			{ char_tex, sf::IntRect(0, 32, 16, 16) },
			{ char_tex, sf::IntRect(0,  0, 16, 16) },
			{ char_tex, sf::IntRect(0, 48, 16, 16) },
			{ char_tex, sf::IntRect(0, 64, 16, 16) },
			{ char_tex, sf::IntRect(0,  0, 16, 16) }
		}),

		// Walk north animation
		std::make_pair(std::string{ "walk_north" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(16, 16, 16, 16) },
			{ char_tex, sf::IntRect(16, 32, 16, 16) },
			{ char_tex, sf::IntRect(16,  0, 16, 16) },
			{ char_tex, sf::IntRect(16, 48, 16, 16) },
			{ char_tex, sf::IntRect(16, 64, 16, 16) },
			{ char_tex, sf::IntRect(16,  0, 16, 16) }
		}),

		// Walk west animation
		std::make_pair(std::string{ "walk_west" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(32, 16, 16, 16) },
			{ char_tex, sf::IntRect(32, 32, 16, 16) },
			{ char_tex, sf::IntRect(32,  0, 16, 16) },
			{ char_tex, sf::IntRect(32, 48, 16, 16) },
			{ char_tex, sf::IntRect(32, 64, 16, 16) },
			{ char_tex, sf::IntRect(32,  0, 16, 16) }
		}),

		// Walk east animation
		std::make_pair(std::string{ "walk_east" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(48, 16, 16, 16) },
			{ char_tex, sf::IntRect(48, 32, 16, 16) },
			{ char_tex, sf::IntRect(48,  0, 16, 16) },
			{ char_tex, sf::IntRect(48, 48, 16, 16) },
			{ char_tex, sf::IntRect(48, 64, 16, 16) },
			{ char_tex, sf::IntRect(48,  0, 16, 16) }
		})
	});
}