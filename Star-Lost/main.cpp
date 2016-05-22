#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "resources.h"

#define TOOT_DELAY 1.0f

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Happiness");
	window.setFramerateLimit(30); // Limit the frame rate to achieve a cinematic feel

	resource<sf::Texture> textures;
	resource<sf::SoundBuffer> sounds;

	sf::Clock clock;
	sf::Sprite sprite;

	const sf::Texture *huetex;// = *textures.load_resource("hue.png");
	const sf::SoundBuffer *tootsound;// = *sounds.load_resource("toot.wav");

	float nexttoot = 3.0f;
	float angleoffset = 0.0f;

	if ((huetex = textures.load_resource("hue.png")) == nullptr)
	{
		printf("Failed to load happiness :(\n");
		return EXIT_FAILURE;
	}

	if ((tootsound = sounds.load_resource("toot.wav")) == nullptr)
	{
		printf("Failed to load happiness audio :(\n");
		return EXIT_FAILURE;
	}

	sprite.setTexture(*huetex);
	sprite.setOrigin(sf::Vector2f(285.5f, 308.0f));
	sprite.setPosition(sf::Vector2f(285.0f, 308.0f));

	sf::Sound sound;
	sound.setBuffer(*tootsound);

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

		// draw everything here...
		// window.draw(...);

		const float secs = clock.getElapsedTime().asSeconds();
		sprite.setRotation(angleoffset);
		window.draw(sprite);

		// end the current frame
		window.display();

		if (secs > nexttoot)
		{
			sound.play();
			angleoffset += 25.0f;
			nexttoot = secs + TOOT_DELAY;
		}

		angleoffset = angleoffset * 0.9f;
	}

	return EXIT_SUCCESS;
}