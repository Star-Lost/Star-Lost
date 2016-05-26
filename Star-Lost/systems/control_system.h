#pragma once

namespace sf
{
	class Event;
}

class scene_director;

namespace ecs
{
	namespace systems
	{
		struct control
		{
			using required = mpl::type_list<
				components::velocity,
				components::animation,
				ecs::tags::player
			>;

			// This is the variable we store the chosen animation in
			// until we can apply it during the next update()
			const model::animation *change_anim;

			control();

			void update(
				entity_index eid,
				game_context &ctx,
				components::velocity &vel,
				components::animation &anim
			);

			void handle_event(scene_director &director, const sf::Event &evt);
		};
	}
}