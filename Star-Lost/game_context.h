#pragma once

#include "entity.h"

#include "components/position_component.h"
#include "components/velocity_component.h"

#include "systems/velocity_system.h"

struct game_context : public ecs::context<ecs::settings<
	// components
	mpl::type_list<
		ecs::components::position,
		ecs::components::velocity
	>,
	// tags
	mpl::type_list<>,
	// systems
	mpl::type_list<
		ecs::systems::velocity
	>
	>>
{
	
};