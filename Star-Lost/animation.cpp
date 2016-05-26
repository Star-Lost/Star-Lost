#pragma once
#include "animation.h"

using namespace rendering;

// Tile
tile::tile(const sf::IntRect &rect) :
	rect(rect)
{

}



// Row
row::row(const std::initializer_list<tile> &tiles) :
	tiles(tiles)
{

}

auto row::get_tiles() const -> const std::vector<tile>&
{
	return tiles;
}



// Layer
layer::layer(const std::initializer_list<row> &rows) :
	rows(rows)
{

}

auto layer::get_rows() const -> const std::vector<row>&
{
	return rows;
}



// Frame
frame::frame(const std::initializer_list<layer> &layers) :
	layers(layers)
{

}

frame::frame(const sf::Texture *tex, const sf::IntRect &rect) :
	texture(tex),
	subtexture(rect)
{}

const sf::Texture *frame::get_texture() const
{
	return texture;
}

const sf::IntRect &frame::get_subtexture() const
{
	return subtexture;
}

auto frame::get_layers() const -> const std::vector<layer> &
{
	return layers;
}


// Animation
animation::animation(const std::initializer_list<frame> &framelist) :
	frames(framelist)
{
}

const frame &animation::operator[](int index) const
{
	return frames[index % frames.size()];
}




// Model
model::model(const sf::Texture *sheet, const std::initializer_list<named_animation> &animlist) :
	sheet(sheet),
	animations(animlist)
{
	for (auto &anim : animations)
		anim.second.mdl = this;
}

model::model(const std::initializer_list<std::pair<const std::string, animation>> &animlist) :
	animations(animlist)
{

}

const animation *model::operator[](const std::string &name) const
{
	auto lookup = animations.find(name);
	if (lookup == animations.cend())
		return nullptr;

	return &lookup->second;
}

bool resource_loader<model>::load(const std::string &name, model &out)
{
	// You can't load models like this, they're defined programmatically
	return false;
}

const std::string resource_loader<model>::path = "";