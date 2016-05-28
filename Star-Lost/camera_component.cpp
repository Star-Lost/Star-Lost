#include "camera_component.h"

using namespace ecs::components;

// The camera would normally follow the player
camera::camera()
{
	position = { 0.0f, 0.0f };
	active = false;
	following = nullptr;
}

sf::Vector2f &ecs::components::camera::get_position()
{
	return position;
}

sf::Vector2f &ecs::components::camera::get_render_area()
{
	return render_area;
}

bool ecs::components::camera::is_active()
{
	return active;
}

void ecs::components::camera::follow_entity(ecs::entity entity)
{
	following = &entity;
}