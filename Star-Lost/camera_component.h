#pragma once
#include <SFML/System/Vector2.hpp>
#include "entity.h"

namespace ecs
{
	namespace components {
		class camera {
		public:
			camera();
			
			sf::Vector2f &get_position();
			sf::Vector2f &get_render_area();
			bool is_active();
			void follow_entity(ecs::entity);
		private:
			sf::Vector2f position;
			sf::Vector2f render_area; // Area we will see when rendering things
			bool active; // Only one camera should ever be active at once.
			ecs::entity *following; // Usually follows the player
		};
	}
}
