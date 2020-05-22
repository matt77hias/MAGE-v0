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
	// Complex
	//-------------------------------------------------------------------------

	template< typename T,
		      typename = std::enable_if_t< std::is_floating_point_v< T > > >
	struct Complex : public Array< T, 2u > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Complex(T xy = T(0)) noexcept
			: Complex(xy, xy) {}

		constexpr Complex(T x, T y) noexcept
			: Array(x, y) {}

		constexpr Complex(const Complex& v) noexcept = default;

		constexpr Complex(Complex&& v) noexcept = default;

		template< typename U >
		constexpr explicit Complex(const Complex< U >& v) noexcept
			: Complex(static_cast< T >(v.Re()),
				      static_cast< T >(v.Im())) {}

		~Complex() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Complex& operator=(const Complex& v) noexcept = default;

		Complex& operator=(Complex&& v) noexcept = default;

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
		constexpr const Complex operator+() const noexcept {
			// +(Re, Im) = (Re, Im)
			return *this;
		}

		[[nodiscard]]
		constexpr const Complex operator-() const noexcept {
			// -(Re, Im) = (-Re, -Im)
			return { -Re(), -Im() };
		}

		[[nodiscard]]
		constexpr const Complex operator+(const Complex& v) const noexcept {
			// (Re, Im) + (v.Re, v.Im) = (Re + v.Re, Im + v.Im)
			return { Re() + v.Re(), Im() + v.Im() };
		}

		[[nodiscard]]
		constexpr const Complex operator-(const Complex& v) const noexcept {
			// (Re, Im) - (v.Re, v.Im) = (Re - v.Re, Im - v.Im)
			return { Re() - v.Re(), Im() - v.Im() };
		}

		[[nodiscard]]
		constexpr const Complex operator*(const Complex& v) const noexcept {
			// (Re, Im) * (v.Re, v.Im) = (Re * v.Re - Im * v.Im,
			//                            Im * v.Re + Re * v.Im)
			return {
				Re() * v.Re() - Im() * v.Im(),
				Im() * v.Re() + Re() * v.Im()
			};
		}

		[[nodiscard]]
		constexpr const Complex operator/(const Complex& v) const noexcept {
			// (Re, Im) / (v.Re, v.Im) = 1 / (v.Re^2 + v.Im^2) *
			//                           (Re * v.Re + Im * v.Im,
			//                            Im * v.Re - Re * v.Im)
			const T inv = T(1) / v.SqrAbs();
			return {
				inv * (Re() * v.Re() + Im() * v.Im()),
				inv * (Im() * v.Re() - Re() * v.Im())
			};
		}

		[[nodiscard]]
		constexpr const Complex operator+(T a) const noexcept {
			// (Re, Im) + (a, 0) = (Re + a, Im)
			return { Re() + a, Im() };
		}

		[[nodiscard]]
		constexpr const Complex operator-(T a) const noexcept {
			// (Re, Im) - (a, 0) = (Re - a, Im)
			return { Re() - a, Im() };
		}

		[[nodiscard]]
		constexpr const Complex operator*(T a) const noexcept {
			// (Re, Im) * (a, 0) = (Re * a, Im * a)
			return { Re() * a, Im() * a };
		}

		[[nodiscard]]
		constexpr const Complex operator/(T a) const noexcept {
			// (Re, Im) / (a, 0) = (Re / a, Im / a)
			const T inv_a = T(1) / a;
			return { Re() * inv_a, Im() * inv_a };
		}

		Complex& operator+=(const Complex& v) noexcept {
			// (Re, Im) + (v.Re, v.Im) = (Re + v.Re, Im + v.Im)
			Re() += v.Re();
			Im() += v.Im();
			return *this;
		}

		Complex& operator-=(const Complex& v) noexcept {
			// (Re, Im) - (v.Re, v.Im) = (Re - v.Re, Im - v.Im)
			Re() -= v.Re();
			Im() -= v.Im();
			return *this;
		}

		Complex& operator*=(const Complex& v) noexcept {
			// (Re, Im) * (v.Re, v.Im) = (Re * v.Re - Im * v.Im,
			//                            Im * v.Re + Re * v.Im)
			Re() = Re() * v.Re() - Im() * v.Im();
			Im() = Re() * v.Im() + Im() * v.Re();
			return *this;
		}

		Complex& operator/=(const Complex& v) noexcept {
			// (Re, Im) / (v.Re, v.Im) = 1 / (v.Re^2 + v.Im^2) *
			//                           (Re * v.Re + Im * v.Im,
			//                            Im * v.Re - Re * v.Im)
			const T inv = T(1) / v.SqrAbs();
			Re() = inv * (Re() * v.Re() + Im() * v.Im());
			Im() = inv * (Im() * v.Re() - Re() * v.Im());
			return *this;
		}

		Complex& operator+=(T a) noexcept {
			// (Re, Im) + (a, 0) = (Re + a, Im)
			Re() += a;
			return *this;
		}

		Complex& operator-=(T a) noexcept {
			// (Re, Im) - (a, 0) = (Re - a, Im)
			Re() -= a;
			return *this;
		}

		Complex& operator*=(T a) noexcept {
			// (Re, Im) * (a, 0) = (Re * a, Im * a)
			Re() *= a;
			Im() *= a;
			return *this;
		}

		Complex& operator/=(T a) noexcept {
			// (Re, Im) / (a, 0) = (Re / a, Im / a)
			const T inv_a = T(1) / a;
			Re() *= inv_a;
			Im() *= inv_a;
			return *this;
		}

		[[nodiscard]]
		constexpr bool operator==(const Complex& v) const {
			return Re() == v.Re() && Im() == v.Im();
		}

		[[nodiscard]]
		constexpr bool operator!=(const Complex& v) const {
			return !(*this == v);
		}

		[[nodiscard]]
		constexpr const Complex Conjugate() const noexcept {
			return { Re(), -Im() };
		}

		[[nodiscard]]
		constexpr const T Norm() const noexcept {
			return SqrAbs();
		}

		[[nodiscard]]
		constexpr const T SqrAbs() const noexcept {
			return Re() * Re() + Im() * Im();
		}

		[[nodiscard]]
		const T Abs() const noexcept {
			return std::sqrt(SqrAbs());
		}

		Complex& Normalize() noexcept {
			const T a = T(1) / Abs();
			Re() *= a;
			Im() *= a;
			return *this;
		}

		[[nodiscard]]
		const T Arg() const noexcept {
			return std::atan2(Im(), Re());
		}
	};

	template< typename T >
	[[nodiscard]]
	constexpr const Complex< T > operator+(T a, const Complex< T >& v) noexcept {
		// (a, 0) + (v.Re, v.Im) = (a + v.Re, v.Im)
		return v + a;
	}

	template< typename T >
	[[nodiscard]]
	constexpr const Complex< T > operator-(T a, const Complex< T >& v) noexcept {
		// (a, 0) - (v.Re, v.Im) = (a - v.Re, v.Im)
		return v - a;
	}

	template< typename T >
	[[nodiscard]]
	constexpr const Complex< T > operator*(T a, const Complex< T >& v) noexcept {
		// (a, 0) * (v.Re, v.Im) = (a * v.Re, a * v.Im)
		return v * a;
	}

	template< typename T >
	[[nodiscard]]
	constexpr const Complex< T > operator/(T a, const Complex< T >& v) noexcept {
		// (a, 0) / (v.Re, v.Im) = 1 / (v.Re^2 + v.Im^2) * (a * v.Re, -a * v.Im)
		const T inv = T(1) / v.SqrAbs();
		return { inv * (a * v.Re()), inv * (-a * v.Im()) };
	}

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	using C32 = Complex< F32 >;
	using C64 = Complex< F64 >;

	static_assert(sizeof(C32) == sizeof(F32x2));
	static_assert(sizeof(C64) == sizeof(F64x2));
}

namespace std {

	template< typename T >
	struct tuple_size< mage::Complex< T > >
		: public integral_constant< std::size_t, 2u > {};

	template< std::size_t I, typename T >
	struct tuple_element< I, mage::Complex< T > > {

	public:

		using type = T;
	};
}
