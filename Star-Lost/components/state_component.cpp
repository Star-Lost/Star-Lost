#include "state_component.h"

using namespace ecs::components;

unsigned int state::get_previous_state()
{
	return previous_state;
}

unsigned int state::get_current_state()
{
	return current_state;
}

void state::set_current_state(unsigned int new_state)
{
	previous_state = current_state;
	current_state = new_state;
}