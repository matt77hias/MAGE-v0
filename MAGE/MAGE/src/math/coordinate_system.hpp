#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of Cartesian axes systems.
	 */
	__declspec(align(16)) struct CartesianAxesSystem final : public AlignedData< CartesianAxesSystem > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a Cartesian axes system.
		 */
		CartesianAxesSystem()
			: m_x(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)), m_y(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)), m_z(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)) {}
		
		/**
		 Constructs a Cartesian axes system from the given axes.

		 @pre			The given axis is normalized.
		 @param[in]		x
						The x-axis.
		 */
		explicit CartesianAxesSystem(const XMVECTOR &x) 
			: m_x(x) {
			XMFLOAT3 w;
			XMStoreFloat3(&w, m_x);
			const XMVECTOR u = (fabs(w.x) > 0.1f) ? XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) : XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
			m_y = XMVector3Cross(m_x, u);
			m_z = XMVector3Cross(m_x, m_y);
		}

		/**
		 Constructs a Cartesian axes system from the given axes.

		 @pre			The given axes are orthonormal.
		 @param[in]		x
						The x-axis.
		 @param[in]		y
						The y-axis.
		 */
		explicit CartesianAxesSystem(const XMVECTOR &x, const XMVECTOR &y) 
			: m_x(x), m_y(y), m_z(XMVector3Cross(x, y)) {}

		/**
		 Constructs a Cartesian axes system from the given axes.

		 @pre			The given axes are orthonormal.
		 @param[in]		x
						The x-axis.
		 @param[in]		y
						The y-axis.
		 @param[in]		z
						The z-axis.
		 */
		explicit CartesianAxesSystem(const XMVECTOR &x, const XMVECTOR &y, const XMVECTOR &z) 
			: m_x(x), m_y(y), m_z(z) {}

		/**
		 Constructs a Cartesian axes system from the given Cartesian axes system.

		 @param[in]		axes
						The Cartesian axes system.
		 */
		CartesianAxesSystem(const CartesianAxesSystem &axes) = default;

		/**
		 Constructs a Cartesian axes system from the given Cartesian axes system.

		 @param[in]		axes
						The Cartesian axes system.
		 */
		CartesianAxesSystem(CartesianAxesSystem &&axes) = default;

		/**
		 Destructs this Cartesian axes system.
		 */
		~CartesianAxesSystem() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given Cartesian axes system to this Cartesian axes system.

		 @param[in]		axes
						The Cartesian axes system to copy from.
		 @return		A reference to the copy of the given Cartesian axes system
						(i.e. this Cartesian axes system).
		 */
		CartesianAxesSystem &operator=(const CartesianAxesSystem &axes) = default;

		/**
		 Copies the given Cartesian axes system to this Cartesian axes system.

		 @param[in]		axes
						The Cartesian axes system to copy from.
		 @return		A reference to the copy of the given Cartesian axes system
						(i.e. this Cartesian axes system).
		 */
		CartesianAxesSystem &operator=(CartesianAxesSystem &&axes) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the x-axis of this Cartesian axes system.

		 @return		The x-axis of this Cartesian axes system.
		 */
		const XMVECTOR GetAxisX() const {
			return m_x;
		}

		/**
		 Returns the y-axis of this Cartesian axes system.

		 @return		The y-axis of this Cartesian axes system.
		 */
		const XMVECTOR GetAxisY() const {
			return m_y;
		}

		/**
		 Returns the z-axis of this Cartesian axes system.

		 @return		The z-axis of this Cartesian axes system.
		 */
		const XMVECTOR GetAxisZ() const {
			return m_z;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The x-axis of this Cartesian axes system.
		 */
		XMVECTOR m_x;

		/**
		 The y-axis of this Cartesian axes system.
		 */
		XMVECTOR m_y;

		/**
		 The z-axis of this Cartesian axes system.
		 */
		XMVECTOR m_z;
	};

	/**
	 A struct of Cartesian coordinate systems.
	 */
	_declspec(align(16)) struct CartesianCoordinateSystem final : public AlignedData< CartesianCoordinateSystem > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a Cartesian coordinate system from the given Cartesian axes system.

		 @param[in]		axes
						The Cartesian axes system.
		 */
		explicit CartesianCoordinateSystem(const CartesianAxesSystem &axes)
			: m_o(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)), m_axes(axes) {}

		/**
		 Constructs a Cartesian coordinate system from the given origin and Cartesian axes system.

		 @param[in]		o
						The origin.
		 @param[in]		axes
						The Cartesian axes system.
		 */
		explicit CartesianCoordinateSystem(const XMVECTOR &o, const CartesianAxesSystem &axes)
			: m_o(o), m_axes(axes) {}

		/**
		 Constructs a Cartesian coordinate system from the given Cartesian coordinate system.

		 @param[in]		coordinate_system
						The Cartesian coordinate system.
		 */
		CartesianCoordinateSystem(const CartesianCoordinateSystem &coordinate_system) = default;

		/**
		 Constructs a Cartesian coordinate system from the given Cartesian coordinate system.

		 @param[in]		coordinate_system
						The Cartesian coordinate system.
		 */
		CartesianCoordinateSystem(CartesianCoordinateSystem &&coordinate_system) = default;

		/**
		 Destructs this Cartesian coordinate system.
		 */
		~CartesianCoordinateSystem() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given Cartesian coordinate system to this Cartesian coordinate system.

		 @param[in]		coordinate_system
						The Cartesian coordinate system to copy from.
		 @return		A reference to the copy of the given Cartesian coordinate system
						(i.e. this Cartesian coordinate system).
		 */
		CartesianCoordinateSystem &operator=(const CartesianCoordinateSystem &coordinate_system) = default;

		/**
		 Copies the given Cartesian coordinate system to this Cartesian coordinate system.

		 @param[in]		coordinate_system
						The Cartesian coordinate system to copy from.
		 @return		A reference to the copy of the given Cartesian coordinate system
						(i.e. this Cartesian coordinate system).
		 */
		CartesianCoordinateSystem &operator=(CartesianCoordinateSystem &&coordinate_system) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the origin of this Cartesian coordinate system.

		 @return		The origin of this Cartesian coordinate system.
		 */
		const XMVECTOR GetOrigin() const {
			return m_o;
		}

		/**
		 Returns the x-axis of this Cartesian coordinate system.

		 @return		The x-axis of this Cartesian coordinate system.
		 */
		const XMVECTOR GetAxisX() const {
			return m_axes.GetAxisX();
		}

		/**
		 Returns the y-axis of this Cartesian coordinate system.

		 @return		The y-axis of this Cartesian coordinate system.
		 */
		const XMVECTOR GetAxisY() const {
			return m_axes.GetAxisY();
		}

		/**
		 Returns the z-axis of this Cartesian coordinate system.

		 @return		The z-axis of this Cartesian coordinate system.
		 */
		const XMVECTOR GetAxisZ() const {
			return m_axes.GetAxisZ();
		}
		
		/**
		 Returns the axes of this Cartesian coordinate system.

		 @return		The Cartesian axes system of this Cartesian coordinate system.
		 */
		const CartesianAxesSystem GetAxes() const {
			return m_axes;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The origin of this Cartesian coordinate system.
		 */
		XMVECTOR m_o;

		/**
		 The Cartesian axes system of this Cartesian coordinate system.
		 */
		CartesianAxesSystem m_axes;
	};
}
