#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct CartesianAxesSystem final {

	public:

		CartesianAxesSystem()
			: m_x(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)), m_y(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), m_z(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)) {}
		CartesianAxesSystem(const XMVECTOR &x) 
			: m_x(x) {
			XMFLOAT3 w;
			XMStoreFloat3(&w, m_x);
			const XMVECTOR u = (abs(w.x) > 0.1f) ? XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) : XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
			m_y = XMVector3Cross(m_x, u);
			m_z = XMVector3Cross(m_x, m_y);
		}
		CartesianAxesSystem(const XMVECTOR &x, const XMVECTOR &y) 
			: m_x(x), m_y(y), m_z(XMVector3Cross(x, y)) {}
		CartesianAxesSystem(const XMVECTOR &x, const XMVECTOR &y, const XMVECTOR &z) 
			: m_x(x), m_y(y), m_z(z) {}
		CartesianAxesSystem(const CartesianAxesSystem &axes) 
			: m_x(axes.m_x), m_y(axes.m_y), m_z(axes.m_z) {}
		~CartesianAxesSystem() {}

		CartesianAxesSystem &operator=(const CartesianAxesSystem &axes) {
			m_x = axes.m_x;
			m_y = axes.m_y;
			m_z = axes.m_z;
			return (*this);
		}

		XMVECTOR GetAxisX() const {
			return m_x;
		}
		XMVECTOR GetAxisY() const {
			return m_y;
		}
		XMVECTOR GetAxisZ() const {
			return m_z;
		}

	private:

		XMVECTOR m_x;
		XMVECTOR m_y;
		XMVECTOR m_z;
	};

	struct CartesianCoordinateSystem final {

	public:

		CartesianCoordinateSystem(const CartesianAxesSystem &axes)
			: m_o(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)), m_axes(axes) {}
		CartesianCoordinateSystem(const XMVECTOR &o, const CartesianAxesSystem &axes)
			: m_o(o), m_axes(axes) {}
		CartesianCoordinateSystem(const CartesianCoordinateSystem &coordinate_system)
			: m_o(coordinate_system.m_o), m_axes(coordinate_system.m_axes) {}
		~CartesianCoordinateSystem() {}

		CartesianCoordinateSystem &operator=(const CartesianCoordinateSystem &coordinate_system) {
			m_o    = coordinate_system.m_o;
			m_axes = coordinate_system.m_axes;
			return (*this);
		}

		XMVECTOR GetOrigin() const {
			return m_o;
		}
		XMVECTOR GetAxisX() const {
			return m_axes.GetAxisX();
		}
		XMVECTOR GetAxisY() const {
			return m_axes.GetAxisY();
		}
		XMVECTOR GetAxisZ() const {
			return m_axes.GetAxisZ();
		}
		CartesianAxesSystem GetAxes() const {
			return m_axes;
		}

	private:

		XMVECTOR m_o;
		CartesianAxesSystem m_axes;
	};
}
