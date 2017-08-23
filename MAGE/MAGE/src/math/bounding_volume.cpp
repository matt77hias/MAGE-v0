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
	// Axis-Aligned Bounding Box: Non-Members
	//-------------------------------------------------------------------------

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
	// Axis-Aligned Bounding Box
	//-------------------------------------------------------------------------

	AABB::AABB(const BS &bs)
		: m_p_min(Point3(bs.m_p.x - bs.m_r, bs.m_p.y - bs.m_r, bs.m_p.z - bs.m_r)),
		m_p_max(Point3(bs.m_p.x + bs.m_r, bs.m_p.y + bs.m_r, bs.m_p.z + bs.m_r)) {}

	const Point3 AABB::Centroid() const noexcept {
		const XMVECTOR p_min = XMLoadFloat3(&m_p_min);
		const XMVECTOR p_max = XMLoadFloat3(&m_p_max);
		const XMVECTOR centroid = 0.5f * (p_min + p_max);
		Point3 c;
		XMStoreFloat3(&c, centroid);
		return c;
	}

	const Direction3 AABB::Radius() const noexcept {
		const XMVECTOR p_min = XMLoadFloat3(&m_p_min);
		const XMVECTOR p_max = XMLoadFloat3(&m_p_max);
		const XMVECTOR radius = 0.5f * (p_max - p_min);
		Direction3 r;
		XMStoreFloat3(&r, radius);
		return r;
	}

	const Direction3 AABB::Diagonal() const noexcept {
		const XMVECTOR p_min = XMLoadFloat3(&m_p_min);
		const XMVECTOR p_max = XMLoadFloat3(&m_p_max);
		const XMVECTOR diagonal = p_max - p_min;
		Direction3 d;
		XMStoreFloat3(&d, diagonal);
		return d;
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

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

	bool AABB::Encloses(FXMVECTOR point) const noexcept {
		Point3 p;
		XMStoreFloat3(&p, point);
		return Encloses(p);
	}

	bool AABB::EnclosesStrict(FXMVECTOR point) const noexcept {
		Point3 p;
		XMStoreFloat3(&p, point);
		return EnclosesStrict(p);
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
		if (m_p_max.x - bs.m_p.x < bs.m_r) {
			return false;
		}
		if (m_p_max.y - bs.m_p.y < bs.m_r) {
			return false;
		}
		if (m_p_max.z - bs.m_p.z < bs.m_r) {
			return false;
		}
		if (bs.m_p.x - m_p_min.x < bs.m_r) {
			return false;
		}
		if (bs.m_p.y - m_p_min.y < bs.m_r) {
			return false;
		}
		if (bs.m_p.z - m_p_min.z < bs.m_r) {
			return false;
		}

		return true;
	}

	bool AABB::EnclosesStrict(const BS &bs) const noexcept {
		if (m_p_max.x - bs.m_p.x <= bs.m_r) {
			return false;
		}
		if (m_p_max.y - bs.m_p.y <= bs.m_r) {
			return false;
		}
		if (m_p_max.z - bs.m_p.z <= bs.m_r) {
			return false;
		}
		if (bs.m_p.x - m_p_min.x <= bs.m_r) {
			return false;
		}
		if (bs.m_p.y - m_p_min.y <= bs.m_r) {
			return false;
		}
		if (bs.m_p.z - m_p_min.z <= bs.m_r) {
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Overlapping = Partial | Full Coverage
	//-------------------------------------------------------------------------

	bool AABB::Overlaps(const AABB &aabb) const noexcept {
		// Test for no coverage.
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
		// Test for no coverage.
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

	bool AABB::Overlaps(const BS &bs) const noexcept {
		// Test for no coverage.
		if (m_p_max.x - bs.m_p.x < -bs.m_r) {
			return false;
		}
		if (m_p_max.y - bs.m_p.y < -bs.m_r) {
			return false;
		}
		if (m_p_max.z - bs.m_p.z < -bs.m_r) {
			return false;
		}
		if (bs.m_p.x - m_p_min.x < -bs.m_r) {
			return false;
		}
		if (bs.m_p.y - m_p_min.y < -bs.m_r) {
			return false;
		}
		if (bs.m_p.z - m_p_min.z < -bs.m_r) {
			return false;
		}

		return true;
	}

	bool AABB::OverlapsStrict(const BS &bs) const noexcept {
		// Test for no coverage.
		if (m_p_max.x - bs.m_p.x <= -bs.m_r) {
			return false;
		}
		if (m_p_max.y - bs.m_p.y <= -bs.m_r) {
			return false;
		}
		if (m_p_max.z - bs.m_p.z <= -bs.m_r) {
			return false;
		}
		if (bs.m_p.x - m_p_min.x <= -bs.m_r) {
			return false;
		}
		if (bs.m_p.y - m_p_min.y <= -bs.m_r) {
			return false;
		}
		if (bs.m_p.z - m_p_min.z <= -bs.m_r) {
			return false;
		}

		return true;
	}
	
	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Overlapping = Intersecting = Partial Coverage
	//-------------------------------------------------------------------------

	bool AABB::Intersects(const Point3 &point, float epsilon) const noexcept {
		float distance[6];

		// Test for no coverage.

		distance[0] = m_p_max.x - point.x;
		if (distance[0] < -epsilon) {
			return false;
		}
		distance[1] = m_p_max.y - point.y;
		if (distance[1] < -epsilon) {
			return false;
		}
		distance[2] = m_p_max.z - point.z;
		if (distance[2] < -epsilon) {
			return false;
		}
		distance[3] = point.x - m_p_min.x;
		if (distance[3] < -epsilon) {
			return false;
		}
		distance[4] = point.y - m_p_min.y;
		if (distance[4] < -epsilon) {
			return false;
		}
		distance[5] = point.z - m_p_min.z;
		if (distance[5] < -epsilon) {
			return false;
		}

		// Test for partial coverage.
		bool intersection = false;
		for (size_t i = 0; i < 6; ++i) {
			intersection |= (fabs(distance[i]) <= epsilon);
		}

		return intersection;
	}

	bool AABB::Intersects(FXMVECTOR point, float epsilon) const noexcept {
		Point3 p;
		XMStoreFloat3(&p, point);
		return Intersects(p, epsilon);
	}

	bool AABB::Intersects(const AABB &aabb) const noexcept {
		// Test for no coverage.
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

		// Test for partial coverage.
		return (aabb.m_p_min.x <= m_p_min.x)
			|| (aabb.m_p_min.y <= m_p_min.y)
			|| (aabb.m_p_min.z <= m_p_min.z)
			|| (aabb.m_p_max.x >= m_p_max.x)
			|| (aabb.m_p_max.y >= m_p_max.y)
			|| (aabb.m_p_max.z >= m_p_max.z);
	}

	bool AABB::Intersects(const BS &bs) const noexcept {
		float distance[6];
		
		// Test for no coverage.

		distance[0] = m_p_max.x - bs.m_p.x;
		if (distance[0] < -bs.m_r) {
			return false;
		}
		distance[1] = m_p_max.y - bs.m_p.y;
		if (distance[1] < -bs.m_r) {
			return false;
		}
		distance[2] = m_p_max.z - bs.m_p.z;
		if (distance[2] < -bs.m_r) {
			return false;
		}
		distance[3] = bs.m_p.x - m_p_min.x;
		if (distance[3] < -bs.m_r) {
			return false;
		}
		distance[4] = bs.m_p.y - m_p_min.y;
		if (distance[4] < -bs.m_r) {
			return false;
		}
		distance[5] = bs.m_p.z - m_p_min.z;
		if (distance[5] < -bs.m_r) {
			return false;
		}

		// Test for partial coverage.
		bool intersection = false;
		for (size_t i = 0; i < 6; ++i) {
			intersection |= (fabs(distance[i]) <= bs.m_r);
		}

		return intersection;
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Overlapping = Intersecting = Partial Coverage
	//-------------------------------------------------------------------------

	Coverage AABB::Classify(const Point3 &point, float epsilon) const noexcept {
		float distance[6];

		// Test for no coverage.

		distance[0] = m_p_max.x - point.x;
		if (distance[0] < -epsilon) {
			return Coverage::NoCoverage;
		}
		distance[1] = m_p_max.y - point.y;
		if (distance[1] < -epsilon) {
			return Coverage::NoCoverage;
		}
		distance[2] = m_p_max.z - point.z;
		if (distance[2] < -epsilon) {
			return Coverage::NoCoverage;
		}
		distance[3] = point.x - m_p_min.x;
		if (distance[3] < -epsilon) {
			return Coverage::NoCoverage;
		}
		distance[4] = point.y - m_p_min.y;
		if (distance[4] < -epsilon) {
			return Coverage::NoCoverage;
		}
		distance[5] = point.z - m_p_min.z;
		if (distance[5] < -epsilon) {
			return Coverage::NoCoverage;
		}

		// Test for partial coverage.
		bool intersection = false;
		for (size_t i = 0; i < 6; ++i) {
			intersection |= (fabs(distance[i]) <= epsilon);
		}

		return intersection ? Coverage::PartialCoverage : Coverage::FullCoverage;
	}

	Coverage AABB::Classify(FXMVECTOR point, float epsilon) const noexcept {
		Point3 p;
		XMStoreFloat3(&p, point);
		return Classify(p, epsilon);
	}

	Coverage AABB::Classify(const AABB &aabb) const noexcept {
		// Test for no coverage.
		if (aabb.m_p_min.x >= m_p_max.x) {
			return Coverage::NoCoverage;
		}
		if (aabb.m_p_min.y >= m_p_max.y) {
			return Coverage::NoCoverage;
		}
		if (aabb.m_p_min.z >= m_p_max.z) {
			return Coverage::NoCoverage;
		}
		if (aabb.m_p_max.x <= m_p_min.x) {
			return Coverage::NoCoverage;
		}
		if (aabb.m_p_max.y <= m_p_min.y) {
			return Coverage::NoCoverage;
		}
		if (aabb.m_p_max.z <= m_p_min.z) {
			return Coverage::NoCoverage;
		}

		// Test for partial coverage.
		const bool intersection 
			 = (aabb.m_p_min.x <= m_p_min.x)
			|| (aabb.m_p_min.y <= m_p_min.y)
			|| (aabb.m_p_min.z <= m_p_min.z)
			|| (aabb.m_p_max.x >= m_p_max.x)
			|| (aabb.m_p_max.y >= m_p_max.y)
			|| (aabb.m_p_max.z >= m_p_max.z);

		return intersection ? Coverage::PartialCoverage : Coverage::FullCoverage;
	}

	Coverage AABB::Classify(const BS &bs) const noexcept {
		float distance[6];

		// Test for no coverage.

		distance[0] = m_p_max.x - bs.m_p.x;
		if (distance[0] < -bs.m_r) {
			return Coverage::NoCoverage;
		}
		distance[1] = m_p_max.y - bs.m_p.y;
		if (distance[1] < -bs.m_r) {
			return Coverage::NoCoverage;
		}
		distance[2] = m_p_max.z - bs.m_p.z;
		if (distance[2] < -bs.m_r) {
			return Coverage::NoCoverage;
		}
		distance[3] = bs.m_p.x - m_p_min.x;
		if (distance[3] < -bs.m_r) {
			return Coverage::NoCoverage;
		}
		distance[4] = bs.m_p.y - m_p_min.y;
		if (distance[4] < -bs.m_r) {
			return Coverage::NoCoverage;
		}
		distance[5] = bs.m_p.z - m_p_min.z;
		if (distance[5] < -bs.m_r) {
			return Coverage::NoCoverage;
		}

		// Test for partial coverage.
		bool intersection = false;
		for (size_t i = 0; i < 6; ++i) {
			intersection |= (fabs(distance[i]) <= bs.m_r);
		}

		return intersection ? Coverage::PartialCoverage : Coverage::FullCoverage;
	}

	//-------------------------------------------------------------------------
	// Bounding Sphere: Non-Members
	//-------------------------------------------------------------------------

	const BS Union(const BS &bs, const Point3 &point) noexcept {
		const XMVECTOR p0 = XMLoadFloat3(&bs.m_p);
		const XMVECTOR p1 = XMLoadFloat3(&point);
		const XMVECTOR length = XMVector3Length(p1 - p0);
		return BS(bs.m_p, std::max(bs.m_r, XMVectorGetX(length)));
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

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	bool BS::Encloses(const Point3 &point) const noexcept {
		return Encloses(XMLoadFloat3(&point));
	}
		
	bool BS::EnclosesStrict(const Point3 &point) const noexcept {
		return EnclosesStrict(XMLoadFloat3(&point));
	}

	bool BS::Encloses(FXMVECTOR point) const noexcept {
		const XMVECTOR p = XMLoadFloat3(&m_p);
		const XMVECTOR length = XMVector3Length(point - p);
		return XMVectorGetX(length) <= m_r;
	}

	bool BS::EnclosesStrict(FXMVECTOR point) const noexcept {
		const XMVECTOR p = XMLoadFloat3(&m_p);
		const XMVECTOR length = XMVector3Length(point - p);
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
}