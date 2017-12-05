//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\geometry\bounding_volume.hpp"
#include "utils\logging\error.hpp"

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

	AABB::AABB(const BS &bs) noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 r = bs.Radius();
		const XMVECTOR radius = XMVectorSet(r, r, r, 0.0f);
		m_min = centroid - radius;
		m_max = centroid + radius;
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	bool AABB::Encloses(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 r = bs.Radius();
		const XMVECTOR radius = XMVectorSet(r, r, r, 0.0f);

		if (XMVector3Less(m_max - centroid, radius)) {
			return false;
		}
		if (XMVector3Less(centroid - m_min, radius)) {
			return false;
		}

		return true;
	}

	bool AABB::EnclosesStrict(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 r = bs.Radius();
		const XMVECTOR radius = XMVectorSet(r, r, r, 0.0f);

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

	bool AABB::Overlaps(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 r = -bs.Radius();
		const XMVECTOR radius = XMVectorSet(r, r, r, 0.0f);

		// Test for no coverage.
		if (XMVector3Less(m_max - centroid, radius)) {
			return false;
		}
		if (XMVector3Less(centroid - m_min, radius)) {
			return false;
		}

		return true;
	}

	bool AABB::OverlapsStrict(const BS &bs) const noexcept {
		const XMVECTOR centroid = bs.Centroid();
		const F32 r = -bs.Radius();
		const XMVECTOR radius = XMVectorSet(r, r, r, 0.0f);

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

	BS::BS(const AABB &aabb) noexcept {
		const XMVECTOR centroid = aabb.Centroid();
		const XMVECTOR radius   = aabb.Radius();
		const F32 r = std::max(XMVectorGetX(radius), 
			          std::max(XMVectorGetY(radius), 
						       XMVectorGetZ(radius)));
		m_pr = XMVectorSetW(centroid, r);
	}

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Enclosing = Full Coverage
	//-------------------------------------------------------------------------

	bool BS::Encloses(const AABB &aabb) const noexcept {
		const XMVECTOR pmin = aabb.MinPoint();
		const XMVECTOR pmax = aabb.MaxPoint();
		
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

	bool BS::EnclosesStrict(const AABB &aabb) const noexcept {
		const XMVECTOR pmin = aabb.MinPoint();
		const XMVECTOR pmax = aabb.MaxPoint();

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

	bool BS::Encloses(const BS &bs) const noexcept {
		const XMVECTOR p = bs.Centroid();
		const F32 radius = bs.Radius();

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

	bool BS::EnclosesStrict(const BS &bs) const noexcept {
		const XMVECTOR p = bs.Centroid();
		const F32 radius = bs.Radius();

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
}