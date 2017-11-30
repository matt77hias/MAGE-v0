#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <directxmath.h>
namespace mage {
	using namespace DirectX;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	using F32x2 = XMFLOAT2;
	using F32x3 = XMFLOAT3;
	using F32x4 = XMFLOAT4;
	using F32x2A = XMFLOAT2A;
	using F32x3A = XMFLOAT3A;
	using F32x4A = XMFLOAT4A;

	using S32x2 = XMINT2;
	using S32x3 = XMINT3;
	using S32x4 = XMINT4;

	using U32x2 = XMUINT2;
	using U32x3 = XMUINT3;
	using U32x4 = XMUINT4;

	//-------------------------------------------------------------------------
	// UV
	//-------------------------------------------------------------------------

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
		UV() noexcept
			: UV(0.0f, 0.0f) {}
		
		/**
		 Constructs a set of UV texture coordinates.

		 @param[in]		u
						The u texture coordinate.
		 @param[in]		v
						The v texture coordinate.			
		 */
		UV(F32 u, F32 v) noexcept
			: F32x2(u, v) {}
		
		/**
		 Constructs a set of UV texture coordinates from the given set of UV 
		 texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						copy.
		 */
		UV(const UV &uv) = default;
		
		/**
		 Constructs a set of UV texture coordinates by moving the given set of 
		 UV texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						move.
		 */
		UV(UV &&uv) noexcept = default;
		
		/**
		 Constructs a set of UV texture coordinates from the given vector.

		 @param[in]		v
						The vector.
		 */
		explicit UV(F32x2 v) noexcept
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
		UV &operator=(const UV &uv) = default;
		
