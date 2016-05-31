#include "../scenes/game_scene.h"
#include "../animation.h"

rendering::model create_player_model(resource<sf::Texture> &textures)
{
	using namespace rendering;

	auto char_tex = textures.load_resource("character.png");

	return model{ char_tex,{
		model::named_animation{ std::string{ "idle_south" },	animation{ frame{ layer{ row{ sf::IntRect{ 0,	0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_north" },	animation{ frame{ layer{ row{ sf::IntRect{ 16,  0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_west" },		animation{ frame{ layer{ row{ sf::IntRect{ 32,  0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_east" },		animation{ frame{ layer{ row{ sf::IntRect{ 48,  0, 16, 16 } } } } } },

		model::named_animation{ std::string{ "idle_nw" },		animation{ frame{ layer{ row{ sf::IntRect{ 64,   0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_ne" },		animation{ frame{ layer{ row{ sf::IntRect{ 80,   0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_sw" },		animation{ frame{ layer{ row{ sf::IntRect{ 96,   0, 16, 16 } } } } } },
		model::named_animation{ std::string{ "idle_se" },		animation{ frame{ layer{ row{ sf::IntRect{ 112,  0, 16, 16 } } } } } },

		model::named_animation{ std::string{ "walk_south" }, animation{
		frame{ layer{ row{ sf::IntRect{ 0, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 0, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 0,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 0, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 0, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 0,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_north" }, animation{
		frame{ layer{ row{ sf::IntRect{ 16, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 16, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 16,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 16, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 16, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 16,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_west" }, animation{
		frame{ layer{ row{ sf::IntRect{ 32, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 32, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 32,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 32, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 32, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 32,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_east" }, animation{
		frame{ layer{ row{ sf::IntRect{ 48, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 48, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 48,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 48, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 48, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 48,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_nw" }, animation{
		frame{ layer{ row{ sf::IntRect{ 64, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 64, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 64,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 64, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 64, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 64,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_ne" }, animation{
		frame{ layer{ row{ sf::IntRect{ 80, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 80, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 80,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 80, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 80, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 80,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_sw" }, animation{
		frame{ layer{ row{ sf::IntRect{ 96, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 96, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 96,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 96, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 96, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 96,  0, 16, 16 } } } }
	} },

		model::named_animation{ std::string{ "walk_se" }, animation{
		frame{ layer{ row{ sf::IntRect{ 112, 16, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 112, 32, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 112,  0, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 112, 48, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 112, 64, 16, 16 } } } },
		frame{ layer{ row{ sf::IntRect{ 112,  0, 16, 16 } } } }
	} }
	} };
}