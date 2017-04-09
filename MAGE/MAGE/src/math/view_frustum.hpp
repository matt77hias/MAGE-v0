#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\bounding_volume.hpp"
#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ViewFrustum final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------
		
		//http://www.txutxi.com/?p=444
		explicit ViewFrustum(const Camera &camera);
		ViewFrustum(const ViewFrustum &view_frustum) = default;
		ViewFrustum(ViewFrustum &&view_frustum) = default;
		~ViewFrustum() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ViewFrustum &operator=(const ViewFrustum &view_frustum) = default;
		ViewFrustum &operator=(ViewFrustum &&view_frustum) = default;
		
		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool Encloses(const Point3 &point) const;
		//http://www.txutxi.com/?p=584
		bool Overlaps(const Transform &transform, const BS &bs) const;
		bool Overlaps(const Transform &transform, const AABB &aabb) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		XMFLOAT4 m_planes[6];
	};
}