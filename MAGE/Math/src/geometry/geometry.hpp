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
	// UV
	//-------------------------------------------------------------------------
	#pragma region

	#ifdef UV
		#error Illegal symbol definition.
	#endif

	/**
	 A struct of UV texture coordinates.
	 */
	struct UV : public F32x2 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a set of UV texture coordinates.
		 */
		constexpr UV() noexcept = default;
		
		/**
		 Constructs a set of UV texture coordinates.

		 @param[in]		u
						The U component.
		 @param[in]		v
						The V component.			
		 */
		constexpr UV(F32 u, F32 v) noexcept
			: F32x2(u, v) {}
		
		/**
		 Constructs a set of UV texture coordinates from the given set of UV 
		 texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						copy.
		 */
		constexpr UV(const UV& uv) noexcept = default;
		
		/**
		 Constructs a set of UV texture coordinates by moving the given set of 
		 UV texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						move.
		 */
		constexpr UV(UV&& uv) noexcept = default;
		
		/**
		 Constructs a set of UV texture coordinates from the given vector.

		 @param[in]		v
						The vector.
		 */
		constexpr explicit UV(F32x2 v) noexcept
			: F32x2(std::move(v)) {}

		/**
		 Destructs this set of UV texture coordinates.
		 */
		~UV() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given set of UV texture coordinates to this set of texture 
		 coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						copy.
		 @return		A reference to the copy of the given set of UV texture 
						coordinates (i.e. this set of UV texture coordinates).
		 */
		UV& operator=(const UV& uv) noexcept = default;
		
		/**
		 Moves the given set of UV texture coordinates to this set of texture 
		 coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						move.
		 @return		A reference to the moved set of UV texture coordinates
						(i.e. this set of UV texture coordinates).
		 */
		UV& operator=(UV&& uv) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the U component of this set of UV texture coordinates.

		 @return		The U component of this set of UV texture coordinates.
		 */
		[[nodiscard]]
		constexpr F32 GetU() const noexcept {
			return operator[](0);
		}

		/**
		 Sets the U component of this set of UV texture coordinates to the 
		 given value.

		 @param[in]		u
						The U component.
		 */
		constexpr void SetU(F32 u) noexcept {
			operator[](0) = u;
		}

		/**
		 Returns the V component of this set of UV texture coordinates.

		 @return		The V component of this set of UV texture 
						coordinates.
		 */
		[[nodiscard]]
		constexpr F32 GetV() const noexcept {
			return operator[](1);
		}

		/**
		 Sets the V component of this set of UV texture coordinates to the 
		 given value.

		 @param[in]		v
						The V component.
		 */
		constexpr void SetV(F32 v) noexcept {
			operator[](1) = v;
		}
	};

	static_assert(sizeof(UV) == sizeof(F32x2));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Point3
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of points in 3D space.
	 */
	struct Point3 : public F32x3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a point.
		 */
		constexpr Point3() noexcept = default;
		
		/**
		 Constructs a point from the given coordinates.

		 @param[in]		x
						The x-coordinate.
		 @param[in]		y
						The y-coordinate.
		 @param[in]		z
						The z-coordinate.
		 */
		constexpr Point3(F32 x, F32 y, F32 z) noexcept
			: F32x3(x, y, z) {}
		
		/**
		 Constructs a point from the given point.

		 @param[in]		point
						A reference to the point to copy.
		 */
		constexpr Point3(const Point3& point) noexcept = default;
		
		/**
		 Constructs a point by moving the given point.

		 @param[in]		point
						A reference to the point to move.
		 */
		constexpr Point3(Point3&& point) noexcept = default;
		
		/**
		 Constructs a point from the given vector.

		 @param[in]		v
						The vector.
		 */
		constexpr explicit Point3(F32x3 v) noexcept
			: F32x3(std::move(v)) {}

		/**
		 Constructs a point.
		 */
		~Point3() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given point to this point.

		 @param[in]		point
						A reference to the point to copy.
		 @return		A reference to the copy of the given point (i.e. this 
						point).
		 */
		Point3& operator=(const Point3& point) noexcept = default;
		
		/**
		 Moves the given point to this point.

		 @param[in]		point
						A reference to the point to move.
		 @return		A reference to the moved point (i.e. this point).
		 */
		Point3& operator=(Point3&& point) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------	

		/**
		 Returns the X component of this point.

		 @return		The X component of this point.
		 */
		[[nodiscard]]
		constexpr F32 GetX() const noexcept {
			return operator[](0);
		}

		/**
		 Sets the X component of this point to the given value.

		 @param[in]		x
						The X component.
		 */
		constexpr void SetX(F32 x) noexcept {
			operator[](0) = x;
		}

		/**
		 Returns the Y component of this point.

		 @return		The Y component of this point.
		 */
		[[nodiscard]]
		constexpr F32 GetY() const noexcept {
			return operator[](1);
		}

		/**
		 Sets the Y component of this point to the given value.

		 @param[in]		y
						The Y component.
		 */
		constexpr void SetY(F32 y) noexcept {
			operator[](1) = y;
		}

		/**
		 Returns the Z component of this point.

		 @return		The Z component of this point.
		 */
		[[nodiscard]]
		constexpr F32 GetZ() const noexcept {
			return operator[](2);
		}
	
		/**
		 Sets the Z component of this point to the given value.

		 @param[in]		z
						The Z component.
		 */
		constexpr void SetZ(F32 z) noexcept {
			operator[](2) = z;
		}
	};

	static_assert(sizeof(Point3) == sizeof(F32x3));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Direction3
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of directions in 3D space.
	 */
	struct Direction3 : public F32x3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a direction.
		 */
		constexpr Direction3() noexcept = default;
		
		/**
		 Constructs a direction from the given coordinates.

		 @param[in]		x
						The x-coordinate.
		 @param[in]		y
						The y-coordinate.
		 @param[in]		z
						The z-coordinate.
		 */
		constexpr Direction3(F32 x, F32 y, F32 z) noexcept
			: F32x3(x, y, z) {}
		
		/**
		 Constructs a direction from the given direction.

		 @param[in]		direction
						A reference to the direction to copy.
		 */
		constexpr Direction3(const Direction3& direction) noexcept = default;
		
		/**
		 Constructs a direction by moving the given direction.

		 @param[in]		direction
						A reference to the direction to move.
		 */
		constexpr Direction3(Direction3&& direction) noexcept = default;
		
		/**
		 Constructs a direction from the given vector.

		 @param[in]		v
						The vector.
		 */
		constexpr explicit Direction3(F32x3 v) noexcept
			: F32x3(std::move(v)) {}

		/**
		 Constructs a direction.
		 */
		~Direction3() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given direction to this direction.

		 @param[in]		direction
						A reference to the direction to copy.
		 @return		A reference to the copy of the given direction (i.e. 
						this direction).
		 */
		Direction3& operator=(const Direction3& direction) noexcept = default;
		
		/**
		 Moves the given direction to this direction.

		 @param[in]		direction
						A reference to the direction to move.
		 @return		A reference to the moved direction (i.e. this direction).
		 */
		Direction3& operator=(Direction3&& direction) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------	

		/**
		 Returns the X component of this direction.

		 @return		The X component of this direction.
		 */
		[[nodiscard]]
		constexpr F32 GetX() const noexcept {
			return operator[](0);
		}

		/**
		 Sets the X component of this direction to the given value.

		 @param[in]		x
						The X component.
		 */
		constexpr void SetX(F32 x) noexcept {
			operator[](0) = x;
		}

		/**
		 Returns the Y component of this direction.

		 @return		The Y component of this direction.
		 */
		[[nodiscard]]
		constexpr F32 GetY() const noexcept {
			return operator[](1);
		}

		/**
		 Sets the Y component of this direction to the given value.

		 @param[in]		y
						The Y component.
		 */
		constexpr void SetY(F32 y) noexcept {
			operator[](1) = y;
		}

		/**
		 Returns the Z component of this direction.

		 @return		The Z component of this direction.
		 */
		[[nodiscard]]
		constexpr F32 GetZ() const noexcept {
			return operator[](2);
		}
	
		/**
		 Sets the Z component of this direction to the given value.

		 @param[in]		z
						The Z component.
		 */
		constexpr void SetZ(F32 z) noexcept {
			operator[](2) = z;
		}
	};

	static_assert(sizeof(Direction3) == sizeof(F32x3));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Normal3
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of normals in 3D space.

	 @note			@c Normal3 does not guarantee or force normalized 
					directions. This should be guaranteed and enforced by the 
					user.
	 */
	struct Normal3 : public Direction3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a normal.
		 */
		constexpr Normal3() noexcept = default;
		
		/**
		 Constructs a normal from the given coordinates.

		 @param[in]		x
						The x-coordinate.
		 @param[in]		y
						The y-coordinate.
		 @param[in]		z
						The z-coordinate.
		 */
		constexpr Normal3(F32 x, F32 y, F32 z) noexcept
			: Direction3(x, y, z) {}
		
		/**
		 Constructs a normal from the given normal.

		 @param[in]		normal
						A reference to the normal to copy.
		 */
		constexpr Normal3(const Normal3& normal) noexcept = default;
		
		/**
		 Constructs a normal by moving the given normal.

		 @param[in]		normal
						A reference to the normal to move.
		 */
		constexpr Normal3(Normal3&& normal) noexcept = default;
		
		/**
		 Constructs a normal from the given vector.

		 @param[in]		v
						The vector.
		 */
		constexpr explicit Normal3(F32x3 v) noexcept
			: Direction3(std::move(v)) {}

		/**
		 Destructs this normal.
		 */
		~Normal3() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given normal to this normal.

		 @param[in]		normal
						A reference to the normal to copy.
		 @return		A reference to the copy of the given normal (i.e. this 
						normal).
		 */
		constexpr Normal3& operator=(const Normal3& normal) noexcept = default;
		
		/**
		 Moves the given normal to this normal.

		 @param[in]		normal
						A reference to the normal to move.
		 @return		A reference to the moved normal (i.e. this normal).
		 */
		constexpr Normal3& operator=(Normal3&& normal) noexcept = default;
	};

	static_assert(sizeof(Normal3) == sizeof(F32x3));

	#pragma endregion
}

