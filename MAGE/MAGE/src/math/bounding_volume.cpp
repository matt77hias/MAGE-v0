//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\bounding_volume.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box
	//-------------------------------------------------------------------------

	AABB::AABB(const BS &bs)
		: m_p_min(Point3(bs.m_p.x - bs.m_r, bs.m_p.y - bs.m_r, bs.m_p.z - bs.m_r)),
		m_p_max(Point3(bs.m_p.x + bs.m_r, bs.m_p.y + bs.m_r, bs.m_p.z + bs.m_r)) {}

	bool AABB::Encloses(const Point3 &point) const noexcept {
		if (point.x > m_p_max.x) {
			return false;
		}
		if (point.y > m_p_max.y) {
			return false;
		}
		if (point.z > m_p_max.z) {
			return false;
		}
		if (point.x < m_p_min.x) {
			return false;
		}
		if (point.y < m_p_min.y) {
			return false;
		}
		if (point.z < m_p_min.z) {
			return false;
		}

		return true;
	}

	bool AABB::EnclosesStrict(const Point3 &point) const noexcept {
		if (point.x >= m_p_max.x) {
			return false;
		}
		if (point.y >= m_p_max.y) {
			return false;
		}
		if (point.z >= m_p_max.z) {
			return false;
		}
		if (point.x <= m_p_min.x) {
			return false;
		}
		if (point.y <= m_p_min.y) {
			return false;
		}
		if (point.z <= m_p_min.z) {
			return false;
		}

		return true;
	}

	bool AABB::Encloses(const AABB &aabb) const noexcept {
		if (!Encloses(aabb.m_p_min)) {
			return false;
		}
		if (!Encloses(aabb.m_p_max)) {
			return false;
		}

		return true;
	}

	bool AABB::EnclosesStrict(const AABB &aabb) const noexcept {
		if (!EnclosesStrict(aabb.m_p_min)) {
			return false;
		}
		if (!EnclosesStrict(aabb.m_p_max)) {
			return false;
		}

		return true;
	}

	bool AABB::Encloses(const BS &bs) const noexcept {
		const AABB aabb(bs);
		return Encloses(aabb);
	}

	bool AABB::EnclosesStrict(const BS &bs) const noexcept {
		const AABB aabb(bs);
		return EnclosesStrict(aabb);
	}

	bool AABB::EnclosedBy(const XMFLOAT4 *planes, size_t nb_planes) const noexcept {
		Assert(planes);
		
		const XMVECTOR corner_000 = XMVectorSet(m_p_min.x, m_p_min.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_001 = XMVectorSet(m_p_min.x, m_p_min.y, m_p_max.z, 1.0f);
		const XMVECTOR corner_010 = XMVectorSet(m_p_min.x, m_p_max.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_011 = XMVectorSet(m_p_min.x, m_p_max.y, m_p_max.z, 1.0f);
		const XMVECTOR corner_100 = XMVectorSet(m_p_max.x, m_p_min.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_101 = XMVectorSet(m_p_max.x, m_p_min.y, m_p_max.z, 1.0f);
		const XMVECTOR corner_110 = XMVectorSet(m_p_max.x, m_p_max.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_111 = XMVectorSet(m_p_max.x, m_p_max.y, m_p_max.z, 1.0f);
		
		for (size_t i  = 0; i < nb_planes; ++i) {
			const XMVECTOR plane = XMLoadFloat4(&planes[i]);

			// 000
			const XMVECTOR result_000 = XMPlaneDotCoord(plane, corner_000);
			if (XMVectorGetX(result_000) < 0.0f) {
				return false;
			}

			// 001
			const XMVECTOR result_001 = XMPlaneDotCoord(plane, corner_001);
			if (XMVectorGetX(result_001) < 0.0f) {
				return false;
			}

			// 010
			const XMVECTOR result_010 = XMPlaneDotCoord(plane, corner_010);
			if (XMVectorGetX(result_010) < 0.0f) {
				return false;
			}

			// 011
			const XMVECTOR result_011 = XMPlaneDotCoord(plane, corner_011);
			if (XMVectorGetX(result_011) < 0.0f) {
				return false;
			}

			// 100
			const XMVECTOR result_100 = XMPlaneDotCoord(plane, corner_100);
			if (XMVectorGetX(result_100) < 0.0f) {
				return false;
			}

			// 101
			const XMVECTOR result_101 = XMPlaneDotCoord(plane, corner_101);
			if (XMVectorGetX(result_101) < 0.0f) {
				return false;
			}

			// 110
			const XMVECTOR result_110 = XMPlaneDotCoord(plane, corner_110);
			if (XMVectorGetX(result_110) < 0.0f) {
				return false;
			}

			// 111
			const XMVECTOR result_111 = XMPlaneDotCoord(plane, corner_111);
			if (XMVectorGetX(result_111) < 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool AABB::EnclosedStrictBy(const XMFLOAT4 *planes, size_t nb_planes) const noexcept {
		Assert(planes);

		const XMVECTOR corner_000 = XMVectorSet(m_p_min.x, m_p_min.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_001 = XMVectorSet(m_p_min.x, m_p_min.y, m_p_max.z, 1.0f);
		const XMVECTOR corner_010 = XMVectorSet(m_p_min.x, m_p_max.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_011 = XMVectorSet(m_p_min.x, m_p_max.y, m_p_max.z, 1.0f);
		const XMVECTOR corner_100 = XMVectorSet(m_p_max.x, m_p_min.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_101 = XMVectorSet(m_p_max.x, m_p_min.y, m_p_max.z, 1.0f);
		const XMVECTOR corner_110 = XMVectorSet(m_p_max.x, m_p_max.y, m_p_min.z, 1.0f);
		const XMVECTOR corner_111 = XMVectorSet(m_p_max.x, m_p_max.y, m_p_max.z, 1.0f);

		for (size_t i = 0; i < nb_planes; ++i) {
			const XMVECTOR plane = XMLoadFloat4(&planes[i]);

			// 000
			const XMVECTOR result_000 = XMPlaneDotCoord(plane, corner_000);
			if (XMVectorGetX(result_000) <= 0.0f) {
				return false;
			}

			// 001
			const XMVECTOR result_001 = XMPlaneDotCoord(plane, corner_001);
			if (XMVectorGetX(result_001) <= 0.0f) {
				return false;
			}

			// 010
			const XMVECTOR result_010 = XMPlaneDotCoord(plane, corner_010);
			if (XMVectorGetX(result_010) <= 0.0f) {
				return false;
			}

			// 011
			const XMVECTOR result_011 = XMPlaneDotCoord(plane, corner_011);
			if (XMVectorGetX(result_011) <= 0.0f) {
				return false;
			}

			// 100
			const XMVECTOR result_100 = XMPlaneDotCoord(plane, corner_100);
			if (XMVectorGetX(result_100) <= 0.0f) {
				return false;
			}

			// 101
			const XMVECTOR result_101 = XMPlaneDotCoord(plane, corner_101);
			if (XMVectorGetX(result_101) <= 0.0f) {
				return false;
			}

			// 110
			const XMVECTOR result_110 = XMPlaneDotCoord(plane, corner_110);
			if (XMVectorGetX(result_110) <= 0.0f) {
				return false;
			}

			// 111
			const XMVECTOR result_111 = XMPlaneDotCoord(plane, corner_111);
			if (XMVectorGetX(result_111) <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool AABB::Overlaps(const AABB &aabb) const noexcept {
		if (aabb.m_p_min.x > m_p_max.x) {
			return false;
		}
		if (aabb.m_p_min.y > m_p_max.y) {
			return false;
		}
		if (aabb.m_p_min.z > m_p_max.z) {
			return false;
		}
		if (aabb.m_p_max.x < m_p_min.x) {
			return false;
		}
		if (aabb.m_p_max.y < m_p_min.y) {
			return false;
		}
		if (aabb.m_p_max.z < m_p_min.z) {
			return false;
		}

		return true;
	}

	bool AABB::OverlapsStrict(const AABB &aabb) const noexcept {
		if (aabb.m_p_min.x >= m_p_max.x) {
			return false;
		}
		if (aabb.m_p_min.y >= m_p_max.y) {
			return false;
		}
		if (aabb.m_p_min.z >= m_p_max.z) {
			return false;
		}
		if (aabb.m_p_max.x <= m_p_min.x) {
			return false;
		}
		if (aabb.m_p_max.y <= m_p_min.y) {
			return false;
		}
		if (aabb.m_p_max.z <= m_p_min.z) {
			return false;
		}

		return true;
	}

	const Point3 AABB::Centroid() const noexcept {
		const XMVECTOR p_min = XMLoadFloat3(&m_p_min);
		const XMVECTOR p_max = XMLoadFloat3(&m_p_max);
		const XMVECTOR centroid = 0.5f * (p_min + p_max);
		Point3 c;
		XMStoreFloat3(&c, centroid);
		return c;
	}

	const Direction3 AABB::Diagonal() const noexcept {
		const XMVECTOR p_min = XMLoadFloat3(&m_p_min);
		const XMVECTOR p_max = XMLoadFloat3(&m_p_max);
		const XMVECTOR diagonal = p_max - p_min;
		Direction3 d;
		XMStoreFloat3(&d, diagonal);
		return d;
	}

	const AABB Union(const AABB &aabb, const Point3 &point) noexcept {
		const XMVECTOR p_min1 = XMLoadFloat3(&aabb.m_p_min);
		const XMVECTOR p_max1 = XMLoadFloat3(&aabb.m_p_max);
		const XMVECTOR p2     = XMLoadFloat3(&point);
		const XMVECTOR p_min  = XMVectorMin(p_min1, p2);
		const XMVECTOR p_max  = XMVectorMax(p_max1, p2);
		Point3 pmin, pmax;
		XMStoreFloat3(&pmin, p_min);
		XMStoreFloat3(&pmax, p_max);
		return AABB(pmin, pmax);
	}

	const AABB Union(const AABB &aabb1, const AABB &aabb2) noexcept {
		const XMVECTOR p_min1 = XMLoadFloat3(&aabb1.m_p_min);
		const XMVECTOR p_max1 = XMLoadFloat3(&aabb1.m_p_max);
		const XMVECTOR p_min2 = XMLoadFloat3(&aabb2.m_p_min);
		const XMVECTOR p_max2 = XMLoadFloat3(&aabb2.m_p_max);
		const XMVECTOR p_min  = XMVectorMin(p_min1, p_min2);
		const XMVECTOR p_max  = XMVectorMax(p_max1, p_max2);
		Point3 pmin, pmax;
		XMStoreFloat3(&pmin, p_min);
		XMStoreFloat3(&pmax, p_max);
		return AABB(pmin, pmax);
	}

	const AABB Overlap(const AABB &aabb1, const AABB &aabb2) noexcept {
		if (!aabb1.Overlaps(aabb2)) {
			return AABB();
		}

		const XMVECTOR p_min1 = XMLoadFloat3(&aabb1.m_p_min);
		const XMVECTOR p_max1 = XMLoadFloat3(&aabb1.m_p_max);
		const XMVECTOR p_min2 = XMLoadFloat3(&aabb2.m_p_min);
		const XMVECTOR p_max2 = XMLoadFloat3(&aabb2.m_p_max);
		const XMVECTOR p_min  = XMVectorMax(p_min1, p_min2);
		const XMVECTOR p_max  = XMVectorMin(p_max1, p_max2);
		Point3 pmin, pmax;
		XMStoreFloat3(&pmin, p_min);
		XMStoreFloat3(&pmax, p_max);
		return AABB(pmin, pmax);
	}

	const AABB OverlapStrict(const AABB &aabb1, const AABB &aabb2) noexcept {
		if (!aabb1.OverlapsStrict(aabb2)) {
			return AABB();
		}

		const XMVECTOR p_min1 = XMLoadFloat3(&aabb1.m_p_min);
		const XMVECTOR p_max1 = XMLoadFloat3(&aabb1.m_p_max);
		const XMVECTOR p_min2 = XMLoadFloat3(&aabb2.m_p_min);
		const XMVECTOR p_max2 = XMLoadFloat3(&aabb2.m_p_max);
		const XMVECTOR p_min  = XMVectorMax(p_min1, p_min2);
		const XMVECTOR p_max  = XMVectorMin(p_max1, p_max2);
		Point3 pmin, pmax;
		XMStoreFloat3(&pmin, p_min);
		XMStoreFloat3(&pmax, p_max);
		return AABB(pmin, pmax);
	}

	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------

	BS::BS(const AABB &aabb) {
		const XMVECTOR p_min = XMLoadFloat3(&aabb.m_p_min);
		const XMVECTOR p_max = XMLoadFloat3(&aabb.m_p_max);
		const XMVECTOR centroid = 0.5f * (p_min + p_max);
		const XMVECTOR radius   = 0.5f * (p_max - p_min);
		XMStoreFloat3(&m_p, centroid);
		m_r = std::max(XMVectorGetX(radius), std::max(XMVectorGetY(radius), XMVectorGetZ(radius)));
	}

	bool BS::Encloses(const Point3 &point) const noexcept {
		const XMVECTOR p0 = XMLoadFloat3(&m_p);
		const XMVECTOR p1 = XMLoadFloat3(&point);
		const XMVECTOR length = XMVector3Length(p1 - p0);
		return XMVectorGetX(length) <= m_r;
	}
		
	bool BS::EnclosesStrict(const Point3 &point) const noexcept {
		const XMVECTOR p0 = XMLoadFloat3(&m_p);
		const XMVECTOR p1 = XMLoadFloat3(&point);
		const XMVECTOR length = XMVector3Length(p1 - p0);
		return XMVectorGetX(length) < m_r;
	}
		
	bool BS::Encloses(const AABB &aabb) const noexcept {
		if (!Encloses(Point3(aabb.m_p_min.x, aabb.m_p_min.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_min.x, aabb.m_p_min.y, aabb.m_p_max.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_min.x, aabb.m_p_max.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_min.x, aabb.m_p_max.y, aabb.m_p_max.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_max.x, aabb.m_p_min.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_max.x, aabb.m_p_min.y, aabb.m_p_max.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_max.x, aabb.m_p_max.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.m_p_max.x, aabb.m_p_max.y, aabb.m_p_max.z))) {
			return false;
		}
		
		return true;
	}

	bool BS::EnclosesStrict(const AABB &aabb) const noexcept {
		if (!EnclosesStrict(Point3(aabb.m_p_min.x, aabb.m_p_min.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_min.x, aabb.m_p_min.y, aabb.m_p_max.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_min.x, aabb.m_p_max.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_min.x, aabb.m_p_max.y, aabb.m_p_max.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_max.x, aabb.m_p_min.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_max.x, aabb.m_p_min.y, aabb.m_p_max.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_max.x, aabb.m_p_max.y, aabb.m_p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.m_p_max.x, aabb.m_p_max.y, aabb.m_p_max.z))) {
			return false;
		}

		return true;
	}

	bool BS::Encloses(const BS &bs) const noexcept {
		if (!Encloses(Point3(bs.m_p.x - bs.m_r, bs.m_p.y, bs.m_p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.m_p.x + bs.m_r, bs.m_p.y, bs.m_p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.m_p.x, bs.m_p.y - bs.m_r, bs.m_p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.m_p.x, bs.m_p.y + bs.m_r, bs.m_p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.m_p.x, bs.m_p.y, bs.m_p.z - bs.m_r))) {
			return false;
		}
		if (!Encloses(Point3(bs.m_p.x, bs.m_p.y, bs.m_p.z + bs.m_r))) {
			return false;
		}

		return true;
	}

	bool BS::EnclosesStrict(const BS &bs) const noexcept {
		if (!EnclosesStrict(Point3(bs.m_p.x - bs.m_r, bs.m_p.y, bs.m_p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.m_p.x + bs.m_r, bs.m_p.y, bs.m_p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.m_p.x, bs.m_p.y - bs.m_r, bs.m_p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.m_p.x, bs.m_p.y + bs.m_r, bs.m_p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.m_p.x, bs.m_p.y, bs.m_p.z - bs.m_r))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.m_p.x, bs.m_p.y, bs.m_p.z + bs.m_r))) {
			return false;
		}

		return true;
	}

	bool BS::EnclosedBy(const XMFLOAT4 *planes, size_t nb_planes) const noexcept {
		Assert(planes);
		
		const XMVECTOR p = XMLoadFloat3(&m_p);
		
		for (size_t i = 0; i < nb_planes; ++i) {
			const XMVECTOR plane = XMLoadFloat4(&planes[i]);
			const XMVECTOR result = XMPlaneDotCoord(plane, p);
			if (XMVectorGetX(result) < -m_r) {
				return false;
			}
		}

		return true;
	}

	bool BS::EnclosedStrictBy(const XMFLOAT4 *planes, size_t nb_planes) const noexcept {
		Assert(planes);
		
		const XMVECTOR p = XMLoadFloat3(&m_p);
		
		for (size_t i = 0; i < nb_planes; ++i) {
			const XMVECTOR plane = XMLoadFloat4(&planes[i]);
			const XMVECTOR result = XMPlaneDotCoord(plane, p);
			if (XMVectorGetX(result) <= -m_r) {
				return false;
			}
		}

		return true;
	}

	const BS Union(const BS &bs, const Point3 &point) noexcept {
		const XMVECTOR p0 = XMLoadFloat3(&bs.m_p);
		const XMVECTOR p1 = XMLoadFloat3(&point);
		const XMVECTOR length = XMVector3Length(p1 - p0);
		return BS(bs.m_p, std::max(bs.m_r, XMVectorGetX(length)));
	}
}