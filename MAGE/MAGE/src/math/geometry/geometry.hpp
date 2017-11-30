#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// UV
	//-------------------------------------------------------------------------
#pragma region

	/**
	 A struct of UV texture coordinates.
	 */
	struct UV final : public F32x2 {

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
						The u texture coordinate.
		 @param[in]		v
						The v texture coordinate.			
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
		constexpr UV(const UV &uv) noexcept = default;
		
		/**
		 Constructs a set of UV texture coordinates by moving the given set of 
		 UV texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						move.
		 */
		constexpr UV(UV &&uv) noexcept = default;
		
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
		constexpr UV &operator=(const UV &uv) = default;
		
		/**
		 Moves the given set of UV texture coordinates to this set of texture 
		 coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						move.
		 @return		A reference to the moved set of UV texture coordinates
						(i.e. this set of UV texture coordinates).
		 */
		constexpr UV &operator=(UV &&uv) = default;
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
	struct Point3 final : public F32x3 {

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
		constexpr Point3(const Point3 &point) noexcept = default;
		
		/**
		 Constructs a point by moving the given point.

		 @param[in]		point
						A reference to the point to move.
		 */
		constexpr Point3(Point3 &&point) noexcept = default;
		
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
		constexpr Point3 &operator=(const Point3 &point) = default;
		
		/**
		 Moves the given point to this point.

		 @param[in]		point
						A reference to the point to move.
		 @return		A reference to the moved point (i.e. this point).
		 */
		constexpr Point3 &operator=(Point3 &&point) = default;
	};

	static_assert(sizeof(Point3) == sizeof(F32x3));

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
	struct Normal3 final : public F32x3 {

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
			: F32x3(x, y, z) {}
		
		/**
		 Constructs a normal from the given normal.

		 @param[in]		normal
						A reference to the normal to copy.
		 */
		constexpr Normal3(const Normal3 &normal) noexcept = default;
		
		/**
		 Constructs a normal by moving the given normal.

		 @param[in]		normal
						A reference to the normal to move.
		 */
		constexpr Normal3(Normal3 &&normal) noexcept = default;
		
		/**
		 Constructs a normal from the given vector.

		 @param[in]		v
						The vector.
		 */
		constexpr explicit Normal3(F32x3 v) noexcept
			: F32x3(std::move(v)) {}

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
		constexpr Normal3 &operator=(const Normal3 &normal) = default;
		
		/**
		 Moves the given normal to this normal.

		 @param[in]		normal
						A reference to the normal to move.
		 @return		A reference to the moved normal (i.e. this normal).
		 */
		constexpr Normal3 &operator=(Normal3 &&normal) = default;
	};

	static_assert(sizeof(Normal3) == sizeof(F32x3));

#pragma endregion

	//-------------------------------------------------------------------------
	// Direction3
	//-------------------------------------------------------------------------
#pragma region

	/**
	 A struct of directions in 3D space.
	 */
	struct Direction3 final : public F32x3 {

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
		constexpr Direction3(const Direction3 &direction) noexcept = default;
		
		/**
		 Constructs a direction by moving the given direction.

		 @param[in]		direction
						A reference to the direction to move.
		 */
		constexpr Direction3(Direction3 &&direction) noexcept = default;
		
		/**
		 Constructs a direction from the given normal.

		 @param[in]		normal
						The normal.
		 */
		constexpr Direction3(Normal3 normal) noexcept
			: F32x3(std::move(normal)) {}

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
		constexpr Direction3 &operator=(const Direction3 &direction) = default;
		
		/**
		 Moves the given direction to this direction.

		 @param[in]		direction
						A reference to the direction to move.
		 @return		A reference to the moved direction (i.e. this direction).
		 */
		constexpr Direction3 &operator=(Direction3 &&direction) = default;
	};

	static_assert(sizeof(Direction3) == sizeof(F32x3));

#pragma endregion

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
	inline const UV InvertHandness(const UV &uv) noexcept {
		return UV(uv.m_x, 1.0f - uv.m_y);
	}
	
	/**
	 Inverts the handness of the given point.

	 @param[in]		point
					A reference to the point.
	 @return		The point with inverted handness.
	 */
	inline const Point3 InvertHandness(const Point3 &point) noexcept {
		return Point3(point.m_x, point.m_y, -point.m_z);
	}
	
	/**
	 Inverts the handness of the given normal.

	 @param[in]		normal
					A reference to the normal.
	 @return		The normal with inverted handness.
	 */
	inline const Normal3 InvertHandness(const Normal3 &normal) noexcept {
		return Normal3(normal.m_x, normal.m_y, -normal.m_z);
	}

	/**
	 Inverts the handness of the given direction.

	 @param[in]		direction
					A reference to the direction.
	 @return		The direction with inverted handness.
	 */
	inline const Direction3 InvertHandness(const Direction3 &direction) noexcept {
		return Direction3(direction.m_x, direction.m_y, -direction.m_z);
	}

#pragma endregion
}