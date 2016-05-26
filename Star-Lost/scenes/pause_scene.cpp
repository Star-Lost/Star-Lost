#include "pause_scene.h"

void pause_scene::handle_event(scene_director &director, const sf::Event &evt)
{

}

void pause_scene::update(scene_director &director, float dt)
{
	director.get_window().clear(sf::Color(100, 149, 237));
	director.get_window().display();
}