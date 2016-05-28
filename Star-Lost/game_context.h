#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

struct game_context;

#include "entity.h"

namespace ecs
{
	namespace tags
	{
		struct player {};
	}
}

#include "components/collision_component.h"
#include "components/position_component.h"
#include "components/velocity_component.h"
#include "components/drawable_component.h"
#include "components/animation_component.h"
#include "components/camera_component.h"

#include "systems/collision_system.h"
#include "systems/velocity_system.h"
#include "systems/animation_system.h"
#include "systems/render_system.h"
#include "systems/control_system.h"

struct game_context : public ecs::context<ecs::settings<
	// components
	mpl::type_list<
		ecs::components::collision,
		ecs::components::position,
		ecs::components::velocity,
		ecs::components::drawable,
		ecs::components::animation
	>,

	// tags
	mpl::type_list<
		ecs::tags::player
	>,

	// systems
	mpl::type_list<
		ecs::systems::control,
		ecs::systems::collision,
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