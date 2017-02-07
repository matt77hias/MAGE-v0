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
	// XMFLOAT2
	//-------------------------------------------------------------------------

	struct UV final : public XMFLOAT2 {

	public:

		UV()
			: XMFLOAT2() {}
		UV(float x, float y)
			: XMFLOAT2(x, y) {}
		UV(const UV &uv)
			: XMFLOAT2(static_cast< const XMFLOAT2 & >(uv)) {}
		explicit UV(const XMFLOAT2 &vector)
			: XMFLOAT2(vector) {}

		~UV() = default;

		UV &operator=(const UV &uv) {
			XMFLOAT2::operator=(uv);
			return (*this);
		}
	};

	static_assert(sizeof(UV) == sizeof(XMFLOAT2), "UV/XMFLOAT2 mismatch");

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

	struct Point3 final : public XMFLOAT3 {

	public:

		Point3()
			: XMFLOAT3() {}
		Point3(float x, float y, float z) 
			: XMFLOAT3(x, y, z) {}
		Point3(const Point3 &point)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(point)) {}
		explicit Point3(const Direction3 &direction);
		explicit Point3(const Normal3 &normal);
		explicit Point3(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}

		~Point3() = default;

		Point3 &operator=(const Point3 &point) {
			XMFLOAT3::operator=(point);
			return (*this);
		}
	};

	struct Direction3 final : public XMFLOAT3 {

	public:

		Direction3()
			: XMFLOAT3() {}
		Direction3(float x, float y, float z)
			: XMFLOAT3(x, y, z) {}
		Direction3(const Direction3 &direction)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(direction)) {}
		explicit Direction3(const Point3 &point)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(point)) {}
		Direction3(const Normal3 &normal);
		explicit Direction3(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}

		~Direction3() = default;

		Direction3 &operator=(const Direction3 &direction) {
			XMFLOAT3::operator=(direction);
			return (*this);
		}
	};

	struct Normal3 final : public XMFLOAT3 {

	public:

		Normal3()
			: XMFLOAT3() {}
		Normal3(float x, float y, float z)
			: XMFLOAT3(x, y, z) {}
		Normal3(const Normal3 &normal)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(normal)) {}
		explicit Normal3(const Point3 &point)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(point)) {}
		explicit Normal3(const Direction3 &direction)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(direction)) {}
		explicit Normal3(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}

		~Normal3() = default;

		Normal3 &operator=(const Normal3 &normal) {
			XMFLOAT3::operator=(normal);
			return (*this);
		}
	};

	inline Point3::Point3(const Direction3 &direction)
		: XMFLOAT3(static_cast< const XMFLOAT3 & >(direction)) {}
	
	inline Point3::Point3(const Normal3 &normal)
		: XMFLOAT3(static_cast< const XMFLOAT3 & >(normal)) {}
	
	inline Direction3::Direction3(const Normal3 &normal)
		: XMFLOAT3(static_cast< const XMFLOAT3 & >(normal)) {}

	static_assert(sizeof(Point3) == sizeof(XMFLOAT3), "Point3/XMFLOAT3 mismatch");
	static_assert(sizeof(Direction3) == sizeof(XMFLOAT3), "Direction3/XMFLOAT3 mismatch");
	static_assert(sizeof(Normal3) == sizeof(XMFLOAT3), "Normal3/XMFLOAT3 mismatch");

	inline ostream &operator<<(ostream& os, const XMFLOAT3 &v) {
		os << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
		return os;
	}

	//-------------------------------------------------------------------------
	// XMFLOAT4
	//-------------------------------------------------------------------------

	struct Color final : public XMFLOAT4 {

	public:

		Color()
			: XMFLOAT4() {}
		Color(float x, float y, float z, float w)
			: XMFLOAT4(x, y, z, w) {}
		Color(const Color &color)
			: XMFLOAT4(static_cast< const XMFLOAT4 & >(color)) {}
		explicit Color(const XMFLOAT4 &vector)
			: XMFLOAT4(vector) {}
		
		~Color() = default;

		Color &operator=(const Color &color) {
			XMFLOAT4::operator=(color);
			return (*this);
		}
	};

	static_assert(sizeof(Color) == sizeof(XMFLOAT4), "Color/XMFLOAT4 mismatch");

	inline ostream &operator<<(ostream& os, const XMFLOAT4 &v) {
		os << '[' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ']';
		return os;
	}
}