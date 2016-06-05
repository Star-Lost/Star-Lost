#pragma once

namespace ecs
{
	namespace components
	{
		struct state {
		private:
			unsigned int previous_state;
			unsigned int current_state;

		public:
			unsigned int get_previous_state();
			unsigned int get_current_state();
			void set_current_state(unsigned int new_state);
		};
	}
}