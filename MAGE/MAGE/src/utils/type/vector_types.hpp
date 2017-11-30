#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

// Primitive types.
#include "utils\type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <type_traits>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Declarations and Definitions: Vector2
	//-------------------------------------------------------------------------
#pragma region

	template< typename T, typename Enable = void >
	struct Vector2;

	template< typename T >
	struct Vector2< T,
		typename std::enable_if_t< std::is_arithmetic_v< T >, void > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector2(T xy = 0) noexcept
			: Vector2(xy, xy) {}
		constexpr Vector2(T x, T y) noexcept
			: m_x(x), m_y(y) {}
		constexpr Vector2(const Vector2 &v) noexcept = default;
		constexpr Vector2(Vector2 &&v) noexcept = default;
		template< typename U >
		constexpr explicit Vector2(const Vector2< U > &v) noexcept
			: Vector2(static_cast< T >(v.m_x), 
				      static_cast< T >(v.m_y)) {}
		~Vector2() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector2 &operator=(const Vector2 &v) = default;
		constexpr Vector2 &operator=(Vector2 &&v) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		constexpr T operator[](size_t i) const noexcept {
			return (&m_x)[i];
		}
		constexpr T &operator[](size_t i) noexcept {
			return (&m_x)[i];
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		T m_y;
	};

#pragma endregion

	//-------------------------------------------------------------------------
	// Declarations and Definitions: Vector3
	//-------------------------------------------------------------------------
#pragma region

	template< typename T, typename Enable = void >
	struct Vector3;

	template< typename T >
	struct Vector3< T, 
		typename std::enable_if_t< std::is_arithmetic_v< T >, void > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector3(T xyz = 0) noexcept
			: Vector3(xyz, xyz, xyz) {}
		constexpr Vector3(T x, T y, T z) noexcept
			: m_x(x), m_y(y), m_z(z) {}
		constexpr explicit Vector3(const Vector2< T > &v, T z = 0) noexcept
			: Vector3(v.m_x, v.m_y, z) {}
		constexpr Vector3(const Vector3 &v) noexcept = default;
		constexpr Vector3(Vector3 &&v) noexcept = default;
		template< typename U >
		constexpr explicit Vector3(const Vector3< U > &v) noexcept
			: Vector3(static_cast< T >(v.m_x),
				      static_cast< T >(v.m_y),
				      static_cast< T >(v.m_z)) {}
		~Vector3() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector3 &operator=(const Vector3 &v) = default;
		constexpr Vector3 &operator=(Vector3 &&v) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		constexpr T operator[](size_t i) const noexcept {
			return (&m_x)[i];
		}
		constexpr T &operator[](size_t i) noexcept {
			return (&m_x)[i];
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		T m_y;
		T m_z;
	};

#pragma endregion

	//-------------------------------------------------------------------------
	// Declarations and Definitions: Vector4
	//-------------------------------------------------------------------------
#pragma region

	template< typename T, typename Enable = void >
	struct Vector4;

	template< typename T >
	struct Vector4< T, 
		typename std::enable_if_t< std::is_arithmetic_v< T >, void > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector4(T xyzw = 0) noexcept
			: Vector4(xyzw, xyzw, xyzw, xyzw) {}
		constexpr Vector4(T x, T y, T z, T w) noexcept
			: m_x(x), m_y(y), m_z(z), m_w(w) {}
		constexpr explicit Vector4(const Vector2< T > &v, T z = 0, T w = 0) noexcept
			: Vector3(v.m_x, v.m_y, z, w) {}
		constexpr explicit Vector4(const Vector3< T > &v, T w = 0) noexcept
			: Vector3(v.m_x, v.m_y, v.m_z, w) {}
		constexpr Vector4(const Vector4 &v) noexcept = default;
		constexpr Vector4(Vector4 &&v) noexcept = default;
		template< typename U >
		constexpr explicit Vector4(const Vector4< U > &v) noexcept
			: Vector4(static_cast< T >(v.m_x),
				      static_cast< T >(v.m_y),
				      static_cast< T >(v.m_z),
				      static_cast< T >(v.m_w)) {}
		~Vector4() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector4 &operator=(const Vector4 &v) = default;
		constexpr Vector4 &operator=(Vector4 &&v) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		constexpr T operator[](size_t i) const noexcept {
			return (&m_x)[i];
		}
		constexpr T &operator[](size_t i) noexcept {
			return (&m_x)[i];
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		T m_y;
		T m_z;
		T m_w;
	};

