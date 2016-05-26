#include "../game_context.h"

using namespace ecs;

void systems::render::update(
	entity_index eid,
	game_context &ctx,
	components::position &pos,
	components::drawable &drw
) const {
	sf::Sprite temp;
	temp.setTexture(*drw.texture);

	sf::Vector2f offset{ 0, 0 };
	for (auto &layer : drw.frame->get_layers())
	{
		for (auto &row : layer.get_rows())
		{
			for (auto &tile : row.get_tiles())
			{
				temp.setTextureRect(tile.rect);

				temp.setPosition(offset + sf::Vector2f(pos.x, pos.y));
				ctx.get_render_target().draw(temp);

				offset.x += tile.rect.width;
			}
			offset.x = 0;
			offset.y -= row.get_tiles()[0].rect.height;
		}
	}
}