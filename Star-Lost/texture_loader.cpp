#include <SFML/Graphics/Texture.hpp>
#include "resources.h"

const std::string resource_loader<sf::Texture>::path = "Images\\";

bool resource_loader<sf::Texture>::load(const std::string &name, sf::Texture &out)
{
	sf::Image img;
	if (!img.loadFromFile(name))
		return false;
	// Replace magenta with transparency
	img.createMaskFromColor(sf::Color{ 255, 0, 255, 255 });

	return out.loadFromImage(img);
}