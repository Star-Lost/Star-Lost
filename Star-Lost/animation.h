#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <map>

#include "resources.h"

class model
{
public:
	class animation
	{
	public:
		class frame
		{
		public:
			frame(const sf::Texture *tex, const sf::IntRect &rect);
			const sf::Texture *get_texture() const;
			const sf::IntRect &get_subtexture() const;

		private:
			const sf::Texture *texture;
			sf::IntRect subtexture;
		};

	public:
		animation(const std::initializer_list<frame> &framelist);
		const frame &operator[](int index) const;

	private:
		std::vector<frame> frames;
	};

public:
	model(const std::initializer_list<std::pair<const std::string, animation>> &animlist);
	const animation *operator[](const std::string &name) const;

private:
	std::map<std::string, animation> animations;
};

template<>
class resource_loader<model>
{
	friend class resource<model>;

	static const std::string path;
	static bool load(const std::string &name, model &out);
};