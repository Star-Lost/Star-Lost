#pragma once
#include <SFML/System/Vector2.hpp>
#include <utility>
#include <vector>
#include <array>

#include "mpl.h"

namespace ecs
{
	using entity_index = std::size_t;
	using data_index = std::size_t;

	// Type signatures are stored in, they have to have a size
	// with more or equal bits to the sum of all tags and components
	using signature_type = unsigned long long;

	template<
		typename Settings
	>
	struct signatures
	{
		using components = typename Settings::components;
		using tags = typename Settings::tags;

		static constexpr std::size_t required_bits = components::size + tags::size;
		static_assert(required_bits < sizeof(signature_type) * 8, "signature bitset can no longer hold all these components and tags");

		template<
			typename T, 
			bool IsComponent = components::contains<T>::value,
			bool IsTag = tags::contains<T>::value
		>
		struct get_bit
		{
			static_assert(!IsComponent && !IsTag, "signatures::get called with type that was neither component nor tag");
			static constexpr signature_type value = 0;
		};

		// If it's a component...
		template<typename T>
		struct get_bit<T, true, false>
		{	
			static constexpr signature_type value = components::index_v<T>;
		};

		// If it's a tag...
		template<typename T>
		struct get_bit<T, false, true>
		{
			static constexpr signature_type value = tags::index_v<T> + components::size;
		};

		template<typename T>
		static constexpr signature_type get_bit_v = get_bit<T>::value;

		// Signature calculation code
		template<typename ...>
		struct get;

		template<typename Head, typename ...Rest>
		struct get<mpl::type_list<Head, Rest...>>
		{
			static constexpr signature_type value = get<mpl::type_list<Rest...>>::value | (1 << get_bit_v<Head>);
		};

		template<typename Head>
		struct get<mpl::type_list<Head>>
		{
			static constexpr signature_type value = 1 << get_bit_v<Head>;
		};

		template<typename Head>
		struct get<Head>
		{
			static constexpr signature_type value = 1 << get_bit_v<Head>;
		};

		template<typename List>
		static constexpr signature_type get_v = get<List>::value;
	};

	template<
		typename Components = mpl::type_list<>, 
		typename Tags = mpl::type_list<>,
		typename Systems = mpl::type_list<>
	>
	struct settings
	{
		using components = Components;
		using tags = Tags;
		using systems = Systems;

		static constexpr std::size_t max_entities = 100;

		// This is the type used for storing all the component arrays
		template<typename ...Args>
		using component_arrays = typename std::tuple<std::array<Args, max_entities>...>;

		// Expand the Components list into a tuple<array<T, max>> like so:
		//		Components = type_list<position_component, velocity_component>
		//	=>  tuple<array<position_component, max>, array<velocity_component, max>>
		using component_storage = typename components::template to_t<component_arrays>;
		using system_storage = typename Systems::template to_t<std::tuple>;

		template<typename Item>
		struct is_component
		{
			static constexpr bool value = settings::components::contains_v<Item>;
		};

		template<typename Item>
		struct is_tag
		{
			static constexpr bool value = settings::tags::contains_v<Item>;
		};
	};

	struct entity
	{
		data_index id;
		data_index data;
		signature_type signature;
		bool alive;
	};

	template<typename Settings>
	struct context
	{
		using settings = Settings;
		using signature = signatures<settings>;

	private:
		typename settings::component_storage components;
		typename settings::system_storage systems;
		std::array<entity, settings::max_entities> entities;

		// This will point to the last entity before an update
		std::size_t last_entity;
		bool is_compressed;

		template<typename T>
		auto &get_storage() {
			return std::get<std::array<T, settings::max_entities>>(components);
		}

		const entity &get_entity(entity_index eid) const
		{
			return entities[eid];
		}

		// Expand call basically takes a context, and entity id, and a system and
		// extracts the components required by the system from the entity, and calls
		// the system with only the relevant components, in order.
		template<typename ...Ts>
		struct expand_call;

		template<typename ...Ts>
		struct expand_call<mpl::type_list<Ts...>>
		{
			template<typename Sys, typename ...Args>
			static void call(context<Settings> &ctx, entity_index eid, Args&& ...args)
			{
				ctx.get_system<Sys>().update(
					eid, 
					std::forward<Args>(args)...,
					// Expand all the component references as arguments
					ctx.get_component<Ts>(eid)...
				);
			}
		};
		