namespace std {

	//-------------------------------------------------------------------------
	// UV
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	struct tuple_size< mage::UV > 
		: public integral_constant< size_t, mage::UV::s_size > {};

	template< size_t I >
	struct tuple_element< I, mage::UV > {

	public:

		using type = typename mage::UV::value_type;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Point3
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	struct tuple_size< mage::Point3 >
		: public integral_constant< size_t, mage::Point3::s_size > {};

	template< size_t I >
	struct tuple_element< I, mage::Point3 > {

	public:

		using type = typename mage::Point3::value_type;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Direction3
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	struct tuple_size< mage::Direction3 >
		: public integral_constant< size_t, mage::Direction3::s_size > {};

	template< size_t I >
	struct tuple_element< I, mage::Direction3 > {

	public:

		using type = typename mage::Direction3::value_type;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Normal3
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	struct tuple_size< mage::Normal3 >
		: public integral_constant< size_t, mage::Normal3::s_size > {};

	template< size_t I >
	struct tuple_element< I, mage::Normal3 > {

	public:

		using type = typename mage::Normal3::value_type;
	};

	#pragma endregion
}

namespace mage {

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Inverts the handness of the given set of UV texture coordinates.

	 @param[in]		uv
					A reference to the set of UV texture coordinates.
	 @return		The set of UV texture coordinates with inverted handness.
	 */
	[[nodiscard]]
	constexpr const UV InvertHandness(const UV& uv) noexcept {
		const auto [u, v] = uv;
		return { u, 1.0f - v };
	}
	
	/**
	 Inverts the handness of the given point.

	 @param[in]		point
					A reference to the point.
	 @return		The point with inverted handness.
	 */
	[[nodiscard]]
	constexpr const Point3 InvertHandness(const Point3& point) noexcept {
		const auto [x, y, z] = point;
		return { x, y, -z };
	}
	
	/**
	 Inverts the handness of the given normal.

	 @param[in]		normal
					A reference to the normal.
	 @return		The normal with inverted handness.
	 */
	[[nodiscard]]
	constexpr const Normal3 InvertHandness(const Normal3& normal) noexcept {
		const auto [x, y, z] = normal;
		return { x, y, -z };
	}

	/**
	 Inverts the handness of the given direction.

	 @param[in]		direction
					A reference to the direction.
	 @return		The direction with inverted handness.
	 */
	[[nodiscard]]
	constexpr const Direction3 InvertHandness(const Direction3& direction) noexcept {
		const auto [x, y, z] = direction;
		return { x, y, -z };
	}

	#pragma endregion
}