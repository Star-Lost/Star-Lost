#pragma once
#include <SFML/System/Vector2.hpp>
#include <utility>
#include <array>

#include "mpl.h"

namespace ecs
{
	using bitset_type = unsigned long long;

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
		static constexpr std::size_t signature_bits = components::size + Tags::size;

		static_assert(components::size < sizeof(bitset_type) * 8, "signature bitset can no longer hold all these components and tags");

		template<typename ...Args>
		using component_arrays = typename std::tuple<std::array<Args, max_entities>...>;

		// Expand the Components list into a tuple<array<T, max>> like so:
		//		Components = type_list<position_component, velocity_component>
		//	=>  tuple<array<position_component, max>, array<velocity_component, max>>
		using component_storage = typename components::template to_t<component_arrays>;
		using system_storage = typename Systems::template to_t<std::tuple>;

		template<typename T>
		static constexpr bool is_component = typename components::contains<T>::value;

		template<typename T>
		static constexpr bool is_tag = typename tags::contains<T>::value;

		// Get the component-specific bit
		template<typename T>
		static constexpr std::size_t component_bit = typename components::index_v<T>;

		// Get the tag-specific bit
		template<typename T>
		static constexpr std::size_t tag_bit = components::size + tags::index_v<T>;

		template<typename T, bool Test>
		struct signature_bit;

		template<typename T>
		struct signature_bit<T, true>
		{
			static constexpr std::size_t value = component_bit<T>;
		};

		template<typename T>
		struct signature_bit<T, false>
		{
			static constexpr std::size_t value = tag_bit<T>;
		};

		template<typename T>
		static constexpr std::size_t signature_bit_v = signature_bit<T, is_component<T>>::value;

		// Signature calculation code
		template<typename ...>
		struct signature;

		template<typename Head, typename ...Rest>
		struct signature<Head, Rest...>
		{
			static constexpr bitset_type value = signature<Rest...>::value | (1 << signature_bit_v<Head>);
		};

		template<typename Head, typename ...Rest>
		struct signature<mpl::type_list<Head, Rest...>>
		{
			static constexpr bitset_type value = signature<Head, Rest...>::value;
		};

		template<>
		struct signature<>
		{
			static constexpr bitset_type value = 0;
		};

		template<typename List>
		static constexpr bitset_type signature_v = signature<List>::value;
	};

	template<typename ...Components>
	using signature = mpl::type_list<Components...>;

	struct entity
	{
		size_t id;
		size_t data_index;
		bitset_type signature;
		bool alive;
	};

	template<typename Settings>
	struct context
	{
		using settings = Settings;

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

		entity &get_entity(std::size_t entity_index)
		{
			return entities[entity_index];
		}

		const entity &get_entity(std::size_t entity_index) const
		{
			return entities[entity_index];
		}


		template<typename ...Ts>
		struct expand_call;

		template<typename ...Ts>
		struct expand_call<mpl::type_list<Ts...>>
		{
			template<typename Sys>
			static void call(context<Settings> &ctx, Sys &sys, std::size_t entity_index)
			{
				sys.update(entity_index, ctx.get_component<Ts>(entity_index)...);
			}
		};
		
		template<typename Sys>
		void for_entities_matching()
		{
			auto &sys = get_system<Sys>();

			for (auto i = 0u; i < last_entity; ++i)
			{
				if (matches_signature<Sys::required>(i))
				{
					expand_call<Sys::required>::call(*this, sys, i);
				}
			}
		}

		template<typename Head, typename ...Rest>
		void update_systems(mpl::type_list<Head, Rest...>)
		{
			for_entities_matching<Head>();
			update_systems<Rest...>();
		}
		
		template<typename Head>
		void update_systems(mpl::type_list<Head>)
		{
			for_entities_matching<Head>();
		}

	public:
		context() :
			last_entity(0)
		{}

		void update(float dt)
		{
			update_systems(settings::systems{});
		}

		// Component-related functions
		template<typename T, typename ... Args>
		auto &add_component(std::size_t entity_index, Args&&... args)
		{
			auto &ent = get_entity(entity_index);
			
			// Add the signature to the entities signatures
			ent.signature |= settings::signature_v<T>;

			// Construct in place
			return *new (&get_storage<T>()[ent.data_index]) T(std::forward<Args>(args)...);
		}

		template<typename T>
		auto &add_component(std::size_t entity_index)
		{
			auto &ent = get_entity(entity_index);

			// Add the signature to the entities signatures
			ent.signature |= settings::signature_v<T>;

			// Construct in place
			return *new (&get_storage<T>()[ent.data_index]) T{};
		}

		template<typename T>
		auto &delete_component(std::size_t entity_index)
		{
			// Just remove the signature from the entity
			ent.signature &= ~settings::signature_v<T>;
		}

		template<typename T>
		auto &get_component(size_t entity_index)
		{
			return get_storage<T>().at(get_entity(entity_index).data_index);
		}


		// Tag-related functionality
		template<typename T>
		void add_tag(std::size_t entity_index)
		{
			auto &ent = get_entity(entity_index);

			// Add the signature to the entities signatures
			ent.signature |= settings::signature_v<T>;
		}

		template<typename T>
		auto &delete_tag(std::size_t entity_index)
		{
			// Just remove the signature from the entity
			ent.signature &= ~settings::signature_v<T>;
		}

		// Entity related functionality
		bool is_alive(std::size_t entity_index) const
		{
			return get_entity(entity_index).alive;
		}

		std::size_t create_entity()
		{
			entity &ent = entities[last_entity];
			ent.id = last_entity;
			ent.data_index = last_entity;
			ent.alive = true;
			ent.signature = 0;

			++last_entity;
			return ent.id;
		}


		// Other stuff
		template<typename Signature>
		bool matches_signature(std::size_t entity_index) const
		{
			return (get_entity(entity_index).signature & Settings::signature_v<Signature>) == Settings::signature_v<Signature>;
		}
	};
}

