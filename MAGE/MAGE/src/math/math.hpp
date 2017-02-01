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

	inline ostream &operator<<(ostream& os, const XMFLOAT3 &v) {
		os << '[' << v.x << ' ' << v.y << ' ' << v.z << ']';
		return os;
	}

	inline ostream &operator<<(ostream& os, const XMFLOAT4 &v) {
		os << '[' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ']';
		return os;
	}
}