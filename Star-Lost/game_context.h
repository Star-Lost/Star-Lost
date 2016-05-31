#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

struct game_context;

#include "entity.h"
#include "scene_director.h"

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
#include "components/timer_component.h"

#include "systems/base_system.h"
#include "systems/velocity_system.h"
#include "systems/animation_system.h"
#include "systems/render_system.h"
#include "systems/control_system.h"
#include "systems/collision_detection_system.h"
#include "systems/collision_resolution_system.h"

#include "systems/tent_system.h"
#include "systems/lamp_system.h"

struct game_context : public ecs::context<ecs::settings<
	// components
	mpl::type_list<
		ecs::components::timer,
		ecs::components::collision,
		ecs::components::position,
		ecs::components::velocity,
		ecs::components::drawable,
		ecs::components::animation
	>,

	// tags
	mpl::type_list<
		ecs::tags::player,
		ecs::tags::tent,
		ecs::tags::lamp
	>,

	// systems
	mpl::type_list<
		ecs::systems::control,
		ecs::systems::collision_detection,
		ecs::systems::tent,
		ecs::systems::collision_resolution,
		ecs::systems::velocity,
		ecs::systems::animation,
		ecs::systems::render
	>
	>>
{
private:
	float delta_time;
	scene_director &director;

public:
	game_context(scene_director &dir);

	void update(float dt);
	scene_director &get_director();
	float get_delta() const;
};