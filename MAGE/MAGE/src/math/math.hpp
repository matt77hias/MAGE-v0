#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <directxmath.h>
namespace mage {
	using namespace DirectX;
}

#include <iostream>
namespace mage {
	using std::ostream;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// XMFLOAT2: UV
	//-------------------------------------------------------------------------

	/**
	 A struct of UV texture coordinates.
	 */
	struct UV final : public XMFLOAT2 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a set of UV texture coordinates.
		 */
		UV()
			: UV(0.0f, 0.0f) {}
		
		/**
		 Constructs a set of UV texture coordinates.

		 @param[in]		u
						The u texture coordinate.
		 @param[in]		v
						The v texture coordinate.			
		 */
		UV(float u, float v)
			: XMFLOAT2(u, v) {}
		
		/**
		 Constructs a set of UV texture coordinates from
		 the given set of UV texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to copy.
		 */
		UV(const UV &uv)
			: XMFLOAT2(static_cast< const XMFLOAT2 & >(uv)) {}
		
		/**
		 Constructs a set of UV texture coordinates by moving
		 the given set of UV texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to move.
		 */
		UV(UV &&uv)
			: XMFLOAT2(static_cast< XMFLOAT2 && >(uv)) {}
		
		/**
		 Constructs a set of UV texture coordinates from the given vector.

		 @param[in]		v
						A reference to the vector to copy.
		 */
		explicit UV(const XMFLOAT2 &v)
			: XMFLOAT2(v) {}

		/**
		 Constructs a set of UV texture coordinates by moving the given vector.
		 
		 @param[in]		v
						A reference to the vector to move.
		 */
		explicit UV(XMFLOAT2 &&v)
			: XMFLOAT2(v) {}

		/**
		 Destructs this set of UV texture coordinates.
		 */
		~UV() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given set of UV texture coordinates to
		 this set of texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to copy.
		 @return		A reference to the copy of the given set of UV texture coordinates
						(i.e. this set of UV texture coordinates).
		 */
		UV &operator=(const UV &uv) {
			XMFLOAT2::operator=(uv);
			return (*this);
		}
		
