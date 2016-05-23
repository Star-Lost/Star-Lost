#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resources.h"
#include "animation.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Happiness");
	window.setFramerateLimit(60); // Limit the frame rate to achieve a cinematic feel

	resource<sf::Texture> textures;
	resource<sf::SoundBuffer> sounds;

	// Character animation stuff goes here
	sf::Sprite character;
	auto char_tex = textures.load_resource("character.png");
	if (char_tex == nullptr)
	{
		printf("Failed to load character :(\n");
		return EXIT_FAILURE;
	}

	model char_model{
		// Standing still facing south animation
		std::make_pair(std::string{ "stand_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 0, 16, 16)}
		}),

		// Standing still facing north animation
		std::make_pair(std::string{ "stand_north" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(16, 0, 16, 16)}
		}),

		// Standing still facing west animation
		std::make_pair(std::string{ "stand_west" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(32, 0, 16, 16)}
		}),

		// Standing still facing east animation
		std::make_pair(std::string{ "stand_east" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(48, 0, 16, 16)}
		}),

		// Walk south animation
		std::make_pair(std::string{ "walk_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 16, 16, 16) },
			{ char_tex, sf::IntRect(0, 32, 16, 16) },
			{ char_tex, sf::IntRect(0,  0, 16, 16) },
			{ char_tex, sf::IntRect(0, 48, 16, 16) },
			{ char_tex, sf::IntRect(0, 64, 16, 16) },
			{ char_tex, sf::IntRect(0,  0, 16, 16)}
		}),

		// Walk north animation
		std::make_pair(std::string{ "walk_north" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(16, 16, 16, 16) },
			{ char_tex, sf::IntRect(16, 32, 16, 16) },
			{ char_tex, sf::IntRect(16,  0, 16, 16) },
			{ char_tex, sf::IntRect(16, 48, 16, 16) },
			{ char_tex, sf::IntRect(16, 64, 16, 16) },
			{ char_tex, sf::IntRect(16,  0, 16, 16) }
		}),

		// Walk west animation
		std::make_pair(std::string{ "walk_west" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(32, 16, 16, 16) },
			{ char_tex, sf::IntRect(32, 32, 16, 16) },
			{ char_tex, sf::IntRect(32,  0, 16, 16) },
			{ char_tex, sf::IntRect(32, 48, 16, 16) },
			{ char_tex, sf::IntRect(32, 64, 16, 16) },
			{ char_tex, sf::IntRect(32,  0, 16, 16) }
		}),

		// Walk east animation
		std::make_pair(std::string{ "walk_east" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(48, 16, 16, 16) },
			{ char_tex, sf::IntRect(48, 32, 16, 16) },
			{ char_tex, sf::IntRect(48,  0, 16, 16) },
			{ char_tex, sf::IntRect(48, 48, 16, 16) },
			{ char_tex, sf::IntRect(48, 64, 16, 16) },
			{ char_tex, sf::IntRect(48,  0, 16, 16) }
		}),
	};
	// Character animation stuff ends here

	sf::Clock clock;
	// run the program as long as the window is open

	// Draw the character
	const model::animation *anim = char_model["stand_south"];

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:	window.close(); break;

			case sf::Event::KeyPressed:
			{
				switch(event.key.code)
				{
					case sf::Keyboard::W: anim = char_model["walk_north"]; break;
					case sf::Keyboard::A: anim = char_model["walk_west"]; break;
					case sf::Keyboard::S: anim = char_model["walk_south"]; break;
					case sf::Keyboard::D: anim = char_model["walk_east"]; break;
					default: break;
				}
				break;
			}

			case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W: anim = char_model["stand_north"]; break;
				case sf::Keyboard::A: anim = char_model["stand_west"]; break;
				case sf::Keyboard::S: anim = char_model["stand_south"]; break;
				case sf::Keyboard::D: anim = char_model["stand_east"]; break;
				default: break;
				}
				break;
			}

			default: break;
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// Then get the current frame of the animation
		const model::animation::frame &curframe =
			(*anim)[clock.getElapsedTime().asMilliseconds() / 100];
		
		character.setTexture(*curframe.get_texture());
		character.setTextureRect(curframe.get_subtexture());
		character.setPosition(sf::Vector2f(20.0f, 20.0f)); // +(clock.getElapsedTime().asMilliseconds() % 5000) / 50.0f));
		window.draw(character);

		// end the current frame
		window.display();
	}

	return EXIT_SUCCESS;
}