		/**
		 Moves the given set of UV texture coordinates to this set of texture 
		 coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to 
						move.
		 @return		A reference to the moved set of UV texture coordinates
						(i.e. this set of UV texture coordinates).
		 */
		UV &operator=(UV &&uv) = default;
	};

	static_assert(sizeof(UV) == sizeof(F32x2), 
		"UV/F32x2 mismatch");

	//-------------------------------------------------------------------------
	// Point3
	//-------------------------------------------------------------------------

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
		Point3() noexcept
			: Point3(0.0f, 0.0f, 0.0f) {}
		
		/**
		 Constructs a point from the given coordinates.

		 @param[in]		x
						The x-coordinate.
		 @param[in]		y
						The y-coordinate.
		 @param[in]		z
						The z-coordinate.
		 */
		Point3(F32 x, F32 y, F32 z) noexcept
			: F32x3(x, y, z) {}
		
		/**
		 Constructs a point from the given point.

		 @param[in]		point
						A reference to the point to copy.
		 */
		Point3(const Point3 &point) noexcept = default;
		
		/**
		 Constructs a point by moving the given point.

		 @param[in]		point
						A reference to the point to move.
		 */
		Point3(Point3 &&point) noexcept = default;
		
		/**
		 Constructs a point from the given vector.

		 @param[in]		v
						The vector.
		 */
		explicit Point3(F32x3 v) noexcept
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
		Point3 &operator=(const Point3 &point) = default;
		
		/**
		 Moves the given point to this point.

		 @param[in]		point
						A reference to the point to move.
		 @return		A reference to the moved point (i.e. this point).
		 */
		Point3 &operator=(Point3 &&point) = default;
	};

	static_assert(sizeof(Point3) == sizeof(F32x3), 
		"Point3/F32x3 mismatch");

	//-------------------------------------------------------------------------
	// Normal3
	//-------------------------------------------------------------------------

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
		Normal3() noexcept
			: Normal3(0.0f, 0.0f, 0.0f) {}
		
		/**
		 Constructs a normal from the given coordinates.

		 @param[in]		x
						The x-coordinate.
		 @param[in]		y
						The y-coordinate.
		 @param[in]		z
						The z-coordinate.
		 */
		Normal3(F32 x, F32 y, F32 z) noexcept
			: F32x3(x, y, z) {}
		
		/**
		 Constructs a normal from the given normal.

		 @param[in]		normal
						A reference to the normal to copy.
		 */
		Normal3(const Normal3 &normal) noexcept = default;
		
		/**
		 Constructs a normal by moving the given normal.

		 @param[in]		normal
						A reference to the normal to move.
		 */
		Normal3(Normal3 &&normal) noexcept = default;
		
		/**
		 Constructs a normal from the given vector.

		 @param[in]		v
						The vector.
		 */
		explicit Normal3(F32x3 v) noexcept
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
		Normal3 &operator=(const Normal3 &normal) = default;
		
		/**
		 Moves the given normal to this normal.

		 @param[in]		normal
						A reference to the normal to move.
		 @return		A reference to the moved normal (i.e. this normal).
		 */
		Normal3 &operator=(Normal3 &&normal) = default;
	};

	static_assert(sizeof(Normal3) == sizeof(F32x3), 
		"Normal3/F32x3 mismatch");

	//-------------------------------------------------------------------------
	// Direction3
	//-------------------------------------------------------------------------

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
		Direction3() noexcept
			: Direction3(0.0f, 0.0f, 0.0f) {}
		
		/**
		 Constructs a direction from the given coordinates.

		 @param[in]		x
						The x-coordinate.
		 @param[in]		y
						The y-coordinate.
		 @param[in]		z
						The z-coordinate.
		 */
		Direction3(F32 x, F32 y, F32 z) noexcept
			: F32x3(x, y, z) {}
		
		/**
		 Constructs a direction from the given direction.

		 @param[in]		direction
						A reference to the direction to copy.
		 */
		Direction3(const Direction3 &direction) noexcept = default;
		
		/**
		 Constructs a direction by moving the given direction.

		 @param[in]		direction
						A reference to the direction to move.
		 */
		Direction3(Direction3 &&direction) noexcept = default;
		
		/**
		 Constructs a direction from the given normal.

		 @param[in]		normal
						The normal.
		 */
		Direction3(Normal3 normal) noexcept
			: F32x3(std::move(normal)) {}

		/**
		 Constructs a direction from the given vector.

		 @param[in]		v
						The vector.
		 */
		explicit Direction3(F32x3 v) noexcept
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
		Direction3 &operator=(const Direction3 &direction) = default;
		
		/**
		 Moves the given direction to this direction.

		 @param[in]		direction
						A reference to the direction to move.
		 @return		A reference to the moved direction (i.e. this direction).
		 */
		Direction3 &operator=(Direction3 &&direction) = default;
	};

	static_assert(sizeof(Direction3) == sizeof(F32x3), 
		"Direction3/F32x3 mismatch");

	//-------------------------------------------------------------------------
	// Utilities
	//-------------------------------------------------------------------------

	/**
	 Inverts the handness of the given set of UV texture coordinates.

	 @param[in]		uv
					A reference to the set of UV texture coordinates.
	 @return		The set of UV texture coordinates with inverted handness.
	 */
	inline const UV InvertHandness(const UV &uv) noexcept {
		return UV(uv.x, 1.0f - uv.y);
	}
	
	/**
	 Inverts the handness of the given point.

	 @param[in]		point
					A reference to the point.
	 @return		The point with inverted handness.
	 */
	inline const Point3 InvertHandness(const Point3 &point) noexcept {
		return Point3(point.x, point.y, -point.z);
	}
	
	/**
	 Inverts the handness of the given normal.

	 @param[in]		normal
					A reference to the normal.
	 @return		The normal with inverted handness.
	 */
	inline const Normal3 InvertHandness(const Normal3 &normal) noexcept {
		return Normal3(normal.x, normal.y, -normal.z);
	}

	/**
	 Inverts the handness of the given direction.

	 @param[in]		direction
					A reference to the direction.
	 @return		The direction with inverted handness.
	 */
	inline const Direction3 InvertHandness(const Direction3 &direction) noexcept {
		return Direction3(direction.x, direction.y, -direction.z);
	}
}