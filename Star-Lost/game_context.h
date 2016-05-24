#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

struct game_context;

#include "entity.h"

#include "components/position_component.h"
#include "components/velocity_component.h"
#include "components/sprite_component.h"
#include "components/animation_component.h"

#include "systems/velocity_system.h"
#include "systems/animation_system.h"
#include "systems/render_system.h"

struct player_tag {};

struct game_context : public ecs::context<ecs::settings<
	// components
	mpl::type_list<
		ecs::components::position,
		ecs::components::velocity,
		ecs::components::animation,
		ecs::components::sprite
	>,

	// tags
	mpl::type_list<
		player_tag
	>,

	// systems
	mpl::type_list<
		ecs::systems::velocity,
		ecs::systems::animation,
		ecs::systems::render
	>
	>>
{
private:
	float delta_time;
	sf::RenderTarget &render_target;

public:
	game_context(sf::RenderTarget &target);

	void update(float dt);

	float get_delta() const;
	sf::RenderTarget &get_render_target();
};