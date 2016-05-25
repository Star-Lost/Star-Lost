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

void game_scene::update(scene_director &director)
{
	director.get_window().clear(sf::Color(100, 149, 237));

	ctx.update(float(director.get_clock().getElapsedTime().asMilliseconds()) / 1000.0f);

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