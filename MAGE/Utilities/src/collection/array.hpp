#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <array>
#include <tuple>
#include <utility>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	namespace details {

		template< typename ActionT, typename FromT, size_t...I >
		constexpr auto TransformArray(ActionT action, 
									  const std::array< FromT, sizeof...(I) >& a, 
									  std::index_sequence< I... >) {

			using ToT = decltype(std::declval< ActionT >()(std::declval< FromT >()));
			return std::array< ToT, sizeof...(I) >{ action(a[I])... };
		}

		template< typename T, size_t...I >
		constexpr auto FillArray(T value, std::index_sequence< I... >) {
			return std::array< T, sizeof...(I) >{ (static_cast< void >(I), value)... };
		}
	
		template< size_t ToN, typename T, size_t...I >
		constexpr auto EnlargeArray(const std::array< T, sizeof...(I) >& a, 
									std::index_sequence< I... >) {

			return std::array< T, ToN >{ a[I]... };
		}
	
		template< typename T, typename TupleT, std::size_t... I >
		constexpr auto TuppleToArray(const TupleT& t, 
									 std::index_sequence< I... >) {

			return std::array< T, sizeof...(I) >{ std::get< I >(t)... };
		}
	}

	template< typename ActionT, typename FromT, size_t N >
	constexpr auto TransformArray(ActionT action, 
								  const std::array< FromT, N >& a) {
		
		return details::TransformArray(std::move(action), a,
									   std::make_index_sequence< N >());
	}

	template< typename ToT, typename FromT, size_t N >
	constexpr auto StaticCastArray(const std::array< FromT, N >& a) {
		constexpr auto f = [](const FromT& v) {
			return static_cast< ToT >(v); 
		};
		return TransformArray(f, a);
	}

	template< typename ToT, typename FromT, size_t N >
	constexpr auto DynamicCastArray(const std::array< FromT, N >& a) {
		constexpr auto f = [](const FromT& v) {
			return dynamic_cast< ToT >(v); 
		};
		return TransformArray(f, a);
	}

	template< typename ToT, typename FromT, size_t N >
	constexpr auto ConstCastArray(const std::array< FromT, N >& a) {
		constexpr auto f = [](const FromT& v) {
			return const_cast< ToT >(v); 
		};
		return TransformArray(f, a);
	}

	template< typename ToT, typename FromT, size_t N >
	constexpr auto ReinterpretCastArray(const std::array< FromT, N >& a) {
		constexpr auto f = [](const FromT& v) {
			return reinterpret_cast< ToT >(v); 
		};
		return TransformArray(f, a);
	}

	template< typename T, size_t N >
	constexpr auto FillArray(T value) {
		return details::FillArray(value, std::make_index_sequence< N >());
	}

	template< size_t ToN, typename T, size_t FromN >
	constexpr auto EnlargeArray(const std::array< T, FromN >& a) {
		return details::EnlargeArray< ToN >(a, std::make_index_sequence< FromN >());
	}

	template< typename T, typename... Ts >
	constexpr auto TuppleToArray(const std::tuple< T, Ts... >& t) {
		constexpr auto N = sizeof...(Ts) + 1u;
		return details::TuppleToArray< T >(t, std::make_index_sequence< N >());
	}
}