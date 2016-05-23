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
		std::make_pair(std::string{ "still_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 0, 16, 16)}
		}),
		// Walk south animation
		std::make_pair(std::string{ "walk_south" }, std::initializer_list<model::animation::frame>{
			{ char_tex, sf::IntRect(0, 16, 16, 16) },
			{ char_tex, sf::IntRect(0, 32, 16, 16) },
			{ char_tex, sf::IntRect(0, 0, 16, 16) },
			{ char_tex, sf::IntRect(0, 48, 16, 16) },
			{ char_tex, sf::IntRect(0, 64, 16, 16) },
			{ char_tex, sf::IntRect(0, 0, 16, 16)}
		}),
	};
	// Character animation stuff ends here

	sf::Clock clock;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);




		// Draw the character
		const model::animation *anim = nullptr;

		// We switch between standing still and walking south every 5 seconds
		if (static_cast<int>(clock.getElapsedTime().asSeconds()) % 10 > 5)
			anim = char_model["still_south"];
		else
			anim = char_model["walk_south"];

		// Then get the current frame of the animation
		const model::animation::frame &curframe =
			(*anim)[clock.getElapsedTime().asMilliseconds() / 100];
		
		character.setTexture(*curframe.get_texture());
		character.setTextureRect(curframe.get_subtexture());
		character.setPosition(sf::Vector2f(700.0f, 200.0f + (clock.getElapsedTime().asMilliseconds() % 5000) / 50.0f));
		window.draw(character);

		// end the current frame
		window.display();
	}

	return EXIT_SUCCESS;
}