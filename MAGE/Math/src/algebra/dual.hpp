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
	// Dual
	//-------------------------------------------------------------------------

	template< typename T, 
		      typename = std::enable_if_t< std::is_floating_point_v< T > > >
	struct Dual : public Array< T, 2u > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Dual(T xy = T(0)) noexcept
			: Dual(xy, xy) {}
		
		constexpr Dual(T x, T y) noexcept
			: Array(x, y) {}
		
		constexpr Dual(const Dual& v) noexcept = default;
		
		constexpr Dual(Dual&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit Dual(const Dual< U >& v) noexcept
			: Dual(static_cast< T >(v.Re()),
				   static_cast< T >(v.Du())) {}
		
		~Dual() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Dual& operator=(const Dual& v) noexcept = default;
		
		Dual& operator=(Dual&& v) noexcept = default;

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
		T& Du() noexcept {
			return operator[](1u);
		}
		
		[[nodiscard]]
		constexpr const T Du() const noexcept {
			return operator[](1u);
		}

		[[nodiscard]]
		constexpr const Dual operator+() const noexcept {
			// +(Re, Du) = (Re, Du)
			return *this;
		}
		
		[[nodiscard]]
		constexpr const Dual operator-() const noexcept {
			// -(Re, Du) = (-Re, -Du)
			return { -Re(), -Du() };
		}
		
		[[nodiscard]]
		constexpr const Dual operator+(const Dual& v) const noexcept {
			// (Re, Du) + (v.Re, v.Du) = (Re + v.Re, Du + v.Du)
			return { Re() + v.Re(), Du() + v.Du() };
		}
		
		[[nodiscard]]
		constexpr const Dual operator-(const Dual& v) const noexcept {
			// (Re, Du) - (v.Re, v.Du) = (Re - v.Re, Du - v.Du)
			return { Re() - v.Re(), Du() - v.Du() };
		}
		
		[[nodiscard]]
		constexpr const Dual operator*(const Dual& v) const noexcept {
			// (Re, Im) * (v.Re, v.Im) = (Re * v.Re, Re * v.Du + Du * v.Re)
			return { Re() * v.Re(), Re() * v.Du() + Du() * v.Re() };
		}
		
		[[nodiscard]]
		constexpr const Dual operator/(const Dual& v) const noexcept {
			// (Re, Im) / (v.Re, v.Im) = (Re / v.Re, 
			//                            (Du * v.Re - Re * v.Du) / v.Re^2)
			const T inv_Re = T(1) / v.Re();
			return { 
				inv_Re * Re(), 
				inv_Re * inv_Re * (Du() * v.Re() - Re() * v.Du()) 
			};
		}
		
		[[nodiscard]]
		constexpr const Dual operator+(T a) const noexcept {
			// (Re, Du) + (a, 0) = (Re + a, Du)
			return { Re() + a, Du() };
		}
		
		[[nodiscard]]
		constexpr const Dual operator-(T a) const noexcept {
			// (Re, Du) - (a, 0) = (Re - a, Du)
			return { Re() - a, Du() };
		}
		
		[[nodiscard]]
		constexpr const Dual operator*(T a) const noexcept {
			// (Re, Du) * (a, 0) = (Re * a, Du * a)
			return { Re() * a, Du() * a };
		}
		
		[[nodiscard]]
		constexpr const Dual operator/(T a) const noexcept {
			// (Re, Du) / (a, 0) = (Re / a, Du / a)
			const T inv_a = T(1) / a;
			return { Re() * inv_a, Du() * inv_a };
		}

		Dual& operator+=(const Dual& v) noexcept {
			// (Re, Du) + (v.Re, v.Du) = (Re + v.Re, Du + v.Du)
			Re() += v.Re();
			Du() += v.Du();
			return *this;
		}
		
		Dual& operator-=(const Dual& v) noexcept {
			// (Re, Du) - (v.Re, v.Du) = (Re - v.Re, Du - v.Du)
			Re() -= v.Re();
			Du() -= v.Du();
			return *this;
		}
		
		Dual& operator*=(const Dual& v) noexcept {
			// (Re, Im) * (v.Re, v.Im) = (Re * v.Re, Re * v.Du + Du * v.Re)
			Re() = Re() * v.Re();
			Du() = Re() * v.Du() + Du() * v.Re();
			return *this;
		}
		
		Dual& operator/=(const Dual& v) noexcept {
			// (Re, Im) / (v.Re, v.Im) = (Re / v.Re, 
			//                            (Du * v.Re - Re * v.Du) / v.Re^2)
			const T inv_Re = T(1) / v.Re();
			Re() *= inv_Re;
			Du()  = inv_Re * inv_Re * (Du() * v.Re() - Re() * v.Du());
			return *this;
		}
		
		Dual& operator+=(T a) noexcept {
			// (Re, Du) + (a, 0) = (Re + a, Du)
			Re() += a;
			return *this;
		}
		
		Dual& operator-=(T a) noexcept {
			// (Re, Du) - (a, 0) = (Re - a, Du)
			Re() -= a;
			return *this;
		}
		
		Dual& operator*=(T a) noexcept {
			// (Re, Du) * (a, 0) = (Re * a, Du * a)
			Re() *= a;
			Du() *= a;
			return *this;
		}
		
		Dual& operator/=(T a) noexcept {
			// (Re, Du) / (a, 0) = (Re / a, Du / a)
			const T inv_a = T(1) / a;
			Re() *= inv_a;
			Du() *= inv_a;
			return *this;
		}

		[[nodiscard]]
		constexpr bool operator==(const Dual& v) const {
			return Re() == v.Re() && Du() == v.Du();
		}
		
		[[nodiscard]]
		constexpr bool operator!=(const Dual& v) const {
			return !(*this == v);
		}
	};

	template< typename T >
	[[nodiscard]]
	constexpr const Dual< T > operator+(T a, const Dual< T >& v) noexcept {
		// (a, 0) + (v.Re, v.Du) = (a + v.Re, v.Du)
		return v + a;
	}
	
	template< typename T >
	[[nodiscard]]
	constexpr const Dual< T > operator-(T a, const Dual< T >& v) noexcept {
		// (a, 0) - (v.Re, v.Du) = (a - v.Re, v.Du)
		return v - a;
	}
	
	template< typename T >
	[[nodiscard]]
	constexpr const Dual< T > operator*(T a, const Dual< T >& v) noexcept {
		// (a, 0) * (v.Re, v.Du) = (a * v.Re, a * v.Du)
		return v * a;
	}
	
	template< typename T >
	[[nodiscard]]
	constexpr const Dual< T > operator/(T a, const Dual< T >& v) noexcept {
		// (a, 0) / (v.Re, v.Im) = (a / v.Re, (-a * v.Du) / v.Re^2)
		const T inv = T(1) / v.Re();
		return { inv * a, inv * inv * (-a * v.Du()) };
	}

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	using D32 = Dual< F32 >;
	using D64 = Dual< F64 >;

	static_assert(sizeof(D32) == sizeof(F32x2));
	static_assert(sizeof(D64) == sizeof(F64x2));
}

namespace std {

	template< typename T >
	struct tuple_size< mage::Dual< T > >
		: public integral_constant< std::size_t, 2u > {};

	template< std::size_t I, typename T >
	struct tuple_element< I, mage::Dual< T > > {

	public:

		using type = T;
	};
}
