#include <SFML/Window/Keyboard.hpp>
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
		struct control : public base_system
		{
			using required = mpl::type_list<
				components::velocity,
				components::animation,
				ecs::tags::player
			>;

			// This is the variable we store the chosen animation in
			// until we can apply it during the next update()
			const rendering::animation *change_anim;
			sf::Vector2f target_vel;
			sf::Keyboard keyboard;

			control();

			void update(
				entity_index eid,
				game_context &ctx,
				components::velocity &vel,
				components::animation &anim
			);

			void handle_event(
				scene_director &director, 
				const sf::Event &evt
			);
		};
	}
}