#pragma once
#include "animation.h"

model::animation::frame::frame(const sf::Texture *tex, const sf::IntRect &rect) :
	texture(tex),
	subtexture(rect)
{}

const sf::Texture *model::animation::frame::get_texture() const
{
	return texture;
}

const sf::IntRect &model::animation::frame::get_subtexture() const
{
	return subtexture;
}

model::animation::animation(const std::initializer_list<model::animation::frame> &framelist) :
	frames(framelist)
{
}

const model::animation::frame &model::animation::operator[](int index) const
{
	return frames[index % frames.size()];
}

model::model(const std::initializer_list<std::pair<const std::string, animation>> &animlist) :
	animations(animlist)
{

}

const model::animation *model::operator[](const std::string &name) const
{
	auto lookup = animations.find(name);
	if (lookup == animations.cend())
		return nullptr;

	return &lookup->second;
}