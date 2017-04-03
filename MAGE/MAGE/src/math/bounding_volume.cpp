//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\bounding_volume.hpp"

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
		: p_min(Point3(bs.p.x - bs.r, bs.p.y - bs.r, bs.p.z - bs.r)),
		p_max(Point3(bs.p.x + bs.r, bs.p.y + bs.r, bs.p.z + bs.r)) {}

	bool AABB::Encloses(const Point3 &point) const {
		if (point.x > p_max.x) {
			return false;
		}
		if (point.y > p_max.y) {
			return false;
		}
		if (point.z > p_max.z) {
			return false;
		}
		if (point.x < p_min.x) {
			return false;
		}
		if (point.y < p_min.y) {
			return false;
		}
		if (point.z < p_min.z) {
			return false;
		}

		return true;
	}

	bool AABB::EnclosesStrict(const Point3 &point) const {
		if (point.x >= p_max.x) {
			return false;
		}
		if (point.y >= p_max.y) {
			return false;
		}
		if (point.z >= p_max.z) {
			return false;
		}
		if (point.x <= p_min.x) {
			return false;
		}
		if (point.y <= p_min.y) {
			return false;
		}
		if (point.z <= p_min.z) {
			return false;
		}

		return true;
	}

	bool AABB::Encloses(const AABB &aabb) const {
		if (!Encloses(aabb.p_min)) {
			return false;
		}
		if (!Encloses(aabb.p_max)) {
			return false;
		}

		return true;
	}

	bool AABB::EnclosesStrict(const AABB &aabb) const {
		if (!EnclosesStrict(aabb.p_min)) {
			return false;
		}
		if (!EnclosesStrict(aabb.p_max)) {
			return false;
		}

		return true;
	}

	bool AABB::Encloses(const BS &bs) const {
		const AABB aabb(bs);
		return Encloses(aabb);
	}

	bool AABB::EnclosesStrict(const BS &bs) const {
		const AABB aabb(bs);
		return EnclosesStrict(aabb);
	}

	bool AABB::EnclosedBy(const XMFLOAT4 *planes, size_t nb_planes) const {
		const XMVECTOR corner_000_v = XMVectorSet(p_min.x, p_min.y, p_min.z, 1.0f);
		const XMVECTOR corner_001_v = XMVectorSet(p_min.x, p_min.y, p_max.z, 1.0f);
		const XMVECTOR corner_010_v = XMVectorSet(p_min.x, p_max.y, p_min.z, 1.0f);
		const XMVECTOR corner_011_v = XMVectorSet(p_min.x, p_max.y, p_max.z, 1.0f);
		const XMVECTOR corner_100_v = XMVectorSet(p_max.x, p_min.y, p_min.z, 1.0f);
		const XMVECTOR corner_101_v = XMVectorSet(p_max.x, p_min.y, p_max.z, 1.0f);
		const XMVECTOR corner_110_v = XMVectorSet(p_max.x, p_max.y, p_min.z, 1.0f);
		const XMVECTOR corner_111_v = XMVectorSet(p_max.x, p_max.y, p_max.z, 1.0f);
		
		for (size_t i  = 0; i < nb_planes; ++i) {
			const XMVECTOR plane_v = XMLoadFloat4(&planes[i]);

			// 000
			const XMVECTOR result_000_v = XMPlaneDotCoord(plane_v, corner_000_v);
			float result_000;
			XMStoreFloat(&result_000, result_000_v);
			if (result_000 < 0.0f) {
				return false;
			}

			// 001
			const XMVECTOR result_001_v = XMPlaneDotCoord(plane_v, corner_001_v);
			float result_001;
			XMStoreFloat(&result_001, result_001_v);
			if (result_001 < 0.0f) {
				return false;
			}

			// 010
			const XMVECTOR result_010_v = XMPlaneDotCoord(plane_v, corner_010_v);
			float result_010;
			XMStoreFloat(&result_010, result_010_v);
			if (result_010 < 0.0f) {
				return false;
			}

			// 011
			const XMVECTOR result_011_v = XMPlaneDotCoord(plane_v, corner_011_v);
			float result_011;
			XMStoreFloat(&result_011, result_011_v);
			if (result_011 < 0.0f) {
				return false;
			}

			// 100
			const XMVECTOR result_100_v = XMPlaneDotCoord(plane_v, corner_100_v);
			float result_100;
			XMStoreFloat(&result_100, result_100_v);
			if (result_100 < 0.0f) {
				return false;
			}

			// 101
			const XMVECTOR result_101_v = XMPlaneDotCoord(plane_v, corner_101_v);
			float result_101;
			XMStoreFloat(&result_101, result_101_v);
			if (result_101 < 0.0f) {
				return false;
			}

			// 110
			const XMVECTOR result_110_v = XMPlaneDotCoord(plane_v, corner_110_v);
			float result_110;
			XMStoreFloat(&result_110, result_110_v);
			if (result_110 < 0.0f) {
				return false;
			}

			// 111
			const XMVECTOR result_111_v = XMPlaneDotCoord(plane_v, corner_111_v);
			float result_111;
			XMStoreFloat(&result_111, result_111_v);
			if (result_111 < 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool AABB::EnclosedStrictBy(const XMFLOAT4 *planes, size_t nb_planes) const {
		const XMVECTOR corner_000_v = XMVectorSet(p_min.x, p_min.y, p_min.z, 1.0f);
		const XMVECTOR corner_001_v = XMVectorSet(p_min.x, p_min.y, p_max.z, 1.0f);
		const XMVECTOR corner_010_v = XMVectorSet(p_min.x, p_max.y, p_min.z, 1.0f);
		const XMVECTOR corner_011_v = XMVectorSet(p_min.x, p_max.y, p_max.z, 1.0f);
		const XMVECTOR corner_100_v = XMVectorSet(p_max.x, p_min.y, p_min.z, 1.0f);
		const XMVECTOR corner_101_v = XMVectorSet(p_max.x, p_min.y, p_max.z, 1.0f);
		const XMVECTOR corner_110_v = XMVectorSet(p_max.x, p_max.y, p_min.z, 1.0f);
		const XMVECTOR corner_111_v = XMVectorSet(p_max.x, p_max.y, p_max.z, 1.0f);
		
		for (size_t i = 0; i < nb_planes; ++i) {
			const XMVECTOR plane_v = XMLoadFloat4(&planes[i]);

			// 000
			const XMVECTOR result_000_v = XMPlaneDotCoord(plane_v, corner_000_v);
			float result_000;
			XMStoreFloat(&result_000, result_000_v);
			if (result_000 <= 0.0f) {
				return false;
			}

			// 001
			const XMVECTOR result_001_v = XMPlaneDotCoord(plane_v, corner_001_v);
			float result_001;
			XMStoreFloat(&result_001, result_001_v);
			if (result_001 <= 0.0f) {
				return false;
			}

			// 010
			const XMVECTOR result_010_v = XMPlaneDotCoord(plane_v, corner_010_v);
			float result_010;
			XMStoreFloat(&result_010, result_010_v);
			if (result_010 <= 0.0f) {
				return false;
			}

			// 011
			const XMVECTOR result_011_v = XMPlaneDotCoord(plane_v, corner_011_v);
			float result_011;
			XMStoreFloat(&result_011, result_011_v);
			if (result_011 <= 0.0f) {
				return false;
			}

			// 100
			const XMVECTOR result_100_v = XMPlaneDotCoord(plane_v, corner_100_v);
			float result_100;
			XMStoreFloat(&result_100, result_100_v);
			if (result_100 <= 0.0f) {
				return false;
			}

			// 101
			const XMVECTOR result_101_v = XMPlaneDotCoord(plane_v, corner_101_v);
			float result_101;
			XMStoreFloat(&result_101, result_101_v);
			if (result_101 <= 0.0f) {
				return false;
			}

			// 110
			const XMVECTOR result_110_v = XMPlaneDotCoord(plane_v, corner_110_v);
			float result_110;
			XMStoreFloat(&result_110, result_110_v);
			if (result_110 <= 0.0f) {
				return false;
			}

			// 111
			const XMVECTOR result_111_v = XMPlaneDotCoord(plane_v, corner_111_v);
			float result_111;
			XMStoreFloat(&result_111, result_111_v);
			if (result_111 <= 0.0f) {
				return false;
			}
		}

		return true;
	}

	bool AABB::Overlaps(const AABB &aabb) const {
		if (aabb.p_min.x > p_max.x) {
			return false;
		}
		if (aabb.p_min.y > p_max.y) {
			return false;
		}
		if (aabb.p_min.z > p_max.z) {
			return false;
		}
		if (aabb.p_max.x < p_min.x) {
			return false;
		}
		if (aabb.p_max.y < p_min.y) {
			return false;
		}
		if (aabb.p_max.z < p_min.z) {
			return false;
		}

		return true;
	}

	bool AABB::OverlapsStrict(const AABB &aabb) const {
		if (aabb.p_min.x >= p_max.x) {
			return false;
		}
		if (aabb.p_min.y >= p_max.y) {
			return false;
		}
		if (aabb.p_min.z >= p_max.z) {
			return false;
		}
		if (aabb.p_max.x <= p_min.x) {
			return false;
		}
		if (aabb.p_max.y <= p_min.y) {
			return false;
		}
		if (aabb.p_max.z <= p_min.z) {
			return false;
		}

		return true;
	}

	const Point3 AABB::Centroid() const {
		const XMVECTOR p_min_v = XMLoadFloat3(&p_min);
		const XMVECTOR p_max_v = XMLoadFloat3(&p_max);
		const XMVECTOR centroid_v = 0.5f * (p_min_v + p_max_v);
		Point3 centroid;
		XMStoreFloat3(&centroid, centroid_v);
		return centroid;
	}

	const Direction3 AABB::Diagonal() const {
		const XMVECTOR p_min_v = XMLoadFloat3(&p_min);
		const XMVECTOR p_max_v = XMLoadFloat3(&p_max);
		const XMVECTOR diagonal_v = p_max_v - p_min_v;
		Direction3 diagonal;
		XMStoreFloat3(&diagonal, diagonal_v);
		return diagonal;
	}

	const AABB Union(const AABB &aabb, const Point3 &point) {
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb.p_max);
		const XMVECTOR p_v2 = XMLoadFloat3(&point);
		const XMVECTOR p_min_v = XMVectorMin(p_min_v1, p_v2);
		const XMVECTOR p_max_v = XMVectorMax(p_max_v1, p_v2);
		Point3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
	}

	const AABB Union(const AABB &aabb1, const AABB &aabb2) {
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb1.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb1.p_max);
		const XMVECTOR p_min_v2 = XMLoadFloat3(&aabb2.p_min);
		const XMVECTOR p_max_v2 = XMLoadFloat3(&aabb2.p_max);
		const XMVECTOR p_min_v = XMVectorMin(p_min_v1, p_min_v2);
		const XMVECTOR p_max_v = XMVectorMax(p_max_v1, p_max_v2);
		Point3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
	}

	const AABB Overlap(const AABB &aabb1, const AABB &aabb2) {
		if (!aabb1.Overlaps(aabb2)) {
			return AABB();
		}
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb1.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb1.p_max);
		const XMVECTOR p_min_v2 = XMLoadFloat3(&aabb2.p_min);
		const XMVECTOR p_max_v2 = XMLoadFloat3(&aabb2.p_max);
		const XMVECTOR p_min_v = XMVectorMax(p_min_v1, p_min_v2);
		const XMVECTOR p_max_v = XMVectorMin(p_max_v1, p_max_v2);
		Point3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
	}

	const AABB OverlapStrict(const AABB &aabb1, const AABB &aabb2) {
		if (!aabb1.OverlapsStrict(aabb2)) {
			return AABB();
		}
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb1.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb1.p_max);
		const XMVECTOR p_min_v2 = XMLoadFloat3(&aabb2.p_min);
		const XMVECTOR p_max_v2 = XMLoadFloat3(&aabb2.p_max);
		const XMVECTOR p_min_v = XMVectorMax(p_min_v1, p_min_v2);
		const XMVECTOR p_max_v = XMVectorMin(p_max_v1, p_max_v2);
		Point3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
	}

	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------

	BS::BS(const AABB &aabb) {
		const XMVECTOR p_min_v = XMLoadFloat3(&aabb.p_min);
		const XMVECTOR p_max_v = XMLoadFloat3(&aabb.p_max);
		const XMVECTOR centroid_v = 0.5f * (p_min_v + p_max_v);
		const XMVECTOR radius_v = 0.5f * (p_max_v - p_min_v);
		XMStoreFloat3(&p, centroid_v);
		Direction3 radius;
		XMStoreFloat3(&radius, radius_v);
		r = std::max(radius.x, std::max(radius.y, radius.z));
	}

	bool BS::Encloses(const Point3 &point) const {
		const XMVECTOR p_v = XMLoadFloat3(&p);
		const XMVECTOR point_v = XMLoadFloat3(&point);
		const XMVECTOR length_v = XMVector3Length(point_v - p_v);
		float length;
		XMStoreFloat(&length, length_v);
		return length <= r;
	}
		
	bool BS::EnclosesStrict(const Point3 &point) const {
		const XMVECTOR p_v = XMLoadFloat3(&p);
		const XMVECTOR point_v = XMLoadFloat3(&point);
		const XMVECTOR length_v = XMVector3Length(point_v - p_v);
		float length;
		XMStoreFloat(&length, length_v);
		return length < r;
	}
		
	bool BS::Encloses(const AABB &aabb) const {
		if (!Encloses(Point3(aabb.p_min.x, aabb.p_min.y, aabb.p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_min.x, aabb.p_min.y, aabb.p_max.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_min.x, aabb.p_max.y, aabb.p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_min.x, aabb.p_max.y, aabb.p_max.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_max.x, aabb.p_min.y, aabb.p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_max.x, aabb.p_min.y, aabb.p_max.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_max.x, aabb.p_max.y, aabb.p_min.z))) {
			return false;
		}
		if (!Encloses(Point3(aabb.p_max.x, aabb.p_max.y, aabb.p_max.z))) {
			return false;
		}
		
		return true;
	}

	bool BS::EnclosesStrict(const AABB &aabb) const {
		if (!EnclosesStrict(Point3(aabb.p_min.x, aabb.p_min.y, aabb.p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_min.x, aabb.p_min.y, aabb.p_max.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_min.x, aabb.p_max.y, aabb.p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_min.x, aabb.p_max.y, aabb.p_max.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_max.x, aabb.p_min.y, aabb.p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_max.x, aabb.p_min.y, aabb.p_max.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_max.x, aabb.p_max.y, aabb.p_min.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(aabb.p_max.x, aabb.p_max.y, aabb.p_max.z))) {
			return false;
		}

		return true;
	}

	bool BS::Encloses(const BS &bs) const {
		if (!Encloses(Point3(bs.p.x - bs.r, bs.p.y, bs.p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.p.x + bs.r, bs.p.y, bs.p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.p.x, bs.p.y - bs.r, bs.p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.p.x, bs.p.y + bs.r, bs.p.z))) {
			return false;
		}
		if (!Encloses(Point3(bs.p.x, bs.p.y, bs.p.z - bs.r))) {
			return false;
		}
		if (!Encloses(Point3(bs.p.x, bs.p.y, bs.p.z + bs.r))) {
			return false;
		}

		return true;
	}

	bool BS::EnclosesStrict(const BS &bs) const {
		if (!EnclosesStrict(Point3(bs.p.x - bs.r, bs.p.y, bs.p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.p.x + bs.r, bs.p.y, bs.p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.p.x, bs.p.y - bs.r, bs.p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.p.x, bs.p.y + bs.r, bs.p.z))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.p.x, bs.p.y, bs.p.z - bs.r))) {
			return false;
		}
		if (!EnclosesStrict(Point3(bs.p.x, bs.p.y, bs.p.z + bs.r))) {
			return false;
		}

		return true;
	}

	bool BS::EnclosedBy(const XMFLOAT4 *planes, size_t nb_planes) const {
		const XMVECTOR p_v = XMLoadFloat3(&p);
		
		for (size_t i = 0; i < nb_planes; ++i) {
			const XMVECTOR plane_v = XMLoadFloat4(&planes[i]);

			const XMVECTOR result_v = XMPlaneDotCoord(plane_v, p_v);
			float result;
			XMStoreFloat(&result, result_v);
			if (result < -r) {
				return false;
			}
		}

		return true;
	}

	bool BS::EnclosedStrictBy(const XMFLOAT4 *planes, size_t nb_planes) const {
		const XMVECTOR p_v = XMLoadFloat3(&p);
		
		
		for (size_t i = 0; i < nb_planes; ++i) {
			const XMVECTOR plane_v = XMLoadFloat4(&planes[i]);

			const XMVECTOR result_v = XMPlaneDotCoord(plane_v, p_v);
			float result;
			XMStoreFloat(&result, result_v);
			if (result <= -r) {
				return false;
			}
		}

		return true;
	}
}