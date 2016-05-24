#include "game_context.h"

game_context::game_context(sf::RenderTarget &target) :
	render_target(target)
{

}

void game_context::update(float dt)
{
	delta_time = dt;
	context::update(*this);
}

sf::RenderTarget &game_context::get_render_target()
{
	return render_target;
}

float game_context::get_delta() const
{
	return delta_time;
}