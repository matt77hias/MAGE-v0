#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\geometry\geometry.hpp"
#include "utils\collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <limits>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Coverage
	//-------------------------------------------------------------------------

	/**
	 An enumeration of the different coverages for volumes.

	 This contains:
	 @c NoCoverage,
	 @c PartialCoverage and
	 @c FullCoverage.
	 */
	enum struct Coverage {
		NoCoverage,		 // No coverage      (i.e. no overlap)
		PartialCoverage, // Partial coverage (i.e. overlap + not enclosing)
		FullCoverage	 // Full coverage    (i.e. overlap + enclosing)
	};

	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------
#pragma region

	// Forward declaration.
	class AABB;

	/**
	 A struct of Bounding Spheres (BS).
	 */
	class alignas(16) BS final {

	public:

		//-------------------------------------------------------------------------
		// Class Member Methods
		//-------------------------------------------------------------------------

		/**
		 Returns the union BS of the given BS and the given point.

		 @param[in]		bs
						A reference to the BS.
		 @param[in]		point
						A reference to the point.
		 @return		The union BS of @a bs and @a point.
		 */
		static const BS Union(const BS &bs, const Point3 &point) noexcept {
			return Union(bs, XMLoadFloat3(&point));
		}

		/**
		 Returns the union BS of the given BS and the given vertex.

		 @tparam		VertexT
						The vertex type.
		 @param[in]		bs
						A reference to the BS.
		 @param[in]		vertex
						A reference to the VertexT.
		 @return		The union BS of @a bs and @a vertex.
		 */
		template< typename VertexT >
		static const BS Union(const BS &bs, const VertexT &vertex) noexcept {
			return Union(bs, vertex.m_p);
		}

		/**
		 Returns the union BS of the given BS and the given point.

		 @param[in]		bs
						A reference to the BS.
		 @param[in]		point
						The point.
		 @return		The union BS of @a bs and @a point.
		 */
		static const BS XM_CALLCONV Union(const BS &bs, FXMVECTOR point) noexcept {
			const XMVECTOR length = XMVector3Length(point - bs.m_pr);
			const F32 radius = std::max(bs.Radius(), XMVectorGetX(length));
			return BS(bs.m_pr, radius);
		}

		/**
		 Returns the maximum BS (i.e. invariant for union operations).

		 @return		The maximum BS.
		 */
		static const BS Maximum() noexcept {
			return BS(g_XMZero, std::numeric_limits< float >::infinity());
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a BS.
		 */
		BS() noexcept
			: m_pr(g_XMZero) {}

		/**
		 Constructs a BS of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit BS(const Point3 &p) noexcept 
			: BS(p, 0.0f) {}

		/**
		 Constructs a BS of the given point.

		 @param[in]		p
						The point.
		 */
		explicit BS(FXMVECTOR p) noexcept
			: BS(p, 0.0f) {}

		/**
		 Constructs a BS.

		 @param[in]		p
						A reference to the position.
		 @param[in]		r
						The radius.
		 */
		BS(const Point3 &p, F32 r) noexcept
			: BS(XMLoadFloat3(&p), r) {}

		/**
		 Constructs a BS.

		 @param[in]		p
						The position.
		 @param[in]		r
						The radius.
		 */
		BS(FXMVECTOR p, F32 r) noexcept
			: m_pr(XMVectorSetW(p, r)) {}

		/**
		 Constructs a BS from the given AABB.

		 @param[in]		aabb
						A reference to the aabb.
		 */
		explicit BS(const AABB &aabb) noexcept;

		/**
		 Constructs a BS from the given BS.

		 @param[in]		bs
						A reference to the bs.
		 */
		BS(const BS &bs) noexcept = default;

		/**
		 Constructs a BS from the given BS.

		 @param[in]		bs
						A reference to the bs.
		 */
		BS(BS &&bs) noexcept = default;

		/**
		 Destructs this BS.
		 */
		~BS() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given BS to this BS.

		 @param[in]		bs
						A reference to the BS to copy from.
		 @return		A reference to the copy of the given BS (i.e. this BS).
		 */
		BS &operator=(const BS &bs) noexcept = default;

		/**
		 Copies the given BS to this BS.

		 @param[in]		bs
						A reference to the BS to copy from.
		 @return		A reference to the copy of the given BS (i.e. this BS).
		 */
		BS &operator=(BS &&bs) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the centroid of this BS.

		 @return		The centroid of this BS.
		 */
		const XMVECTOR Centroid() const noexcept {
			return XMVectorSetW(m_pr, 1.0f);
		}

		/**
		 Returns the radius of this BS.

		 @return		The radius of this BS.
		 */
		F32 Radius() const noexcept {
			return XMVectorGetW(m_pr);
		}

		//---------------------------------------------------------------------
		// Member Methods: Enclosing = Full Coverage
		//---------------------------------------------------------------------

		/**
		 Checks whether this BS completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this BS completely encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool Encloses(const Point3 &point) const noexcept {
			return Encloses(XMLoadFloat3(&point));
		}

		/**
		 Checks whether this BS completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this BS completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool EnclosesStrict(const Point3 &point) const noexcept {
			return EnclosesStrict(XMLoadFloat3(&point));
		}

		/**
		 Checks whether this BS completely encloses the given point.

		 @param[in]		point
						The point.
		 @return		@c true if this BS completely encloses
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept {
			const XMVECTOR length = XMVector3Length(point - m_pr);
			return XMVectorGetX(length) <= Radius();
		}

		/**
		 Checks whether this BS completely, strictly encloses the given point.

		 @param[in]		point
						The point.
		 @return		@c true if this BS completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept {
			const XMVECTOR length = XMVector3Length(point - m_pr);
			return XMVectorGetX(length) < Radius();
		}

		/**
		 Checks whether this BS completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this BS completely encloses @a aabb. 
						@c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						a BS.
		 */
		bool Encloses(const AABB &aabb) const noexcept;

		/**
		 Checks whether this BS completely, strictly encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this BS completely, strictly encloses 
						@a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						a BS.
		 */
		bool EnclosesStrict(const AABB &aabb) const noexcept;

		/**
		 Checks whether this BS completely encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this BS completely encloses @a bs.
						@c false otherwise.
		 @note			This is a full coverage test of a BS with regard to a 
						BS.
		 */
		bool Encloses(const BS &bs) const noexcept;

		/**
		 Checks whether this BS completely, strictly encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this BS completely, strictly encloses @a bs.
						@c false otherwise.
		 @note			This is a full coverage test of a BS with regard to a 
						BS.
		 */
		bool EnclosesStrict(const BS &bs) const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Operators
		//---------------------------------------------------------------------

		/**
		 Checks whether the given BS is equal to this BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if the given BS is equal to this BS.
						@c false otherwise.
		 */
		bool operator==(const BS &bs) const noexcept {
			return XMVector4Equal(m_pr, bs.m_pr);
		}

		/**
		 Checks whether the given BS is not equal to this BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if the given BS is equal to this BS.
						@c false otherwise.
		 */
		bool operator!=(const BS &bs) const noexcept {
			return !(*this == bs);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position and radus of this BS.
		 */
		XMVECTOR m_pr;
	};

#pragma endregion

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box
	//-------------------------------------------------------------------------
#pragma region

	/**
	 A struct of Axis-Aligned Bounding Boxes (AABBs).
	 */
	class alignas(16) AABB final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the union AABB of the given AABB and the given point.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		point
						A reference to the point.
		 @return		The union AABB of @a aabb and @a point.
		 */
		static const AABB Union(const AABB &aabb, const Point3 &point) noexcept {
			return Union(aabb, XMLoadFloat3(&point));
		}

		/**
		 Returns the union AABB of the given AABB and the given vertex.

		 @tparam		VertexT
						The vertex type.
		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		vertex
						A reference to the VertexT.
		 @return		The union AABB of @a aabb and @a vertex.
		*/
		template< typename VertexT >
		static const AABB Union(const AABB &aabb, const VertexT &vertex) noexcept {
			return Union(aabb, vertex.m_p);
		}

		/**
		 Returns the union AABB of the given AABB and the given point.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		point
						A reference to the point.
		 @return		The union AABB of @a aabb and @a point.
		 */
		static const AABB XM_CALLCONV Union(const AABB &aabb, FXMVECTOR point) noexcept {
			return Union(aabb, AABB(point));
		}

		/**
		 Returns the union AABB of the two given AABBs.

		 @param[in]		aabb1
						A reference to the first AABB.
		 @param[in]		aabb2
						A reference to the second AABB.
		 @return		The union AABB of @a aabb1 and @a aabb2.
		 */
		static const AABB Union(const AABB &aabb1, const AABB &aabb2) noexcept {
			const XMVECTOR p_min = XMVectorMin(aabb1.m_min, aabb2.m_min);
			const XMVECTOR p_max = XMVectorMax(aabb1.m_max, aabb2.m_max);
			return AABB(p_min, p_max);
		}
	
		/**
		 Returns the overlap AABB of the two given AABBs.

		 @param[in]		aabb1
						A reference to the first AABB.
		 @param[in]		aabb2
						A reference to the second AABB.
		 @return		The identity AABB in case of no overlap.
		 @return		The overlap AABB of @a aabb1 and @a aabb2.
		 */
		static const AABB Overlap(const AABB &aabb1, const AABB &aabb2) noexcept {
			const XMVECTOR p_min = XMVectorMax(aabb1.m_min, aabb2.m_min);
			const XMVECTOR p_max = XMVectorMin(aabb1.m_max, aabb2.m_max);
			return aabb1.Overlaps(aabb2) ? AABB(p_min, p_max) : AABB();
		}
	
		/**
		 Returns the strict overlap AABB of the two given AABBs.

		 @param[in]		aabb1
						A reference to the first AABB.
		 @param[in]		aabb2
						A reference to the second AABB.
		 @return		The identity AABB in case of no strict overlap.
		 @return		The strict overlap AABB of @a aabb1 and @a aabb2.
		 */
		static const AABB OverlapStrict(const AABB &aabb1, const AABB &aabb2) noexcept {
			const XMVECTOR p_min = XMVectorMax(aabb1.m_min, aabb2.m_min);
			const XMVECTOR p_max = XMVectorMin(aabb1.m_max, aabb2.m_max);
			return aabb1.OverlapsStrict(aabb2) ? AABB(p_min, p_max) : AABB();
		}
	
		/**
		 Returns the minimum AABB (i.e. variant for union operations).

		 @return		The minimum AABB.
		 */
		static const AABB Minimum() noexcept {
			return AABB();
		}

		/**
		 Returns the maximum AABB (i.e. invariant for union operations).

		 @return		The maximum AABB.
		 */
		static const AABB Maximum() noexcept {
			return AABB(-g_XMInfinity, g_XMInfinity);
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an (identity) AABB.
		 */
		AABB() noexcept 
			: AABB(g_XMInfinity, -g_XMInfinity) {}

		/**
		 Constructs an AABB of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit AABB(const Point3 &p) noexcept
			: AABB(XMLoadFloat3(&p)) {}

		/**
		 Constructs an AABB of the given point.

		 @param[in]		p
						The point.
		 */
		explicit AABB(FXMVECTOR p) noexcept
			: AABB(p, p) {}

		/**
		 Constructs an AABB of the given extents.

		 @param[in]		p_min
						A reference to the minimum extents.
		 @param[in]		p_max
						A reference to the maximum extents.
		 */
		AABB(const Point3 &p_min, const Point3 &p_max) noexcept
			: AABB(XMLoadFloat3(&p_min), XMLoadFloat3(&p_max)) {}

		/**
		 Constructs an AABB of the given extents.

		 @param[in]		p_min
						The minimum extents.
		 @param[in]		p_max
						The maximum extents.
		 */
		AABB(FXMVECTOR p_min, FXMVECTOR p_max) noexcept
			: m_min(XMVectorSetW(p_min, 1.0f)), 
			  m_max(XMVectorSetW(p_max, 1.0f)) {}

		/**
		 Constructs an AABB from the given AABB.

		 @param[in]		aabb
						A reference to the AABB to copy.
		 */
		AABB(const AABB &aabb) noexcept = default;

		/**
		 Constructs an AABB by moving the given AABB.

		 @param[in]		aabb
						A reference to the AABB to move.
		 */
		AABB(AABB &&aabb) noexcept = default;

		/**
		 Constructs an AABB of the given BS.

		 @param[in]		bs
						A reference to the BS.
		 */
		explicit AABB(const BS &bs) noexcept;

		/**
		 Destructs this AABB.
		 */
		~AABB() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given AABB to this AABB.

		 @param[in]		aabb
						A reference to the AABB to copy.
		 @return		A reference to the copy of the given AABB (i.e. this 
						AABB).
		 */
		AABB &operator=(const AABB &aabb) noexcept = default;

		/**
		 Moves the given AABB to this AABB.

		 @param[in]		aabb
						A reference to the AABB to move.
		 @return		A reference to the moved AABB (i.e. this AABB).
		 */
		AABB &operator=(AABB &&aabb) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the minimum point of this AABB.
 
		 @return		The minimum point of this AABB.
		 */
		const XMVECTOR MinPoint() const noexcept {
			return m_min;
		}

		/**
		 Returns the maximum point of this AABB.
 
		 @return		The maximum point of this AABB.
		 */
		const XMVECTOR MaxPoint() const noexcept {
			return m_max;
		}

		/**
		 Returns the minimum point of this AABB along a given normal.

		 @param[in]		n
						The normal.
		 @param[out]	pmin
						A reference to the minimum point of this AABB along @a n.
		 @param[out]	pmax
						A reference to the maximum point of this AABB along @a n.
		 */
		void XM_CALLCONV MinAndMaxPointAlongNormal(FXMVECTOR n, 
			XMVECTOR &pmin, XMVECTOR &pmax) const noexcept {
			
			const XMVECTOR control = XMVectorGreaterOrEqual(n, XMVectorZero());
			pmin = XMVectorSelect(m_max, m_min, control);
			pmax = XMVectorSelect(m_min, m_max, control);
		}

		/**
		 Returns the minimum point of this AABB along a given normal.

		 @param[in]		n
						The normal.
		 @return		The minimum point of this AABB along @a n.
		 */
		const XMVECTOR XM_CALLCONV MinPointAlongNormal(FXMVECTOR n) const noexcept {
			const XMVECTOR control = XMVectorGreaterOrEqual(n, XMVectorZero());
			return XMVectorSelect(m_max, m_min, control);
		}

		/**
		 Returns the maximum point of this AABB along a given normal.

		 @param[in]		n
						The normal.
		 @return		The minimum point of this AABB along @a n.
		 */
		const XMVECTOR XM_CALLCONV MaxPointAlongNormal(FXMVECTOR n) const noexcept {
			const XMVECTOR control = XMVectorGreaterOrEqual(n, XMVectorZero());
			return XMVectorSelect(m_min, m_max, control);
		}

		/**
		 Returns the centroid of this AABB.
 
		 @return		The centroid of this AABB.
		 */
		const XMVECTOR Centroid() const noexcept {
			return 0.5f * (m_min + m_max);
		}

		/**
		 Returns the radius of this AABB.

		 @return		The radius of this AABB.
		 */
		const XMVECTOR Radius() const noexcept {
			return 0.5f * (m_max - m_min);
		}

		/**
		 Returns the diagonal of this AABB.

		 @return		The diagonal of this AABB.
		 */
		const XMVECTOR Diagonal() const noexcept {
			return m_max - m_min;
		}

		//---------------------------------------------------------------------
		// Member Methods: Enclosing = Full Coverage
		//---------------------------------------------------------------------

		/**
		 Checks whether this AABB completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely encloses @a point.
						@c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool Encloses(const Point3 &point) const noexcept {
			return Encloses(XMLoadFloat3(&point));
		}

		/**
		 Checks whether this AABB completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool EnclosesStrict(const Point3 &point) const noexcept {
			return EnclosesStrict(XMLoadFloat3(&point));
		}

		/**
		 Checks whether this AABB completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely encloses @a point.
						@c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept {
			if (XMVector3Less(point, m_min)) {
				return false;
			}
			if (XMVector3Greater(point, m_max)) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept {
			if (XMVector3LessOrEqual(point, m_min)) {
				return false;
			}
			if (XMVector3GreaterOrEqual(point, m_max)) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely encloses @a aabb.
						@c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						an AABB.
		 */
		bool Encloses(const AABB &aabb) const noexcept {
			if (!Encloses(aabb.m_min)) {
				return false;
			}
			if (!Encloses(aabb.m_max)) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB completely, strictly encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely, strictly encloses 
						@a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						an AABB.
		 */
		bool EnclosesStrict(const AABB &aabb) const noexcept {
			if (!EnclosesStrict(aabb.m_min)) {
				return false;
			}
			if (!EnclosesStrict(aabb.m_max)) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB completely encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB completely encloses @a bs.
						@c false otherwise.
		 @note			This is a full coverage test of a BS with regard to an 
						AABB.
		 */
		bool Encloses(const BS &bs) const noexcept;

		/**
		 Checks whether this AABB completely, strictly encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB completely, strictly encloses 
						@a bs. @c false otherwise.
		 @note			This is a full coverage test of a BS with regard to an 
						AABB.
		 */
		bool EnclosesStrict(const BS &bs) const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Overlapping = Partial | Full Coverage
		//---------------------------------------------------------------------

		/**
		 Checks whether this AABB overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB overlaps @a aabb.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of an AABB 
						with regard to an AABB.
		 */
		bool Overlaps(const AABB &aabb) const noexcept {
			// Test for no coverage.
			if (XMVector3Greater(aabb.m_min, m_max)) {
				return false;
			}
			if (XMVector3Less(aabb.m_max, m_min)) {
				return false;
			}
			
			return true;
		}

		/**
		 Checks whether this AABB strictly overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB strictly overlaps @a aabb.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of an AABB 
						with regard to an AABB.
		 */
		bool OverlapsStrict(const AABB &aabb) const noexcept {
			// Test for no coverage.
			if (XMVector3GreaterOrEqual(aabb.m_min, m_max)) {
				return false;
			}
			if (XMVector3LessOrEqual(aabb.m_max, m_min)) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB overlaps the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB overlaps @a bs.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of a BS with 
						regard to an AABB.
		 */
		bool Overlaps(const BS &bs) const noexcept;

		/**
		 Checks whether this AABB strictly overlaps the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB strictly overlaps @a bs.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of a BS with 
						regard to an AABB.
		 */
		bool OverlapsStrict(const BS &bs) const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Classification
		//---------------------------------------------------------------------

		/**
		 Classifies the coverage of the given point with regard to this AABB.

		 @param[in]		point
						A reference to the point.
		 @param[in]		epsilon
						The epsilon value for F32 comparisons.
		 @return		The coverage of @a point with regard to this AABB.
		 */
		Coverage Classify(const Point3 &point,
			F32 epsilon = 0.0f) const noexcept {

			return Classify(XMLoadFloat3(&point), epsilon);
		}

		/**
		 Classifies the coverage of the given point with regard to this AABB.

		 @param[in]		point
						The point.
		 @param[in]		epsilon
						The epsilon value for F32 comparisons.
		 @return		The coverage of @a point with regard to this AABB.
		 */
		Coverage XM_CALLCONV Classify(FXMVECTOR point,
			F32 epsilon = 0.0f) const noexcept {

			return Classify(BS(point, epsilon));
		}

		/**
		 Classifies the coverage of the given AABB with regard to this AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		The coverage of @a aabb with regard to this AABB.
		 */
		Coverage Classify(const AABB &aabb) const noexcept {
			return Encloses(aabb) ? Coverage::FullCoverage : 
				(Overlaps(aabb) ? Coverage::PartialCoverage : Coverage::NoCoverage);
		}
		
		/**
		 Classifies the coverage of the given BS with regard to this AABB.

		 @param[in]		bs
						A reference to the BS.
		 @return		The coverage of @a bs with regard to this AABB.
		 */
		Coverage Classify(const BS &bs) const noexcept {
			return Encloses(bs) ? Coverage::FullCoverage :
				(Overlaps(bs) ? Coverage::PartialCoverage : Coverage::NoCoverage);
		}

		//---------------------------------------------------------------------
		// Member Methods: Operators
		//---------------------------------------------------------------------

		/**
		 Checks whether the given AABB is equal to this AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if the given AABB is equal to this AABB.
						@c false otherwise.
		 */
		bool operator==(const AABB &aabb) const noexcept {
			return XMVector4Equal(m_min, aabb.m_min)
				&& XMVector4Equal(m_max, aabb.m_max);
		}

		/**
		 Checks whether the given AABB is not equal to this AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if the given AABB is equal to this AABB.
						@c false otherwise.
		 */
		bool operator!=(const AABB &aabb) const noexcept {
			return !(*this == aabb);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The minimum extents of this AABB.
		 */
		XMVECTOR m_min;

		/**
		 The maximum extents of this AABB.
		 */
		XMVECTOR m_max;
	};

#pragma endregion
}