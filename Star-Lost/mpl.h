#pragma once
#include <type_traits>

// This file will contain a bunch of template metaprogramming helper functions

namespace mpl
{
	template<template <typename...> class Template, typename T>
	struct is_specialization_of : std::false_type {};

	template<template <typename...> class Template, typename... Args>
	struct is_specialization_of<Template, Template<Args...>> : std::true_type {};

	template<typename ...Types>
	struct type_list
	{
		// Append
		template<typename ...List>
		struct append;

		template<typename ...List>
		struct append<List...>
		{
			using type = typename type_list<Types..., List...>;
		};

		template<typename ...List>
		struct append<type_list<List...>>
		{
			using type = typename append<List...>::type;
		};

		template<>
		struct append<type_list<>>
		{
			using type = type_list<Types...>;
		};

		template<typename ...List>
		using append_t = typename append<List...>::type;



		// Prepend
		template<typename ...List>
		struct prepend;

		template<typename ...List>
		struct prepend<List...>
		{
			using type = type_list<List..., Types...>;
		};

		template<typename ...List>
		struct prepend<type_list<List...>>
		{
			using type = typename prepend<List...>::type;
		};

		template<>
		struct prepend<type_list<>>
		{
			using type = type_list<Types...>;
		};

		template<typename ...List>
		using prepend_t = typename prepend<List...>::type;


		// Get
		template<unsigned int I>
		struct get
		{
			template<unsigned int N, typename ...Rest>
			struct search;

			template<unsigned int N, typename Head, typename ...Rest>
			struct search<N, Head, Rest...>
			{
				using type = typename search<N - 1, Rest...>::type;
			};

			template<typename Head, typename ...Rest>
			struct search<0, Head, Rest...>
			{
				using type = Head;
			};

			using type = typename search<I, Types...>::type;
		};

		template<unsigned int I>
		using get_t = typename get<I>::type;


		// Filter
		template<template<typename> typename Predicate>
		struct filter
		{
			template<typename Head, typename ...Rest>
			struct filter_list;

			template<typename Head, typename ...Rest>
			struct filter_list<Head, Rest...>
			{
				using type = typename std::conditional<Predicate<typename Head>::value,
					typename filter_list<Rest...>::type::template prepend_t<Head>,
					typename filter_list<Rest...>::type
				>::type;
			};

			template<typename Head>
			struct filter_list<Head>
			{
				using type = typename std::conditional<Predicate<typename Head>::value,
					type_list<Head>,
					type_list<>
				>::type;
			};

			using type = typename filter_list<Types...>::type;
		};

		template<template<typename> typename Predicate>
		using filter_t = typename filter<Predicate>::type;



		// Contains
		template<typename ...Needles>
		struct contains;

		template<typename Needle, typename ...Rest>
		struct contains<type_list<Needle, Rest...>>
		{
			static constexpr bool value = contains<Needle, Rest...>::value;
		};

		template<typename Needle, typename ...Rest>
		struct contains<Needle, Rest...>
		{
			static constexpr bool value = contains<Needle>::value && contains<Rest...>::value;
		};

		template<typename Needle>
		struct contains<Needle>
		{
		private:
			template<typename Head, typename ...Tail>
			struct search;

			template<typename Head, typename ...Tail>
			struct search<Head, Tail...>
			{
				static constexpr bool value = std::is_same<Needle, Head>::value || search<Tail...>::value;
			};

			template<typename Head>
			struct search<Head>
			{
				static constexpr bool value = std::is_same<Needle, Head>::value;
			};

		public:
			static constexpr bool value = search<Types...>::value;
		};

		template<typename ...Needles>
		using contains_v = typename contains<Needles...>::value;



		// To
		template<template<typename...> typename T>
		struct to
		{
			using type = typename T<Types...>;
		};

		template<template<typename...> typename T>
		using to_t = typename to<T>::type;
	};	

	namespace tests
	{
		using long_list = type_list<int, unsigned int, unsigned char, long, float, double>;
		using short_list = type_list<int, bool>;
		
		// Append
		static_assert(std::is_same<short_list::append_t<char>, type_list<int, bool, char>>::value, "");
		static_assert(!std::is_same<short_list::append_t<char>, type_list<int, bool, long>>::value, "");

		// Prepend
		static_assert(std::is_same<short_list::prepend_t<char>, type_list<char, int, bool>>::value, "");
		static_assert(!std::is_same<short_list::prepend_t<char>, type_list<long, int, bool>>::value, "");

		// Get
		static_assert( std::is_same<long_list::get_t<1>, unsigned int>::value, "");
		static_assert( std::is_same<long_list::get_t<3>, long>::value, "");
		static_assert(!std::is_same<long_list::get_t<4>, long>::value, "");

		// Filter
		static_assert( std::is_same<long_list::filter_t<std::is_floating_point>, type_list<float, double>>::value, "");

		// Contains
		static_assert( long_list::contains<long>::value, "");
		static_assert(!long_list::contains<bool>::value, "");
		static_assert(!long_list::contains<char>::value, "");

		// To
		static_assert( std::is_same<short_list::to_t<std::tuple>, std::tuple<int, bool>>::value, "");
		static_assert(!std::is_same<short_list::to_t<std::tuple>, std::tuple<bool, int>>::value, "");
	}
}