#pragma endregion

	//-------------------------------------------------------------------------
	// Declarations and Definitions: Vector2A
	//-------------------------------------------------------------------------
#pragma region

#pragma warning( push )
#pragma warning( disable : 4324)

	template< typename T, typename Enable = void >
	struct alignas(16) Vector2A;

	template< typename T >
	struct alignas(16) Vector2A< T, 
		typename std::enable_if_t< std::is_arithmetic_v< T >, void > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector2A(T xy = 0) noexcept
			: Vector2A(xy, xy) {}
		constexpr Vector2A(T x, T y) noexcept
			: m_x(x), m_y(y) {}
		constexpr Vector2A(const Vector2A &v) noexcept = default;
		constexpr Vector2A(Vector2A &&v) noexcept = default;
		template< typename U >
		constexpr explicit Vector2A(const Vector2< U > &v) noexcept
			: Vector2A(static_cast< T >(v.m_x),
				       static_cast< T >(v.m_y)) {}
		template< typename U >
		constexpr explicit Vector2A(const Vector2A< U > &v) noexcept
			: Vector2A(static_cast< T >(v.m_x),
				       static_cast< T >(v.m_y)) {}
		~Vector2A() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector2A &operator=(const Vector2A &v) = default;
		constexpr Vector2A &operator=(Vector2A &&v) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		constexpr T operator[](size_t i) const noexcept {
			return (&m_x)[i];
		}
		constexpr T &operator[](size_t i) noexcept {
			return (&m_x)[i];
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		T m_y;
	};

#pragma warning( pop )

#pragma endregion

	//-------------------------------------------------------------------------
	// Declarations and Definitions: Vector3A
	//-------------------------------------------------------------------------
#pragma region

#pragma warning( push )
#pragma warning( disable : 4324)

	template< typename T, typename Enable = void >
	struct alignas(16) Vector3A;

	template< typename T >
	struct alignas(16) Vector3A< T,
		typename std::enable_if_t< std::is_arithmetic_v< T >, void > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector3A(T xyz = 0) noexcept
			: Vector3A(xyz, xyz, xyz) {}
		constexpr Vector3A(T x, T y, T z) noexcept
			: m_x(x), m_y(y), m_z(z) {}
		constexpr explicit Vector3A(const Vector2A< T > &v, T z = 0) noexcept
			: Vector3A(v.m_x, v.m_y, z) {}
		constexpr Vector3A(const Vector3A &v) noexcept = default;
		constexpr Vector3A(Vector3A &&v) noexcept = default;
		template< typename U >
		constexpr explicit Vector3A(const Vector3< U > &v) noexcept
			: Vector3A(static_cast< T >(v.m_x),
				       static_cast< T >(v.m_y),
				       static_cast< T >(v.m_z)) {}
		template< typename U >
		constexpr explicit Vector3A(const Vector3A< U > &v) noexcept
			: Vector3A(static_cast< T >(v.m_x),
				       static_cast< T >(v.m_y),
				       static_cast< T >(v.m_z)) {}
		~Vector3A() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector3A &operator=(const Vector3A &v) = default;
		constexpr Vector3A &operator=(Vector3A &&v) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		constexpr T operator[](size_t i) const noexcept {
			return (&m_x)[i];
		}
		constexpr T &operator[](size_t i) noexcept {
			return (&m_x)[i];
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		T m_y;
		T m_z;
	};

#pragma warning( pop )

#pragma endregion

	//-------------------------------------------------------------------------
	// Declarations and Definitions: Vector4A
	//-------------------------------------------------------------------------
#pragma region

