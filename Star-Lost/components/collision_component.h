#pragma once

namespace ecs
{
	namespace components
	{
		struct collision
		{
			enum collision_edge : int {
				north,
				south,
				east,
				west
			};

			sf::FloatRect bbox;

			struct collision_event {
				entity_index aid;
				entity_index bid;
				collision_edge edge;
				sf::FloatRect overlap;

				collision_event(
					entity_index aid, 
					entity_index bid, 
					collision_edge edge, 
					sf::FloatRect overlap) 
				:
					aid(aid),
					bid(bid),
					edge(edge),
					overlap(overlap)					
				{

				}
			};

			std::vector<collision_event> collisions;
		};
	}
}