#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resources.h"

const std::string thirdparty_resource_path = "..\\..\\Resources\\";
const std::string internal_resource_path = "..\\..\\..\\Resources\\";

const std::string resource_loader<sf::Texture>::path = "Images\\";
const std::string resource_loader<sf::SoundBuffer>::path = "Sounds\\";