#include "../scenes/game_scene.h"
#include "../animation.h"

rendering::model create_lamp_model(resource<sf::Texture> &textures)
{
	using namespace rendering;

	auto lamp_tex = textures.load_resource("furniture.png");

	return model{
		model::named_animation{
			std::string{ "idle" },
			animation{
				// Frame 0 - only one frame
				frame{
					// Layer 0 - bottom of the lamp
					layer{
						// Row 0 - front row
						row{
							sf::IntRect{ 0, 0, 16, 16 }
						}
					}
				}
			}
		}
	};
}