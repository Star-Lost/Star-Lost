#include "pause_scene.h"

void pause_scene::handle_event(const sf::Event &evt)
{

}

void pause_scene::update(scene_director &director)
{
	director.window.clear(sf::Color(100, 149, 237));
	director.window.display();
}