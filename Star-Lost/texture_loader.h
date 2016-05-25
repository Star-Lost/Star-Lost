#pragma once
#include "resource_loader.h"

namespace sf { class Texture; }

template<>
class resource_loader<sf::Texture>
{
	friend class resource<sf::Texture>;

	static const std::string path;
	static bool load(const std::string &name, sf::Texture &out);
};