#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

// Scalar types.
#include "type\scalar_types.hpp"

#include "collection\array.hpp"
#include "collection\tupple.hpp"

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
	// Vector
	//-------------------------------------------------------------------------
	#pragma region

	template< typename T, size_t N, typename Enable = void >
	struct Vector;

	template< typename T >
	struct Vector< T, 2, 
		typename std::enable_if_t< std::is_arithmetic_v< T > > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector(T xy = 0) noexcept
			: Vector(xy, xy) {}
		
		constexpr Vector(T x, T y) noexcept
			: m_x(x), m_y(y) {}
		
		Vector(const T* v) noexcept
			: Vector(v[0], v[1]) {}
		
		constexpr Vector(const Vector& v) noexcept = default;
		
		constexpr Vector(Vector&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit Vector(const Vector< U, 2 >& v) noexcept
			: Vector(static_cast< T >(v.m_x), 
					 static_cast< T >(v.m_y)) {}
		
		~Vector() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector& operator=(const Vector& v) noexcept = default;
		
		constexpr Vector& operator=(Vector&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const T operator[](size_t i) noexcept {
			return GetData()[i];
		}
		
		[[nodiscard]]
		constexpr const T& operator[](size_t i) const noexcept {
			return GetData()[i];
		}

		[[nodiscard]]
		constexpr T* GetData() noexcept {
			return &m_x;
		}
		
		[[nodiscard]]
		constexpr const T* GetData() const noexcept {
			return &m_x;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		
		T m_y;
	};

	template< typename T >
	struct Vector< T, 3, 
		typename std::enable_if_t< std::is_arithmetic_v< T > > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector(T xyz = 0) noexcept
			: Vector(xyz, xyz, xyz) {}
		
		constexpr Vector(T x, T y, T z) noexcept
			: m_x(x), m_y(y), m_z(z) {}
		
		Vector(const T* v) noexcept
			: Vector(v[0], v[1], v[2]) {}
		
		constexpr explicit Vector(const Vector< T, 2 >& v, T z = 0) noexcept
			: Vector(v.m_x, v.m_y, z) {}
		
		constexpr Vector(const Vector& v) noexcept = default;
		
		constexpr Vector(Vector&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit Vector(const Vector< U, 3 >& v) noexcept
			: Vector(static_cast< T >(v.m_x), 
					 static_cast< T >(v.m_y), 
					 static_cast< T >(v.m_z)) {}
		
		~Vector() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector& operator=(const Vector& v) noexcept = default;
		
		constexpr Vector& operator=(Vector&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const T operator[](size_t i) noexcept {
			return GetData()[i];
		}
		
		[[nodiscard]]
		constexpr const T& operator[](size_t i) const noexcept {
			return GetData()[i];
		}

		[[nodiscard]]
		constexpr T* GetData() noexcept {
			return &m_x;
		}
		
		[[nodiscard]]
		constexpr const T* GetData() const noexcept {
			return &m_x;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;
		
		T m_y;
		
		T m_z;
	};

	template< typename T >
	struct Vector< T, 4, 
		typename std::enable_if_t< std::is_arithmetic_v< T > > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit Vector(T xyzw = 0) noexcept
			: Vector(xyzw, xyzw, xyzw, xyzw) {}
		
		constexpr Vector(T x, T y, T z, T w) noexcept
			: m_x(x), m_y(y), m_z(z), m_w(w) {}
		
		Vector(const T* v) noexcept
			: Vector(v[0], v[1], v[2], v[3]) {}
		
		constexpr explicit Vector(const Vector< T, 2 >& v, T z = 0, T w = 0) noexcept
			: Vector(v.m_x, v.m_y, z, w) {}
		
		constexpr explicit Vector(const Vector< T, 3 >& v, T w = 0) noexcept
			: Vector(v.m_x, v.m_y, v.m_z, w) {}
		
		constexpr Vector(const Vector& v) noexcept = default;
		
		constexpr Vector(Vector&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit Vector(const Vector< U, 4 >& v) noexcept
			: Vector(static_cast< T >(v.m_x),
					 static_cast< T >(v.m_y), 
					 static_cast< T >(v.m_z), 
					 static_cast< T >(v.m_w)) {}
		
		~Vector() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr Vector& operator=(const Vector& v) noexcept = default;

		constexpr Vector& operator=(Vector&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const T operator[](size_t i) noexcept {
			return GetData()[i];
		}
		
		[[nodiscard]]
		constexpr const T& operator[](size_t i) const noexcept {
			return GetData()[i];
		}

		[[nodiscard]]
		constexpr T* GetData() noexcept {
			return &m_x;
		}
		
		[[nodiscard]]
		constexpr const T* GetData() const noexcept {
			return &m_x;
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
	// VectorA
	//-------------------------------------------------------------------------
	#pragma region

	template< typename T, size_t N, typename Enable = void >
	struct alignas(16) VectorA;


	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	template< typename T >
	struct alignas(16) VectorA< T, 2, 
		typename std::enable_if_t< std::is_arithmetic_v< T > > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit VectorA(T xy = 0) noexcept
			: VectorA(xy, xy) {}
		
		constexpr VectorA(T x, T y) noexcept
			: m_x(x), m_y(y) {}
		
		VectorA(const T* v) noexcept
			: VectorA(v[0], v[1]) {}
		
		constexpr VectorA(const VectorA& v) noexcept = default;
		
		constexpr VectorA(VectorA&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit VectorA(const Vector< U, 2 >& v) noexcept
			: VectorA(static_cast< T >(v.m_x), 
					  static_cast< T >(v.m_y)) {}
		
		template< typename U >
		constexpr explicit VectorA(const VectorA< U, 2 >& v) noexcept
			: VectorA(static_cast< T >(v.m_x),
					  static_cast< T >(v.m_y)) {}
		
		~VectorA() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr VectorA& operator=(const VectorA& v) noexcept = default;
		
		constexpr VectorA& operator=(VectorA&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const T operator[](size_t i) noexcept {
			return GetData()[i];
		}
		
		[[nodiscard]]
		constexpr const T& operator[](size_t i) const noexcept {
			return GetData()[i];
		}

		[[nodiscard]]
		constexpr T* GetData() noexcept {
			return &m_x;
		}
		
		[[nodiscard]]
		constexpr const T* GetData() const noexcept {
			return &m_x;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;

		T m_y;
	};

	template< typename T >
	struct alignas(16) VectorA< T, 3, 
		typename std::enable_if_t< std::is_arithmetic_v< T > > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit VectorA(T xyz = 0) noexcept
			: VectorA(xyz, xyz, xyz) {}
		
		constexpr VectorA(T x, T y, T z) noexcept
			: m_x(x), m_y(y), m_z(z) {}
		
		VectorA(const T* v) noexcept
			: VectorA(v[0], v[1], v[2]) {}
		
		constexpr explicit VectorA(const VectorA< T, 2 >& v, T z = 0) noexcept
			: VectorA(v.m_x, v.m_y, z) {}
		
		constexpr VectorA(const VectorA& v) noexcept = default;
		
		constexpr VectorA(VectorA&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit VectorA(const Vector< U, 3 >& v) noexcept
			: VectorA(static_cast< T >(v.m_x), 
					  static_cast< T >(v.m_y), 
					  static_cast< T >(v.m_z)) {}
		
		template< typename U >
		constexpr explicit VectorA(const VectorA< U, 3 >& v) noexcept
			: VectorA(static_cast< T >(v.m_x), 
					  static_cast< T >(v.m_y), 
					  static_cast< T >(v.m_z)) {}
		
		~VectorA() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr VectorA& operator=(const VectorA& v) noexcept = default;
		
		constexpr VectorA& operator=(VectorA&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const T operator[](size_t i) noexcept {
			return GetData()[i];
		}
		
		[[nodiscard]]
		constexpr const T& operator[](size_t i) const noexcept {
			return GetData()[i];
		}

		[[nodiscard]]
		constexpr T* GetData() noexcept {
			return &m_x;
		}
		
		[[nodiscard]]
		constexpr const T* GetData() const noexcept {
			return &m_x;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		T m_x;

		T m_y;

		T m_z;
	};

	template< typename T >
	struct alignas(16) VectorA< T, 4, 
		typename std::enable_if_t< std::is_arithmetic_v< T > > > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		constexpr explicit VectorA(T xyzw = 0) noexcept
			: VectorA(xyzw, xyzw, xyzw, xyzw) {}
		
		constexpr VectorA(T x, T y, T z, T w) noexcept
			: m_x(x), m_y(y), m_z(z), m_w(w) {}
		
		VectorA(const T* v) noexcept
			: VectorA(v[0], v[1], v[2], v[3]) {}
		
		constexpr explicit VectorA(const VectorA< T, 2 >& v, T z = 0, T w = 0) noexcept
			: VectorA(v.m_x, v.m_y, z, w) {}
		
		constexpr explicit VectorA(const VectorA< T, 3 >& v, T w = 0) noexcept
			: VectorA(v.m_x, v.m_y, v.m_z, w) {}
		
		constexpr VectorA(const VectorA& v) noexcept = default;
		
		constexpr VectorA(VectorA&& v) noexcept = default;
		
		template< typename U >
		constexpr explicit VectorA(const Vector< U, 4 >& v) noexcept
			: VectorA(static_cast< T >(v.m_x), 
					  static_cast< T >(v.m_y), 
					  static_cast< T >(v.m_z), 
					  static_cast< T >(v.m_w)) {}
		
		template< typename U >
		constexpr explicit VectorA(const VectorA< U, 4 >& v) noexcept
			: VectorA(static_cast< T >(v.m_x),
					  static_cast< T >(v.m_y),
					  static_cast< T >(v.m_z), 
					  static_cast< T >(v.m_w)) {}
		
		~VectorA() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		constexpr VectorA& operator=(const VectorA& v) noexcept = default;
		
		constexpr VectorA& operator=(VectorA&& v) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr const T operator[](size_t i) noexcept {
			return GetData()[i];
		}
		
		[[nodiscard]]
		constexpr const T& operator[](size_t i) const noexcept {
			return GetData()[i];
		}

		[[nodiscard]]
		constexpr T* GetData() noexcept {
			return &m_x;
		}
		
		[[nodiscard]]
		constexpr const T* GetData() const noexcept {
			return &m_x;
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
	// Floating Point Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 32-bit floating point vector type.
	 */
	using F32x2 = Vector< F32, 2 >;

	/**
	 A 3x1 32-bit floating point vector type.
	 */
	using F32x3 = Vector< F32, 3 >;

	/**
	 A 4x1 32-bit floating point vector type.
	 */
	using F32x4 = Vector< F32, 4 >;

	/**
	 A 2x1 32-bit floating point aligned vector type.
	 */
	using F32x2A = VectorA< F32, 2 >;

	/**
	 A 3x1 32-bit floating point aligned vector type.
	 */
	using F32x3A = VectorA< F32, 3 >;

	/**
	 A 4x1 32-bit floating point aligned vector type.
	 */
	using F32x4A = VectorA< F32, 4 >;

	static_assert(8  == sizeof(F32x2));
	static_assert(12 == sizeof(F32x3));
	static_assert(16 == sizeof(F32x4));

	static_assert(16 == sizeof(F32x2A));
	static_assert(16 == sizeof(F32x3A));
	static_assert(16 == sizeof(F32x4A));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Signed Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A 2x1 signed 32-bit integer vector type.
	 */
	using S32x2 = Vector< S32, 2 >;

	/**
	 A 3x1 signed 32-bit integer vector type.
	 */
	using S32x3 = Vector< S32, 3 >;

	/**
	 A 4x1 signed 32-bit integer vector type.
	 */
	using S32x4 = Vector< S32, 4 >;

	static_assert(8  == sizeof(S32x2));
	static_assert(12 == sizeof(S32x3));
	static_assert(16 == sizeof(S32x4));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Unsigned Integer Vectors
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An 2x1 unsigned 32-bit integer vector type.
	 */
	using U32x2 = Vector< U32, 2 >;

	/**
	 An 3x1 unsigned 32-bit integer vector type.
	 */
	using U32x3 = Vector< U32, 3 >;

	/**
	 An 4x1 unsigned 32-bit integer vector type.
	 */
	using U32x4 = Vector< U32, 4 >;

	static_assert(8  == sizeof(U32x2));
	static_assert(12 == sizeof(U32x3));
	static_assert(16 == sizeof(U32x4));

	#pragma endregion
}