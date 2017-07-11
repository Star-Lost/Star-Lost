#include "../scenes/game_scene.h"
#include "../animation.h"

rendering::model create_wall_model(resource<sf::Texture> &textures)
{
	using namespace rendering;

	auto tex = textures.load_resource("Spritesheet/roguelikeSheet_magenta.png");

	return model{ tex,{
		model::named_animation{ // right
			std::string{ "0100" },
			animation{
				frame{ sf::IntRect{ 221, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 340, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 459, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 579, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // horizontal
			std::string{ "0101" },
			animation{
				frame{ sf::IntRect{ 238, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 357, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 476, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 596, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // left
			std::string{ "0001" },
			animation{
				frame{ sf::IntRect{ 255, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 374, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 493, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 613, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // top left corner
			std::string{ "0110" },
			animation{
				frame{ sf::IntRect{ 272, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 391, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 510, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 630, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // top right corner
			std::string{ "0011" },
			animation{
				frame{ sf::IntRect{ 289, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 408, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 527, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 647, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // t-section right
			std::string{ "1110" },
			animation{
				frame{ sf::IntRect{ 306, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 425, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 544, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 664, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // t-section up
			std::string{ "1101" },
			animation{
				frame{ sf::IntRect{ 323, 204, 16, 16 } }, // sand
				frame{ sf::IntRect{ 442, 204, 16, 16 } }, // stone
				frame{ sf::IntRect{ 561, 204, 16, 16 } }, // metal
				frame{ sf::IntRect{ 681, 204, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // down
			std::string{ "0010" },
			animation{
				frame{ sf::IntRect{ 221, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 340, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 459, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 579, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // cross
			std::string{ "1111" },
			animation{
				frame{ sf::IntRect{ 238, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 357, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 476, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 596, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // vertical
			std::string{ "1010" },
			animation{
				frame{ sf::IntRect{ 255, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 374, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 493, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 613, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // bottom left corner
			std::string{ "1100" },
			animation{
				frame{ sf::IntRect{ 272, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 391, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 510, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 630, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // bottom right corner
			std::string{ "1001" },
			animation{
				frame{ sf::IntRect{ 289, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 408, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 527, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 647, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // t-section left
			std::string{ "1011" },
			animation{
				frame{ sf::IntRect{ 306, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 425, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 544, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 664, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // t-section down
			std::string{ "0111" },
			animation{
				frame{ sf::IntRect{ 323, 221, 16, 16 } }, // sand
				frame{ sf::IntRect{ 442, 221, 16, 16 } }, // stone
				frame{ sf::IntRect{ 561, 221, 16, 16 } }, // metal
				frame{ sf::IntRect{ 681, 221, 16, 16 } }  // wood
			}
		},

		model::named_animation{ // up
			std::string{ "1000" },
			animation{
				frame{ sf::IntRect{ 221, 238, 16, 16 } }, // sand
				frame{ sf::IntRect{ 340, 238, 16, 16 } }, // stone
				frame{ sf::IntRect{ 459, 238, 16, 16 } }, // metal
				frame{ sf::IntRect{ 579, 238, 16, 16 } }  // wood
			}
		}
	} };
}