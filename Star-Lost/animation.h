#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class model
{
public:
	class animation
	{
	public:
		class frame
		{
		public:
			frame(const sf::Texture *tex, const sf::IntRect &rect) :
				texture(tex),
				subtexture(rect)
			{}

			const sf::Texture *get_texture() const
			{
				return texture;
			}

			const sf::IntRect &get_subtexture() const
			{
				return subtexture;
			}

		private:
			const sf::Texture *texture;
			sf::IntRect subtexture;
		};

	public:
		animation(const std::initializer_list<frame> &framelist) :
			frames(framelist)
		{
		}

		const frame &operator[](int index) const
		{
			return frames[index % frames.size()];
		}

	private:
		std::vector<frame> frames;
	};

public:
	model(const std::initializer_list<std::pair<const std::string, animation>> &animlist) :
		animations(animlist)
	{

	}

	const animation *operator[](const std::string &name) const
	{
		auto lookup = animations.find(name);
		if (lookup == animations.cend())
			return nullptr;

		return &lookup->second;
	}

private:
	std::map<std::string, animation> animations;
};