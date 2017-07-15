#include "../game_context.h"

using namespace ecs;
using ecs::systems::render;

render::draw_order::draw_order(
	float depth,
	sf::Vector2f position,
	const sf::Texture *texture,
	sf::IntRect subtexture,
	sf::Color color
) :
	depth(depth),
	position(position),
	texture(texture),
	subtexture(subtexture),
	color(color)
{

}

bool render::draw_order::operator<(const render::draw_order &other) const
{
	return depth < other.depth;
}

void render::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::drawable &drw
) {
	float depth = 0.0f;
	sf::Vector2f offset{ 0, 0 };

	sf::Color color{ 255, 255, 255, 255 };

	if (ctx.has_component<components::color>(eid))
		color = ctx.get_component<components::color>(eid);

	for (auto &layer : drw.frame->get_layers())
	{
		for (auto &row : layer.get_rows())
		{
			for (auto &tile : row.get_tiles())
			{
				draw_orders.emplace_back(
					pos.y - offset.y + depth,
					offset + pos,
					drw.texture,
					tile.rect,
					color
				);

				offset.x += tile.rect.width;
			}
			offset.x = 0;
			offset.y -= row.get_tiles()[0].rect.height;
		}
		depth += 16.0f;
	}
}

void render::draw(scene_director &director, sf::RenderTarget &target)
{
	// Sort all the draw orders by depth, so we can paint the world 
	// from the ground up
	std::sort(draw_orders.begin(), draw_orders.end());

	sf::Sprite temp;
	for (auto &order : draw_orders)
	{
		temp.setPosition(order.position);
		temp.setTexture(*order.texture);
		temp.setTextureRect(order.subtexture);
		temp.setColor(order.color);

		target.draw(temp);
	}

	draw_orders.clear();
}