		/**
		 Moves the given set of UV texture coordinates to
		 this set of texture coordinates.

		 @param[in]		uv
						A reference to the set of UV texture coordinates to move.
		 @return		A reference to the moved set of UV texture coordinates
						(i.e. this set of UV texture coordinates).
		 */
		UV &operator=(UV &&uv) {
			XMFLOAT2::operator=(uv);
			return (*this);
		}
	};

	static_assert(sizeof(UV) == sizeof(XMFLOAT2), "UV/XMFLOAT2 mismatch");

	/**
	 Outputs the given vector to the given output stream.

	 @param[in]		os
					A reference to the output stream.
	 @param[in]		v
					A reference to the vector.
	 @return		A reference to the given output stream.
	 */
	inline ostream &operator<<(ostream& os, const XMFLOAT2 &v) {
		os << '[' << v.x << ' ' << v.y << ']';
		return os;
	}

	//-------------------------------------------------------------------------
	// XMFLOAT3
	//-------------------------------------------------------------------------

	// Forward declarations
	struct Direction3;
	struct Normal3;

	//-------------------------------------------------------------------------
	// XMFLOAT3: Point3
	//-------------------------------------------------------------------------

	/**
	 A struct of points in 3D space.
	 */
	struct Point3 final : public XMFLOAT3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a point.
		 */
		Point3()
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
		Point3(float x, float y, float z) 
			: XMFLOAT3(x, y, z) {}
		
		/**
		 Constructs a point from the given point.

		 @param[in]		point
						A reference to the point to copy.
		 */
		Point3(const Point3 &point)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(point)) {}
		
		/**
		 Constructs a point by moving the given point.

		 @param[in]		point
						A reference to the point to move.
		 */
		Point3(Point3 &&point)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(point)) {}
		
		/**
		 Constructs a point from the given vector.

		 @param[in]		v
						A reference to the vector to copy.
		 */
		explicit Point3(const XMFLOAT3 &v)
			: XMFLOAT3(v) {}

		/**
		 Constructs a point by moving the given vector.

		 @param[in]		v
						A reference to the vector to move.
		 */
		explicit Point3(XMFLOAT3 &&v)
			: XMFLOAT3(v) {}

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
		 @return		A reference to the copy of the given point
						(i.e. this point).
		 */
		Point3 &operator=(const Point3 &point) {
			XMFLOAT3::operator=(point);
			return (*this);
		}
		
		/**
		 Moves the given point to this point.

		 @param[in]		point
						A reference to the point to move.
		 @return		A reference to the moved point
						(i.e. this point).
		 */
		Point3 &operator=(Point3 &&point) {
			XMFLOAT3::operator=(point);
			return (*this);
		}
	};

	static_assert(sizeof(Point3) == sizeof(XMFLOAT3), "Point3/XMFLOAT3 mismatch");

	//-------------------------------------------------------------------------
	// XMFLOAT3: Direction3
	//-------------------------------------------------------------------------

	/**
	 A struct of directions in 3D space.
	 */
	struct Direction3 final : public XMFLOAT3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a direction.
		 */
		Direction3()
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
		Direction3(float x, float y, float z)
			: XMFLOAT3(x, y, z) {}
		
		/**
		 Constructs a direction from the given direction.

		 @param[in]		direction
						A reference to the direction to copy.
		 */
		Direction3(const Direction3 &direction)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(direction)) {}
		
		/**
		 Constructs a direction by moving the given direction.

		 @param[in]		direction
						A reference to the direction to move.
		 */
		Direction3(Direction3 &&direction)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(direction)) {}
		
		/**
		 Constructs a direction from the given normal.

		 @param[in]		normal
						A reference to the normal to copy.
		 */
		Direction3(const Normal3 &normal);

		/**
		 Constructs a direction by moving the given normal.

		 @param[in]		normal
						A reference to the normal to move.
		 */
		Direction3(Normal3 &&normal);

		/**
		 Constructs a direction from the given vector.

		 @param[in]		v
						A reference to the vector to copy.
		 */
		explicit Direction3(const XMFLOAT3 &v)
			: XMFLOAT3(v) {}

		/**
		 Constructs a direction by moving the given vector.

		 @param[in]		v
						A reference to the vector to move.
		 */
		explicit Direction3(XMFLOAT3 &&v)
			: XMFLOAT3(v) {}

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
		 @return		A reference to the copy of the given direction
						(i.e. this direction).
		 */
		Direction3 &operator=(const Direction3 &direction) {
			XMFLOAT3::operator=(direction);
			return (*this);
		}
		
		/**
		 Moves the given direction to this direction.

		 @param[in]		direction
						A reference to the direction to move.
		 @return		A reference to the moved direction
						(i.e. this direction).
		 */
		Direction3 &operator=(Direction3 &&direction) {
			XMFLOAT3::operator=(direction);
			return (*this);
		}
	};

	static_assert(sizeof(Direction3) == sizeof(XMFLOAT3), "Direction3/XMFLOAT3 mismatch");

	//-------------------------------------------------------------------------
	// XMFLOAT3: Normal3
	//-------------------------------------------------------------------------

	/**
	 A struct of normals in 3D space.

	 @note			@c Normal3 does not guarantee or force normalized directions.
					This should be guaranteed and enforced by the user.
	 */
	struct Normal3 final : public XMFLOAT3 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a normal.
		 */
		Normal3()
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
		Normal3(float x, float y, float z)
			: XMFLOAT3(x, y, z) {}
		
		/**
		 Constructs a normal from the given normal.

		 @param[in]		normal
						A reference to the normal to copy.
		 */
		Normal3(const Normal3 &normal)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(normal)) {}
		
		/**
		 Constructs a normal by moving the given normal.

		 @param[in]		normal
						A reference to the normal to move.
		 */
		Normal3(Normal3 &&normal)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(normal)) {}
		
		/**
		 Constructs a normal from the given direction.

		 @param[in]		direction
						A reference to the direction to copy.
		 */
		explicit Normal3(const Direction3 &direction)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(direction)) {}

		/**
		 Constructs a normal by moving the given direction.

		 @param[in]		direction
						A reference to the direction to move.
		 */
		explicit Normal3(Direction3 &&direction)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(direction)) {}
		
		/**
		 Constructs a normal from the given vector.

		 @param[in]		v
						A reference to the vector to copy.
		 */
		explicit Normal3(const XMFLOAT3 &v)
			: XMFLOAT3(v) {}

		/**
		 Constructs a normal by moving the given vector.

		 @param[in]		v
						A reference to the vector to move.
		 */
		explicit Normal3(XMFLOAT3 &&v)
			: XMFLOAT3(v) {}

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
		 @return		A reference to the copy of the given normal
						(i.e. this normal).
		 */
		Normal3 &operator=(const Normal3 &normal) {
			XMFLOAT3::operator=(normal);
			return (*this);
		}
		
		/**
		 Moves the given normal to this normal.

		 @param[in]		normal
						A reference to the normal to move.
		 @return		A reference to the moved normal
						(i.e. this normal).
		 */
		Normal3 &operator=(Normal3 &&normal) {
			XMFLOAT3::operator=(normal);
			return (*this);
		}
	};

	static_assert(sizeof(Normal3) == sizeof(XMFLOAT3), "Normal3/XMFLOAT3 mismatch");

	inline Direction3::Direction3(const Normal3 &normal)
		: XMFLOAT3(static_cast< const XMFLOAT3 & >(normal)) {}
	
	inline Direction3::Direction3(Normal3 &&normal)
		: XMFLOAT3(static_cast< XMFLOAT3 && >(normal)) {}

	/**
	 Outputs the given vector to the given output stream.

	 @param[in]		os
					A reference to the output stream.
	 @param[in]		v
					A reference to the vector.
	 @return		A reference to the given output stream.
	 */
	inline ostream &operator<<(ostream& os, const XMFLOAT3 &v) {
		os << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
		return os;
	}

	//-------------------------------------------------------------------------
	// XMFLOAT4: Color
	//-------------------------------------------------------------------------

	/**
	 A struct of colors.
	 */
	struct Color final : public XMFLOAT4 {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a color.
		 */
		Color()
			: Color(0.0f, 0.0f, 0.0f, 0.0f) {}
		
		/**
		 Constructs a color from the given components.

		 @param[in]		x
						The first component.
		 @param[in]		y
						The second component.
		 @param[in]		z
						The third component.
		 @param[in]		w
						The fourth component.
		 */
		Color(float x, float y, float z, float w)
			: XMFLOAT4(x, y, z, w) {}
		
		/**
		 Constructs a color from the given color.

		 @param[in]		color
						A reference to the color to copy.
		 */
		Color(const Color &color)
			: XMFLOAT4(static_cast< const XMFLOAT4 & >(color)) {}
		
		/**
		 Constructs a color by moving the given color.

		 @param[in]		color
						A reference to the color to move.
		 */
		Color(Color &&color)
			: XMFLOAT4(static_cast< XMFLOAT4 && >(color)) {}
		
		/**
		 Constructs a color from the given vector.

		 @param[in]		v
						A reference to the vector to copy.
		 */
		explicit Color(const XMFLOAT4 &v)
			: XMFLOAT4(v) {}
		
		/**
		 Constructs a color by moving the given vector.

		 @param[in]		v
						A reference to the vector to move.
		 */
		explicit Color(XMFLOAT4 &&v)
			: XMFLOAT4(v) {}
		
		/**
		 Destructs this color.
		 */
		~Color() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given color to this color.

		 @param[in]		color
						A reference to the color to copy.
		 @return		A reference to the copy of the given color
						(i.e. this color).
		 */
		Color &operator=(const Color &color) {
			XMFLOAT4::operator=(color);
			return (*this);
		}
		
		/**
		 Moves the given color to this color.

		 @param[in]		color
						A reference to the color to move.
		 @return		A reference to the moved color
						(i.e. this color).
		 */
		Color &operator=(Color &&color) {
			XMFLOAT4::operator=(color);
			return (*this);
		}
	};

	static_assert(sizeof(Color) == sizeof(XMFLOAT4), "Color/XMFLOAT4 mismatch");

	/**
	 Outputs the given vector to the given output stream.

	 @param[in]		os
					A reference to the output stream.
	 @param[in]		v
					A reference to the vector.
	 @return		A reference to the given output stream.
	 */
	inline ostream &operator<<(ostream& os, const XMFLOAT4 &v) {
		os << '[' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ']';
		return os;
	}

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
	 Inverts the handness of the given direction.

	 @param[in]		direction
					A reference to the direction.
	 @return		The direction with inverted handness.
	 */
	inline const Direction3 InvertHandness(const Direction3 &direction) noexcept {
		return Direction3(direction.x, direction.y, -direction.z);
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
}