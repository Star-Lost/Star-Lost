#pragma once
#include "../attributes.h"

namespace ecs
{
	namespace entities
	{
		template<typename Requirements>
		struct base : public unique
		{
			entity_index get_id() const
			{
				return id;
			}

		protected:
			base(game_context &ctx, entity_index eid) :
				ctx(ctx),
				id(eid)
			{
				if (!ctx.matches_signature<Requirements>(eid))
					throw std::runtime_error("you tried to construct an entity from an id that wasnt of that type you ding dong!");
			}

			base(game_context &ctx) :
				ctx(ctx),
				id(ctx.create_entity())
			{

			}

			const entity_index id;
			game_context &ctx;
		};
	}
}