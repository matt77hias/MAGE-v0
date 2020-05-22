#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Hyperbolic
	//-------------------------------------------------------------------------

	template< typename T,
		      typename = std::enable_if_t< std::is_floating_point_v< T > > >
	struct Hyperbolic : public Array< T, 2u > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Hyperbolic(T xy = T(0)) noexcept
			: Hyperbolic(xy, xy) {}

		constexpr Hyperbolic(T x, T y) noexcept
			: Array(x, y) {}

		constexpr Hyperbolic(const Hyperbolic& v) noexcept = default;

		constexpr Hyperbolic(Hyperbolic&& v) noexcept = default;

		template< typename U >
		constexpr explicit Hyperbolic(const Hyperbolic< U >& v) noexcept
			: Hyperbolic(static_cast< T >(v.Re()),
				         static_cast< T >(v.Im())) {}

		~Hyperbolic() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Hyperbolic& operator=(const Hyperbolic& v) noexcept = default;

		Hyperbolic& operator=(Hyperbolic&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		T& Re() noexcept {
			return operator[](0u);
		}

		[[nodiscard]]
		constexpr const T Re() const noexcept {
			return operator[](0u);
		}

		[[nodiscard]]
		T& Im() noexcept {
			return operator[](1u);
		}

		[[nodiscard]]
		constexpr const T Im() const noexcept {
			return operator[](1u);
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator+() const noexcept {
			// +(Re, Im) = (Re, Im)
			return *this;
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator-() const noexcept {
			// -(Re, Im) = (-Re, -Im)
			return { -Re(), -Im() };
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator+(const Hyperbolic& v) const noexcept {
			// (Re, Im) + (v.Re, v.Im) = (Re + v.Re, Im + v.Im)
			return { Re() + v.Re(), Im() + v.Im() };
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator-(const Hyperbolic& v) const noexcept {
			// (Re, Im) - (v.Re, v.Im) = (Re - v.Re, Im - v.Im)
			return { Re() - v.Re(), Im() - v.Im() };
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator*(const Hyperbolic& v) const noexcept {
			// (Re, Im) * (v.Re, v.Im) = (Re * v.Re + Im * v.Im,
			//                            Re * v.Im + Im * v.Re)
			return {
				Re() * v.Re() + Im() * v.Im(),
				Re() * v.Im() + Im() * v.Re()
			};
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator+(T a) const noexcept {
			// (Re, Im) + (a, 0) = (Re + a, Im)
			return { Re() + a, Im() };
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator-(T a) const noexcept {
			// (Re, Im) - (a, 0) = (Re - a, Im)
			return { Re() - a, Im() };
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator*(T a) const noexcept {
			// (Re, Im) * (a, 0) = (Re * a, Im * a)
			return { Re() * a, Im() * a };
		}

		[[nodiscard]]
		constexpr const Hyperbolic operator/(T a) const noexcept {
			// (Re, Im) / (a, 0) = (Re / a, Im / a)
			const T inv_a = T(1) / a;
			return { Re() * inv_a, Im() * inv_a };
		}

		Hyperbolic& operator+=(const Hyperbolic& v) noexcept {
			// (Re, Im) + (v.Re, v.Im) = (Re + v.Re, Im + v.Im)
			Re() += v.Re();
			Im() += v.Im();
			return *this;
		}

		Hyperbolic& operator-=(const Hyperbolic& v) noexcept {
			// (Re, Im) - (v.Re, v.Im) = (Re - v.Re, Im - v.Im)
			Re() -= v.Re();
			Im() -= v.Im();
			return *this;
		}

		Hyperbolic& operator*=(const Hyperbolic& v) noexcept {
			// (Re, Im) * (v.Re, v.Im) = (Re * v.Re + Im * v.Im,
			//                            Re * v.Im + Im * v.Re)
			Re() = Re() * v.Re() + Im() * v.Im();
			Im() = Re() * v.Im() + Im() * v.Re();
			return *this;
		}

		Hyperbolic& operator+=(T a) noexcept {
			// (Re, Im) + (a, 0) = (Re + a, Im)
			Re() += a;
			return *this;
		}

		Hyperbolic& operator-=(T a) noexcept {
			// (Re, Im) - (a, 0) = (Re - a, Im)
			Re() -= a;
			return *this;
		}

		Hyperbolic& operator*=(T a) noexcept {
			// (Re, Im) * (a, 0) = (Re * a, Im * a)
			Re() *= a;
			Im() *= a;
			return *this;
		}

		Hyperbolic& operator/=(T a) noexcept {
			// (Re, Im) / (a, 0) = (Re / a, Im / a)
			const T inv_a = T(1) / a;
			Re() *= inv_a;
			Im() *= inv_a;
			return *this;
		}

		[[nodiscard]]
		constexpr bool operator==(const Hyperbolic& v) const {
			return Re() == v.Re() && Im() == v.Im();
		}

		[[nodiscard]]
		constexpr bool operator!=(const Hyperbolic& v) const {
			return !(*this == v);
		}

		[[nodiscard]]
		constexpr const Hyperbolic Conjugate() const noexcept {
			return { Re(), -Im() };
		}

		[[nodiscard]]
		constexpr const T Modulus() const noexcept {
			return Re() * Re() - Im() * Im();
		}
	};

	template< typename T >
	[[nodiscard]]
	constexpr const Hyperbolic< T > operator+(T a, const Hyperbolic< T >& v) noexcept {
		// (a, 0) + (v.Re, v.Im) = (a + v.Re, v.Im)
		return v + a;
	}

	template< typename T >
	[[nodiscard]]
	constexpr const Hyperbolic< T > operator-(T a, const Hyperbolic< T >& v) noexcept {
		// (a, 0) - (v.Re, v.Im) = (a - v.Re, v.Im)
		return v - a;
	}

	template< typename T >
	[[nodiscard]]
	constexpr const Hyperbolic< T > operator*(T a, const Hyperbolic< T >& v) noexcept {
		// (a, 0) * (v.Re, v.Im) = (a * v.Re, a * v.Im)
		return v * a;
	}

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	using H32 = Hyperbolic< F32 >;
	using H64 = Hyperbolic< F64 >;

	static_assert(sizeof(H32) == sizeof(F32x2));
	static_assert(sizeof(H64) == sizeof(F64x2));
}

namespace std {

	template< typename T >
	struct tuple_size< mage::Hyperbolic< T > >
		: public integral_constant< std::size_t, 2u > {};

	template< std::size_t I, typename T >
	struct tuple_element< I, mage::Hyperbolic< T > > {

	public:

		using type = T;
	};
}