#pragma warning( push )
#pragma warning( disable : 4324)

	template< typename T, typename Enable = void >
	struct __declspec(align(16)) Vector4A;

	template< typename T >
	struct __declspec(align(16)) Vector4A< T, 
		typename std::enable_if_t< std::is_arithmetic_v< T >, void > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector4A(T xyzw = 0) noexcept
			: Vector4A(xyzw, xyzw, xyzw, xyzw) {}
		constexpr Vector4A(T x, T y, T z, T w) noexcept
			: m_x(x), m_y(y), m_z(z), m_w(w) {}
		constexpr explicit Vector4A(const Vector2A< T > &v, T z = 0, T w = 0) noexcept
			: Vector4A(v.m_x, v.m_y, z, w) {}
		constexpr explicit Vector4A(const Vector3A< T > &v, T w = 0) noexcept
			: Vector4A(v.m_x, v.m_y, v.m_z, w) {}
		constexpr Vector4A(const Vector4A &v) noexcept = default;
		constexpr Vector4A(Vector4A &&v) noexcept = default;
		template< typename U >
		constexpr explicit Vector4A(const Vector4< U > &v) noexcept
			: Vector4A(static_cast< T >(v.m_x),
				       static_cast< T >(v.m_y),
				       static_cast< T >(v.m_z),
				       static_cast< T >(v.m_w)) {}
		template< typename U >
		constexpr explicit Vector4A(const Vector4A< U > &v) noexcept
			: Vector4A(static_cast< T >(v.m_x),
				       static_cast< T >(v.m_y),
				       static_cast< T >(v.m_z),
				       static_cast< T >(v.m_w)) {}
		~Vector4A() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector4A &operator=(const Vector4A &v) = default;
		constexpr Vector4A &operator=(Vector4A &&v) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		constexpr T operator[](size_t i) const noexcept {
			return (&m_x)[i];
		}
		constexpr T &operator[](size_t i) noexcept {
			return (&m_x)[i];
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		T m_y;
		T m_z;
		T m_w;
	};

#pragma warning( pop )

#pragma endregion

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Floating Point Vectors
	//-------------------------------------------------------------------------

	/**
	 A 2x1 32-bit floating point vector.
	 */
	using _F32x2 = Vector2< F32 >;

	/**
	 A 3x1 32-bit floating point vector.
	 */
	using _F32x3 = Vector3< F32 >;

	/**
	 A 4x1 32-bit floating point vector.
	 */
	using _F32x4 = Vector4< F32 >;

	/**
	 A 2x1 32-bit floating point aligned vector.
	 */
	using _F32x2A = Vector2A< F32 >;

	/**
	 A 3x1 32-bit floating point aligned vector.
	 */
	using _F32x3A = Vector3A< F32 >;

	/**
	 A 4x1 32-bit floating point aligned vector.
	 */
	using _F32x4A = Vector4A< F32 >;

	static_assert(8  == sizeof(_F32x2));
	static_assert(12 == sizeof(_F32x3));
	static_assert(16 == sizeof(_F32x4));

	static_assert(16 == sizeof(_F32x2A));
	static_assert(16 == sizeof(_F32x3A));
	static_assert(16 == sizeof(_F32x4A));

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Signed Integer Vectors
	//-------------------------------------------------------------------------

	/**
	 A 2x1 signed 32-bit integer vector.
	 */
	using _S32x2 = Vector2< S32 >;

	/**
	 A 3x1 signed 32-bit integer vector.
	 */
	using _S32x3 = Vector3< S32 >;

	/**
	 A 4x1 signed 32-bit integer vector.
	 */
	using _S32x4 = Vector4< S32 >;

	static_assert(8  == sizeof(_S32x2));
	static_assert(12 == sizeof(_S32x3));
	static_assert(16 == sizeof(_S32x4));

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions: Unsigned Integer Vectors
	//-------------------------------------------------------------------------

	/**
	 An 2x1 unsigned 32-bit integer vector.
	 */
	using _U32x2 = Vector2< U32 >;

	/**
	 An 3x1 unsigned 32-bit integer vector.
	 */
	using _U32x3 = Vector3< U32 >;

	/**
	 An 4x1 unsigned 32-bit integer vector.
	 */
	using _U32x4 = Vector4< U32 >;

	static_assert(8  == sizeof(_U32x2));
	static_assert(12 == sizeof(_U32x3));
	static_assert(16 == sizeof(_U32x4));
}