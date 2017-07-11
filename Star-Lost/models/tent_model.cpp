#include "../scenes/game_scene.h"
#include "../animation.h"

rendering::model create_tent_model(resource<sf::Texture> &textures)
{
	using namespace rendering;

	auto tent_tex = textures.load_resource("Spritesheet/roguelikeSheet_magenta.png");

	return model{ tent_tex,{
		model::named_animation{
			std::string{ "idle" },
			animation{
				// Frame 0 - only one frame
				frame{
				// Layer 0 - bottom of the tent
					layer{
						sf::IntRect{ 783, 187, 15, 16 },
						sf::IntRect{ 799, 187, 16, 16 }
					},
					// Layer 1 - top of the tent 
					layer{
						sf::IntRect{ 783, 170, 15, 16 },
						sf::IntRect{ 799, 170, 16, 16 }
					}
				}
			}
		},
	} };
}