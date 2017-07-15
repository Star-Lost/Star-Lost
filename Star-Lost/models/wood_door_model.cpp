#include "../scenes/game_scene.h"
#include "../animation.h"

rendering::model create_wood_door_model(resource<sf::Texture> &textures)
{
	using namespace rendering;

	return model{
		model::named_animation{
			std::string{ "closed" },
			animation{
				// Frame 0 - only one frame
				frame{
					// Layer 0 - bottom of the lamp
					layer{
						// Row 0 - front row
						row{
							sf::IntRect{ 35*16, 1*16, 16, 16 }
						}
					}
				}
			}
		}
	};
}