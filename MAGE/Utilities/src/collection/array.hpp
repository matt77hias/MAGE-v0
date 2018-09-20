#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <array>
#include <utility>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Array Utilities
	//-------------------------------------------------------------------------
	#pragma region

	namespace details {

		template< typename ActionT, typename FromT, std::size_t... I >
		[[nodiscard]]
		constexpr const auto TransformArray(ActionT&& action,
											const std::array< FromT, sizeof...(I) >& a,
											std::index_sequence< I... >) {

			using ToT = decltype(std::declval< ActionT >()(std::declval< FromT >()));
			return std::array< ToT, sizeof...(I) >{ action(a[I])... };
		}

		template< typename T, std::size_t... I >
		[[nodiscard]]
		constexpr const auto FillArray(const T& value,
									   std::index_sequence< I... >) {

			return std::array< T, sizeof...(I) >{ (static_cast< void >(I), value)... };
		}

		template< std::size_t ToN, typename T, std::size_t... I >
		[[nodiscard]]
		constexpr const auto EnlargeArray(const std::array< T, sizeof...(I) >& a,
										  std::index_sequence< I... >) {

			return std::array< T, ToN >{ a[I]... };
		}

		template< typename T, typename TupleT, std::size_t... I >
		[[nodiscard]]
		constexpr const auto TuppleToArray(const TupleT& t,
										   std::index_sequence< I... >) {

			return std::array< T, sizeof...(I) >{ std::get< I >(t)... };
		}

		template< typename T, std::size_t... I >
		[[nodiscard]]
		constexpr const auto ArrayToTupple(const std::array< T, sizeof...(I) >& a,
										   std::index_sequence< I... >) noexcept {

			return std::make_tuple(a[I]...);
		}
	}

	template< typename ActionT, typename FromT, std::size_t N >
	[[nodiscard]]
	constexpr const auto TransformArray(ActionT&& action,
										const std::array< FromT, N >& a) {

		return details::TransformArray(std::forward< ActionT >(action), a,
									   std::make_index_sequence< N >());
	}

	template< typename ToT, typename FromT, std::size_t N >
	[[nodiscard]]
	constexpr const auto StaticCastArray(const std::array< FromT, N >& a) {
		constexpr auto f = [](const FromT& v) {
			return static_cast< ToT >(v);
		};
		return TransformArray(f, a);
	}

	template< typename T, std::size_t N >
	[[nodiscard]]
	constexpr const auto FillArray(const T& value) {
		return details::FillArray(value, std::make_index_sequence< N >());
	}

	template< std::size_t ToN, typename T, std::size_t FromN >
	[[nodiscard]]
	constexpr const auto EnlargeArray(const std::array< T, FromN >& a) {
		return details::EnlargeArray< ToN >(a, std::make_index_sequence< FromN >());
	}

	template< typename T, typename... Ts >
	[[nodiscard]]
	constexpr const auto TuppleToArray(const std::tuple< T, Ts... >& t) {
		constexpr auto N = sizeof...(Ts) + 1u;
		return details::TuppleToArray< T >(t, std::make_index_sequence< N >());
	}

	template< typename T, std::size_t N >
	[[nodiscard]]
	constexpr const auto ArrayToTupple(const std::array< T, N >& a) {
		return details::ArrayToTupple(a, std::make_index_sequence< N >());
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Array
	//-------------------------------------------------------------------------
	#pragma region

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	template< typename T, std::size_t N, std::size_t A = alignof(T),
		      typename = std::enable_if_t< (N > 1u) > >
	struct alignas(A) Array : public std::array< T, N > {

	public:

		static constexpr std::size_t s_size = N;

		constexpr Array() noexcept
			: std::array< T, N >{} {}

		constexpr explicit Array(const T& value) noexcept
			: std::array< T, N >(FillArray< T, N >(value)) {}

		template< typename... ArgsT,
			      typename = std::enable_if_t< (N == sizeof...(ArgsT)) > >
		constexpr Array(ArgsT&&... args) noexcept
			: std::array< T, N >{ std::forward< ArgsT >(args)... } {}

		template< std::size_t FromN,
			      typename = std::enable_if_t< (FromN < N) > >
		constexpr Array(const Array< T, FromN, A >& a) noexcept
			: std::array< T, N >(EnlargeArray< N >(a)) {}

		template< std::size_t FromN, std::size_t FromA,
			      typename = std::enable_if_t< (FromN < N && FromA != A) > >
		constexpr explicit Array(const Array< T, FromN, FromA >& a) noexcept
			: std::array< T, N >(EnlargeArray< N >(a)) {}

		template< std::size_t FromN, typename... ArgsT,
			      typename = std::enable_if_t< (FromN < N && (FromN + sizeof...(ArgsT)) == N) > >
		constexpr Array(const Array< T, FromN, A >& a, ArgsT&&... args) noexcept
			: std::array< T, N >(TuppleToArray(std::tuple_cat(ArrayToTupple(a),
							     std::make_tuple(std::forward< ArgsT >(args)...)))) {}

		template< std::size_t FromN, std::size_t FromA, typename... ArgsT,
			      typename = std::enable_if_t< (FromN < N && (FromN + sizeof...(ArgsT)) == N && FromA != A) > >
		constexpr explicit Array(const Array< T, FromN, FromA >& a, ArgsT&&... args) noexcept
			: std::array< T, N >(TuppleToArray(std::tuple_cat(ArrayToTupple(a),
							     std::make_tuple(std::forward< ArgsT >(args)...)))) {}

		constexpr Array(const Array& a) noexcept = default;

		constexpr Array(Array&& a) noexcept = default;

		template< typename FromT, std::size_t FromA,
			      typename = std::enable_if_t< std::is_convertible_v< FromT, T > > >
		constexpr explicit Array(const Array< FromT, N, FromA >& a) noexcept
			: std::array< T, N >(StaticCastArray< T >(a)) {}

		~Array() = default;

		Array& operator=(const Array& a) noexcept = default;

		Array& operator=(Array&& a) noexcept = default;
	};

	#pragma warning( pop )

	#pragma endregion
}

namespace std {

	template< typename T, std::size_t N, std::size_t A >
	struct tuple_size< mage::Array< T, N, A > >
		: public integral_constant< std::size_t, N > {};

	template< std::size_t I, typename T, std::size_t N, std::size_t A >
	struct tuple_element< I, mage::Array< T, N, A > > {

	public:

		using type = T;
	};
}
