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
			static constexpr signature_type value = tags::index_v<T>;
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
		unsigned int last_entity;

		template<typename T>
		auto &get_storage() {
			return std::get<std::array<T, settings::max_entities>>(components);
		}

		template<typename T>
		auto &get_system() {
			return std::get<T>(systems);
		}

		entity &get_entity(entity_index eid)
		{
			return entities[eid];
		}

		const entity &get_entity(entity_index eid) const
		{
			return entities[eid];
		}


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
			for (auto i = 0u; i < last_entity; ++i)
			{
				if (matches_signature<Sys::required>(i))
				{
					expand_call<Sys::required>::call<Sys>(*this, i, std::forward<Args>(args)...);
				}
			}
		}

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

	public:
		context() :
			last_entity(0)
		{}

		template<typename ...Args>
		void update(Args&&... args)
		{
			update_systems(settings::systems{}, args...);
		}

		// Component-related functions
		template<typename T, typename ... Args>
		auto &add_component(entity_index eid, Args&&... args)
		{
			auto &ent = get_entity(eid);
			
			// Add the signature to the entities signatures
			ent.signature |= signature::get_v<T>;

			// Construct in place
			return *new (&get_storage<T>()[ent.data]) T(std::forward<Args>(args)...);
		}

		template<typename T>
		auto &add_component(entity_index eid)
		{
			auto &ent = get_entity(eid);

			// Add the signature to the entities signatures
			ent.signature |= signature::get_v<T>;

			// Construct in place
			return *new (&get_storage<T>()[ent.data]) T{};
		}

		template<typename T>
		auto &delete_component(entity_index eid)
		{
			// Just remove the signature from the entity
			eid.signature &= ~signature::get_v<T>;
		}

		template<typename T>
		auto &get_component(entity_index eid)
		{
			return get_storage<T>().at(get_entity(eid).data);
		}


		// Tag-related functionality
		template<typename T>
		void add_tag(entity_index eid)
		{
			auto &ent = get_entity(eid);

			// Add the signature to the entities signatures
			ent.signature |= signature::get_v<T>;
		}

		template<typename T>
		auto &delete_tag(entity_index eid)
		{
			// Just remove the signature from the entity
			eid.signature &= ~signature::get_v<T>;
		}

		// Entity related functionality
		bool is_alive(entity_index eid) const
		{
			return get_entity(eid).alive;
		}

		const std::vector<entity_index> &get_entities() const
		{
			return entities;
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
		template<typename Signature>
		bool matches_signature(entity_index eid) const
		{
			return (get_entity(eid).signature & signature::get_v<Signature>) == signature::get_v<Signature>;
		}
	};
}

