#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations
	struct CartesianAxesSystem;
	CartesianAxesSystem ConstructCartesianAxesSystem(const XMVECTOR &x);

	struct CartesianAxesSystem final {

	public:

		CartesianAxesSystem()
			: x(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)), y(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), z(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)) {}
		CartesianAxesSystem(const XMVECTOR &x) 
			: CartesianAxesSystem(ConstructCartesianAxesSystem(x)) {}
		CartesianAxesSystem(const XMVECTOR &x, const XMVECTOR &y) 
			: x(x), y(y), z(XMVector3Cross(x, y)) {}
		CartesianAxesSystem(const XMVECTOR &x, const XMVECTOR &y, const XMVECTOR &z) 
			: x(x), y(y), z(z) {}
		CartesianAxesSystem(const CartesianAxesSystem &axes) 
			: x(axes.x), y(axes.y), z(axes.z) {}
		~CartesianAxesSystem() {}

		const XMVECTOR x;
		const XMVECTOR y;
		const XMVECTOR z;
	};

	inline CartesianAxesSystem ConstructCartesianAxesSystem(const XMVECTOR &x) {
		XMFLOAT3 w;
		XMStoreFloat3(&w, x);
		const XMVECTOR u = (abs(w.x) > 0.1f) ? XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) : XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		const XMVECTOR y = XMVector3Cross(x, u);
		const XMVECTOR z = XMVector3Cross(x, y);
		return CartesianAxesSystem(x, y, z);
	}

	struct CartesianCoordinateSystem final {

	public:

		CartesianCoordinateSystem(const CartesianAxesSystem &axes)
			: o(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)), axes(axes) {}
		CartesianCoordinateSystem(const XMVECTOR &o, const CartesianAxesSystem &axes)
			: o(o), axes(axes) {}
		CartesianCoordinateSystem(const CartesianCoordinateSystem &coordinate_system)
			: o(coordinate_system.o), axes(coordinate_system.axes) {}
		~CartesianCoordinateSystem() {}

		const XMVECTOR o;
		const CartesianAxesSystem axes;
	};
}
