#include <iostream>

#include "game_scene.h"

#include "../entities/player_entity.h"
#include "../entities/tent_entity.h"
#include "../entities/lamp_entity.h"
#include "../entities/wall_entity.h"

using namespace ecs;

void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models);

game_scene::game_scene(scene_director &director) :
	ctx(director)
{
	create_models(director.get_textures(), director.get_models());

	// Create a new player entity
	entities::player pl{ ctx };
	entities::tent tn{ ctx };
	entities::lamp lmp{ ctx };


	std::array<std::array<const char *, 5>, 5> room = { {
		{ "0110", "0101", "0101", "0101", "0011" },
		{ "1010", "0000", "0000", "0000", "1010" },
		{ "1010", "0000", "0000", "0000", "1010" },
		{ "1010", "0000", "0000", "0000", "1010" },
		{ "1100", "0101", "0101", "0101", "1001" },
	} };

	auto empty = std::string{ "0000" };

	auto y = 0u;
	for (const auto &line : room)
	{
		auto x = 0u;
		for (const auto &wall : line)
		{
			if (empty != wall)
				entities::wall wl{ ctx, wall, (float)x * 16, (float)y * 16 };

			++x;
		}
		
		++y;
	}

	camera.setCenter(pl.get_position());
	
	camera.setSize(
		static_cast<float>(director.get_window().getSize().x),
		static_cast<float>(director.get_window().getSize().y)
	);

	director.get_fonts().load_resource("PIXEARG_.TTF");

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

	sf::Text text;
	text.setFont(*director.get_fonts().get_resource("PIXEARG_.TTF"));
	text.setString("Hello");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(10.0f, 10.0f);
	director.get_window().draw(text);

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

void create_models(resource<sf::Texture> &textures, resource<rendering::model> &models)
{
	models.set_resource("character", create_player_model(textures));
	models.set_resource("green_tent", create_tent_model(textures));
	models.set_resource("lamp", create_lamp_model(textures));
	models.set_resource("wall", create_wall_model(textures));
}