		template<typename Sys, typename ...Args>
		void update_system(Args&& ...args)
		{
			// Remove the tags from the list of components required by the system
			// since tags are void types they can't be instantiated so it doesn't
			// make sense to supply them as real arguments to the system
			using components_only = Sys::required::filter_t<settings::is_component>;

			for (auto i = 0u; i < last_entity; ++i)
			{
				// Tags are still gonna be matched against the system's requirements though
				if (matches_signature<Sys::required>(i))
				{
					expand_call<components_only>::call<Sys>(*this, i, std::forward<Args>(args)...);
				}
			}
		}

		// This function calls update on the systems supplied by the type_list<Systems...> argument
		template<typename Head, typename ...Rest, typename ...Args>
		void update_systems(mpl::type_list<Head, Rest...>, Args&&... args)
		{
			update_system<Head>(std::forward<Args>(args)...);
			update_systems(mpl::type_list<Rest...>{}, std::forward<Args>(args)...);
		}
		
		template<typename Head, typename ...Args>
		void update_systems(mpl::type_list<Head>, Args&&... args)
		{
			update_system<Head>(std::forward<Args>(args)...);
		}

		template<typename Component>
		void swap_component(entity_index aid, entity_index bid)
		{
			std::swap(get_component<Component>(aid), get_component<Component>(bid));
		}


		// Swaps the components supplied as template arguments between the two entities.
		// This function is primarily called by the compress_entities function with
		// the full list of components within this context to swap them entirely.
		template<typename ...>
		struct swap_components_impl;

		template<typename Component, typename ...Components>
		struct swap_components_impl<Component, Components...>
		{
			static void swap(context &ctx, entity_index aid, entity_index bid)
			{
				ctx.swap_component<Component>(aid, bid);
				swap_components_impl<Components...>::swap(ctx, aid, bid);
			}
		};

		template<typename Component>
		struct swap_components_impl<Component>
		{
			static void swap(context &ctx, entity_index aid, entity_index bid)
			{
				ctx.swap_component<Component>(aid, bid);
			}
		};

		void swap_components(entity_index aid, entity_index bid)
		{
			// Swap all the components of the entities first
			settings::components::to_t<swap_components_impl>::swap(*this, aid, bid);

			// Then swap their data pointers
			std::swap(entities[aid].data, entities[bid].data);
		}


		// This function just sorts the entity list from alive to dead
		// so the array is contiguous, and no gaps have to be to jumped
		// when looping through it.
		void compress_entities()
		{
			auto alive = 0;
			auto dead = last_entity;

			auto left = entities.begin();
			auto right = entities.rbegin() + entities.size() - last_entity;

			while (true)
			{
				// Find the first (left) dead one
				//
				//     L
				// AAAADAAADDADD
				left = std::find_if(left, entities.end(), [](const entity & ent) { return !ent.alive; });

				// Find the last (right) alive one
				//
				//           R
				// AAAADAAADDADD
				right = std::find_if(right, entities.rend(), [](entity & ent)
				{
					if (ent.alive)
						return true;

					// If it's already dead and sorted, clear it
					ent.id = 0;
					ent.data = 0;
					return false;
				});

				// If our alive iterator(L) is lower than our dead iterator(R), 
				// then the entities have been fully sorted
				//		 RL
				// AAAAAAADDDDDDD
				if (std::distance(&*entities.begin(), &*right) < std::distance(entities.begin(), left))
					break;

				// Otherwise, swap the left and right entities:
				std::swap(*left, *right);

				// Swap their IDs too
				std::swap(left->id, right->id);
			
				swap_components(left->id, right->id);
			}

			last_entity = std::distance(entities.begin(), left);

			is_compressed = true;
		}

		template<typename ...>
		struct initialize_systems_impl;

		template<typename Context, typename System, typename ...Systems>
		struct initialize_systems_impl<Context, System, Systems...>
		{
			static void initialize(Context &ctx)
			{
				// Construct in place
				ctx.get_system<System>().initialize(ctx);
				initialize_systems_impl<Context, Systems...>::initialize(ctx);
			}
		};

