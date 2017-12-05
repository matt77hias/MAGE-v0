//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\geometry\view_frustum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ViewFrustum::ViewFrustum(CXMMATRIX transform) noexcept {
		const XMMATRIX C = XMMatrixTranspose(transform);

		// Extract the view frustum planes from the given transform.
		// All view frustum planes are inward facing: 0 <= n . p + d

		// p' = (x',y',z',w') = (x,y,z,1) T = p T

		//   -w' <= x'
		// <=> 0 <= w' + x'
		// <=> 0 <= p . c3 + p . c0
		// <=> 0 <= p . (c3 + c0)
		m_left_plane = C.r[3] + C.r[0];
		
		//    x' <= w'
		// <=> 0 <= w' - x'
		// <=> 0 <= p . c3 - p . c0
		// <=> 0 <= p . (c3 - c0)
		m_right_plane = C.r[3] - C.r[0];
		
		//   -w' <= y'
		// <=> 0 <= w' + y'
		// <=> 0 <= p . c3 + p . c1
		// <=> 0 <= p . (c3 + c1)
		m_bottom_plane = C.r[3] + C.r[1];
		
		//    y' <= w'
		// <=> 0 <= w' - y'
		// <=> 0 <= p . c3 - p . c1
		// <=> 0 <= p . (c3 - c1)
		m_top_plane = C.r[3] - C.r[1];
		
		//     0 <= z'
		// <=> 0 <= p . c2
		m_near_plane = C.r[2];

		//    z' <= w'
		// <=> 0 <= w' - z'
		// <=> 0 <= p . c3 - p . c2
		// <=> 0 <= p . (c3 - c2)
		m_far_plane = C.r[3] - C.r[2];

		// Normalize the view frustum planes.
		for (size_t i = 0; i < 6; ++i) {
			m_planes[i] = XMPlaneNormalize(m_planes[i]);
		}
	}

	//-------------------------------------------------------------------------
	// ViewFrustum: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	bool XM_CALLCONV ViewFrustum::Encloses(FXMVECTOR point) const noexcept {
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], point);
			if (XMVectorGetX(result) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool XM_CALLCONV ViewFrustum::EnclosesStrict(FXMVECTOR point) const noexcept {
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], point);
			if (XMVectorGetX(result) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::Encloses(const AABB &aabb) const noexcept {
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR p = aabb.MinPointAlongNormal(m_planes[i]);
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::EnclosesStrict(const AABB &aabb) const noexcept {
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR p = aabb.MinPointAlongNormal(m_planes[i]);
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::Encloses(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 radius = bs.Radius();
		
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) < radius) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::EnclosesStrict(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 radius = bs.Radius();

		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) <= radius) {
				return false;
			}
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// ViewFrustum: Overlapping = Partial | Full Coverage
	//-------------------------------------------------------------------------

	bool ViewFrustum::Overlaps(const AABB &aabb) const noexcept {
		// Test for no coverage.
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR p = aabb.MaxPointAlongNormal(m_planes[i]);
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::OverlapsStrict(const AABB &aabb) const noexcept {
		// Test for no coverage.
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR p = aabb.MaxPointAlongNormal(m_planes[i]);
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::Overlaps(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 radius = bs.Radius();
		
		// Test for no coverage.
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) < -radius) {
				return false;
			}
		}

		return true;
	}

	bool ViewFrustum::OverlapsStrict(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 radius = bs.Radius();
		
		// Test for no coverage.
		for (size_t i = 0; i < 6; ++i) {
			const XMVECTOR result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) <= -radius) {
				return false;
			}
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// Member Methods: Operators
	//-------------------------------------------------------------------------

	bool ViewFrustum::operator==(const ViewFrustum &view_frustum) const noexcept {
		if (XMVector4NotEqual(m_left_plane,   view_frustum.m_left_plane)) {
			return false;
		}
		if (XMVector4NotEqual(m_right_plane,  view_frustum.m_right_plane)) {
			return false;
		}
		if (XMVector4NotEqual(m_bottom_plane, view_frustum.m_bottom_plane)) {
			return false;
		}
		if (XMVector4NotEqual(m_top_plane,    view_frustum.m_top_plane)) {
			return false;
		}
		if (XMVector4NotEqual(m_near_plane,   view_frustum.m_near_plane)) {
			return false;
		}
		if (XMVector4NotEqual(m_far_plane,    view_frustum.m_far_plane)) {
			return false;
		}

		return false;
	}
}