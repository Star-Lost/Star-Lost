#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <map>

#include "resources.h"

namespace rendering
{
	struct tile
	{
		tile() = default;
		tile(const sf::IntRect &rect);

		sf::IntRect rect;
	};


	class row
	{
	public:
		row(const std::initializer_list<tile> &tiles);
		const std::vector<tile> &get_tiles() const;

	private:
		std::vector<tile> tiles;
	};



	class layer
	{
	public:
		layer(const std::initializer_list<row> &rows);
		layer(const std::initializer_list<tile> &tiles);

		const std::vector<row> &get_rows() const;

	private:
		std::vector<row> rows;
	};



	class frame
	{
	public:
		frame(const std::initializer_list<layer> &layers);
		frame(const std::initializer_list<row> &rows);
		frame(const std::initializer_list<tile> &tiles);

		frame(const sf::Texture *tex, const sf::IntRect &rect);
		const sf::Texture *get_texture() const;
		const sf::IntRect &get_subtexture() const;
		const std::vector<layer> &get_layers() const;

	private:
		std::vector<layer> layers;
		const sf::Texture *texture;
		sf::IntRect subtexture;
	};

	class animation
	{
		friend class model;
	public:
		animation(const std::initializer_list<frame> &framelist);
		const frame &operator[](int index) const;

	private:
		model *mdl;
		std::vector<frame> frames;
	};

	class model
	{
	public:
		using named_animation = std::pair<const std::string, animation>;

		model(const sf::Texture *sheet, const std::initializer_list<named_animation> &animlist);
		model(const std::initializer_list<named_animation> &animlist);
		const animation *operator[](const std::string &name) const;

	private:
		const sf::Texture *sheet;
		std::map<std::string, animation> animations;
	};
}

template<>
class resource_loader<rendering::model>
{
	friend class resource<rendering::model>;

	static const std::string path;
	static bool load(const std::string &name, rendering::model &out);
};