		template<typename Context, typename System>
		struct initialize_systems_impl<Context, System>
		{
			static void initialize(Context &ctx)
			{
				// Construct in place
				ctx.get_system<System>().initialize(ctx);
			}
		};
		
	protected:
		template<typename Context>
		void initialize_systems(Context &ctx)
		{
			settings::systems::prepend_t<Context>::to_t<initialize_systems_impl>::initialize(ctx);
		}

	public:
		context() :
			last_entity(0),
			is_compressed(true)
		{

		}

		entity &get_entity(entity_index eid)
		{
			return entities[eid];
		}

		template<typename ...Args>
		void update(Args&&... args)
		{
			update_systems(settings::systems{}, args...);

			if (!is_compressed)
				compress_entities();
		}

		template<typename System>
		auto &get_system() {
			return std::get<System>(systems);
		}

		// Component-related functions
		template<typename Component, typename ... Args>
		auto &add_component(entity_index eid, Args&&... args)
		{
			auto &ent = get_entity(eid);
			
			// Add the signature to the entities signatures
			ent.signature |= signature::get<Component>::value;

			// Construct in place
			return *new (&get_storage<Component>()[ent.data]) Component{ std::forward<Args>(args)... };
		}

		template<typename Component>
		auto &add_component(entity_index eid)
		{
			auto &ent = get_entity(eid);

			// Add the signature to the entities signatures
			ent.signature |= signature::get<Component>::value;

			// Construct in place
			return *new (&get_storage<Component>()[ent.data]) Component{};
		}

		template<typename Component>
		auto &delete_component(entity_index eid)
		{
			// Just remove the signature from the entity
			eid.signature &= ~signature::get<Component>::value;
		}

		template<typename Component>
		auto &get_component(entity_index eid)
		{
			return get_storage<Component>().at(get_entity(eid).data);
		}

		template<typename Component>
		bool has_component(entity_index eid)
		{
			return matches_signature<Component>(eid);
		}


		// Tag-related functionality
		template<typename Tag>
		void add_tag(entity_index eid)
		{
			auto &ent = get_entity(eid);

			// Add the signature to the entities signatures
			ent.signature |= signature::get<Tag>::value;
		}

		template<typename Tag>
		auto &delete_tag(entity_index eid)
		{
			// Just remove the signature from the entity
			eid.signature &= ~signature::get<Tag>::value;
		}

		template<typename Tag>
		bool has_tag(entity_index eid)
		{
			return matches_signature<Tag>(eid);
		}

		// Entity related functionality
		bool is_alive(entity_index eid) const
		{
			return get_entity(eid).alive;
		}

		void kill(entity_index eid) const
		{
			get_entity(eid).alive = false;

			// If we're already compressed, and the killed entity
			// was the last one, then we are still compressed.
			is_compressed = is_compressed && eid == last_entity - 1;
		}

		template<typename Lambda>
		void for_entities(const Lambda &lambda) const
		{
			for (entity_index eid = 0; eid < last_entity; ++eid)
				lambda(eid);
		}

		template<typename Signature, typename Lambda>
		void for_entities(const Lambda &lambda) const
		{
			for (entity_index eid = 0; eid < last_entity; ++eid)
				if (matches_signature<Signature>(eid))
					lambda(eid);
		}

		template<typename Lambda>
		void for_entities(const Lambda &lambda, signature_type signature)
		{
			for (entity_index eid = 0; eid < last_entity; ++eid)
				if (matches_signature(eid, signature))
					lambda(eid);
		}

		std::size_t create_entity()
		{
			entity &ent = entities[last_entity];
			ent.id = last_entity;
			ent.data = last_entity;
			ent.alive = true;
			ent.signature = 0;

			++last_entity;
			return ent.id;
		}

		// Other stuff
		template<typename Component>
		bool matches_signature(entity_index eid) const
		{
			return (get_entity(eid).signature & signature::get<Component>::value) == signature::get<Component>::value;
		}

		bool matches_signature(entity_index eid, signature_type signature) const
		{
			return (get_entity(eid).signature & signature) == signature;
		}
	};
}

