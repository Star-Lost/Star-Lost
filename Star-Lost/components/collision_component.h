#pragma once

namespace ecs
{
	namespace components
	{
		struct collision
		{
			static constexpr float static_mass = std::numeric_limits<float>::infinity();

			enum collision_edge : int {
				north,
				south,
				east,
				west
			};

			struct collision_event {
				entity_index aid;
				entity_index bid;
				collision_edge edge;
				sf::FloatRect overlap;
				sf::Vector2f force;

				collision_event(
					entity_index aid, 
					entity_index bid, 
					collision_edge edge, 
					sf::FloatRect overlap,
					sf::Vector2f force)
				:
					aid(aid),
					bid(bid),
					edge(edge),
					overlap(overlap),
					force(force)
				{

				}
			};

			float mass;
			sf::FloatRect bbox;
			std::vector<collision_event> collisions;
		};
	}
}