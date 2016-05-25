#include "../scene_director.h"
#include "../game_context.h"

#include <SFML/Window/Event.hpp>

using namespace ecs;

systems::control::control() :
	change_anim(nullptr)
{

}

void systems::control::update(
	entity_index eid,
	game_context &ctx,
	components::animation &anim
) {
	// If we have a new animation lined up, apply it.
	if (change_anim == nullptr)
		return;
	
	anim.anim = change_anim;
	anim.runtime = 0;
	change_anim = nullptr;
}

void systems::control::handle_event(scene_director &director, const sf::Event &evt)
{
	if (evt.type != sf::Event::KeyPressed && evt.type != sf::Event::KeyReleased)
		return;

	const model &mdl = *director.get_models().get_resource("char_model");

	switch (evt.type)
	{
	case sf::Event::KeyPressed:
	{
		switch (evt.key.code)
		{
		case sf::Keyboard::W: change_anim = mdl["walk_north"]; break;
		case sf::Keyboard::A: change_anim = mdl["walk_west"]; break;
		case sf::Keyboard::S: change_anim = mdl["walk_south"]; break;
		case sf::Keyboard::D: change_anim = mdl["walk_east"]; break;
		default: break;
		}
		break;
	}

	case sf::Event::KeyReleased:
	{
		switch (evt.key.code)
		{
		case sf::Keyboard::W: change_anim = mdl["stand_north"]; break;
		case sf::Keyboard::A: change_anim = mdl["stand_west"]; break;
		case sf::Keyboard::S: change_anim = mdl["stand_south"]; break;
		case sf::Keyboard::D: change_anim = mdl["stand_east"]; break;
		default: break;
		}

		break;
	}
	}
}