//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "geometry\bounding_volume.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box
	//-------------------------------------------------------------------------

	AABB::AABB(const BoundingSphere& sphere) noexcept {
		const auto centroid = sphere.Centroid();
		const auto r        = sphere.Radius();
		const auto radius   = XMVectorSet(r, r, r, 0.0f);
		m_min = centroid - radius;
		m_max = centroid + radius;
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	[[nodiscard]]
	bool AABB::Encloses(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto r        = sphere.Radius();
		const auto radius   = XMVectorSet(r, r, r, 0.0f);

		if (XMVector3Less(m_max - centroid, radius)) {
			return false;
		}
		if (XMVector3Less(centroid - m_min, radius)) {
			return false;
		}

		return true;
	}

	[[nodiscard]]
	bool AABB::EnclosesStrict(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto r        = sphere.Radius();
		const auto radius   = XMVectorSet(r, r, r, 0.0f);

		if (XMVector3LessOrEqual(m_max - centroid, radius)) {
			return false;
		}
		if (XMVector3LessOrEqual(centroid - m_min, radius)) {
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Overlapping = Partial | Full Coverage
	//-------------------------------------------------------------------------

	[[nodiscard]]
	bool AABB::Overlaps(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto r        = -sphere.Radius();
		const auto radius   = XMVectorSet(r, r, r, 0.0f);

		// Test for no coverage.
		if (XMVector3Less(m_max - centroid, radius)) {
			return false;
		}
		if (XMVector3Less(centroid - m_min, radius)) {
			return false;
		}

		return true;
	}

	[[nodiscard]]
	bool AABB::OverlapsStrict(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto r        = -sphere.Radius();
		const auto radius   = XMVectorSet(r, r, r, 0.0f);

		// Test for no coverage.
		if (XMVector3LessOrEqual(m_max - centroid, radius)) {
			return false;
		}
		if (XMVector3LessOrEqual(centroid - m_min, radius)) {
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------

	BoundingSphere::BoundingSphere(const AABB& aabb) noexcept {
		const auto centroid = aabb.Centroid();
		const auto radius   = aabb.Radius();
		const auto r        = std::max(XMVectorGetX(radius),
			                  std::max(XMVectorGetY(radius), 
						               XMVectorGetZ(radius)));
		m_pr = XMVectorSetW(centroid, r);
	}

	//-------------------------------------------------------------------------
	// Bounding Sphere: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	[[nodiscard]]
	bool BoundingSphere::Encloses(const AABB& aabb) const noexcept {
		const auto pmin = aabb.MinPoint();
		const auto pmax = aabb.MaxPoint();
		
		if (!Encloses(XMVectorPermute(pmin, pmax, 0, 1, 2, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 0, 1, 6, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 0, 5, 2, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 0, 5, 6, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 4, 1, 2, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 4, 1, 6, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 4, 5, 2, 3))) {
			return false;
		}
		if (!Encloses(XMVectorPermute(pmin, pmax, 4, 5, 6, 3))) {
			return false;
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingSphere::EnclosesStrict(const AABB& aabb) const noexcept {
		const auto pmin = aabb.MinPoint();
		const auto pmax = aabb.MaxPoint();

		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 0, 1, 2, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 0, 1, 6, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 0, 5, 2, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 0, 5, 6, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 4, 1, 2, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 4, 1, 6, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 4, 5, 2, 3))) {
			return false;
		}
		if (!EnclosesStrict(XMVectorPermute(pmin, pmax, 4, 5, 6, 3))) {
			return false;
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingSphere::Encloses(const BoundingSphere& sphere) const noexcept {
		const auto p      = sphere.Centroid();
		const auto radius = sphere.Radius();

		if (!Encloses(p - XMVectorSet(radius, 0.0f, 0.0f, 0.0f))) {
			return false;
		}
		if (!Encloses(p + XMVectorSet(radius, 0.0f, 0.0f, 0.0f))) {
			return false;
		}
		if (!Encloses(p - XMVectorSet(0.0f, radius, 0.0f, 0.0f))) {
			return false;
		}
		if (!Encloses(p + XMVectorSet(0.0f, radius, 0.0f, 0.0f))) {
			return false;
		}
		if (!Encloses(p - XMVectorSet(0.0f, 0.0f, radius, 0.0f))) {
			return false;
		}
		if (!Encloses(p + XMVectorSet(0.0f, 0.0f, radius, 0.0f))) {
			return false;
		}
		
		return true;
	}

	[[nodiscard]]
	bool BoundingSphere::EnclosesStrict(const BoundingSphere& sphere) const noexcept {
		const auto p      = sphere.Centroid();
		const auto radius = sphere.Radius();

		if (!EnclosesStrict(p - XMVectorSet(radius, 0.0f, 0.0f, 0.0f))) {
			return false;
		}
		if (!EnclosesStrict(p + XMVectorSet(radius, 0.0f, 0.0f, 0.0f))) {
			return false;
		}
		if (!EnclosesStrict(p - XMVectorSet(0.0f, radius, 0.0f, 0.0f))) {
			return false;
		}
		if (!EnclosesStrict(p + XMVectorSet(0.0f, radius, 0.0f, 0.0f))) {
			return false;
		}
		if (!EnclosesStrict(p - XMVectorSet(0.0f, 0.0f, radius, 0.0f))) {
			return false;
		}
		if (!EnclosesStrict(p + XMVectorSet(0.0f, 0.0f, radius, 0.0f))) {
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// Bounding Frustum
	//-------------------------------------------------------------------------

	BoundingFrustum::BoundingFrustum(CXMMATRIX transform) noexcept {
		const auto C = XMMatrixTranspose(transform);

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
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			m_planes[i] = XMPlaneNormalize(m_planes[i]);
		}
	}

	//-------------------------------------------------------------------------
	// BoundingFrustum: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	[[nodiscard]]bool XM_CALLCONV 
		BoundingFrustum::Encloses(FXMVECTOR point) const noexcept {

		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto result = XMPlaneDotCoord(m_planes[i], point);
			if (XMVectorGetX(result) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]bool XM_CALLCONV 
		BoundingFrustum::EnclosesStrict(FXMVECTOR point) const noexcept {
		
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto result = XMPlaneDotCoord(m_planes[i], point);
			if (XMVectorGetX(result) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::Encloses(const AABB& aabb) const noexcept {
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto p      = aabb.MinPointAlongNormal(m_planes[i]);
			const auto result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::EnclosesStrict(const AABB& aabb) const noexcept {
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto p      = aabb.MinPointAlongNormal(m_planes[i]);
			const auto result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::Encloses(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto radius   = sphere.Radius();
		
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) < radius) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::EnclosesStrict(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto radius   = sphere.Radius();

		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) <= radius) {
				return false;
			}
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// BoundingFrustum: Overlapping = Partial | Full Coverage
	//-------------------------------------------------------------------------

	[[nodiscard]]
	bool BoundingFrustum::Overlaps(const AABB& aabb) const noexcept {
		// Test for no coverage.
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto p      = aabb.MaxPointAlongNormal(m_planes[i]);
			const auto result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::OverlapsStrict(const AABB& aabb) const noexcept {
		// Test for no coverage.
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto p      = aabb.MaxPointAlongNormal(m_planes[i]);
			const auto result = XMPlaneDotCoord(m_planes[i], p);
			if (XMVectorGetX(result) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::Overlaps(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto radius   = sphere.Radius();
		
		// Test for no coverage.
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) < -radius) {
				return false;
			}
		}

		return true;
	}

	[[nodiscard]]
	bool BoundingFrustum::OverlapsStrict(const BoundingSphere& sphere) const noexcept {
		const auto centroid = sphere.Centroid();
		const auto radius   = sphere.Radius();
		
		// Test for no coverage.
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			const auto result = XMPlaneDotCoord(m_planes[i], centroid);
			if (XMVectorGetX(result) <= -radius) {
				return false;
			}
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// BoundingFrustum: Operators
	//-------------------------------------------------------------------------

	[[nodiscard]]
	bool BoundingFrustum::operator==(const BoundingFrustum& frustum) const noexcept {
		for (size_t i = 0; i < std::size(m_planes); ++i) {
			if (XMVector4NotEqual(m_planes[i], frustum.m_planes[i])) {
				return false;
			}
		}
		
		return false;
	}
}