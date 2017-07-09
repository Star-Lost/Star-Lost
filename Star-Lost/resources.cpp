#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resources.h"

const std::string thirdparty_resource_path = "..\\Third party\\Resources\\";
const std::string internal_resource_path = "..\\Resources\\";

const std::string resource_loader<sf::SoundBuffer>::path = "Sounds\\";
const std::string resource_loader<sf::Font>::path = "Fonts\\";