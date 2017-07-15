#pragma once

class scene_director;

namespace ecs
{
	namespace systems
	{
		struct render : public base_system
		{
			using required = mpl::type_list<
				components::position,
				components::drawable
			>;

			struct draw_order
			{
				draw_order() = default;
				draw_order(float depth, sf::Vector2f position, const sf::Texture *texture, sf::IntRect subtexture, sf::Color color);

				float depth;
				sf::Vector2f position;
				const sf::Texture *texture;
				sf::IntRect subtexture;
				sf::Color color;

				bool operator<(const draw_order &other) const;
			};

			void update(
				entity_index eid, 
				game_context &ctx, 
				components::position &pos, 
				components::drawable &drw
			);

			void draw(scene_director &director, sf::RenderTarget &target);

			std::vector<draw_order> draw_orders;
		};
	}
}