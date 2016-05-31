#include <SFML/Graphics/Color.hpp>
#include "color_component.h"

using namespace ecs;

components::color::color(
	unsigned char red,
	unsigned char green,
	unsigned char blue,
	unsigned char alpha) :
	sf::Color(red, green, blue, alpha)
{

}