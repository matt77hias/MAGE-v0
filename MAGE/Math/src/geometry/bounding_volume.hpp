#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "geometry\geometry.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <limits>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------
	#pragma region

	// Forward declaration.
	class AABB;

	/**
	 A class of Bounding Spheres.
	 */
	class alignas(16) BoundingSphere final {

	public:

		//-------------------------------------------------------------------------
		// Class Member Methods
		//-------------------------------------------------------------------------

		/**
		 Returns the union bounding sphere of the given bounding sphere and the 
		 given point.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @param[in]		point
						A reference to the point.
		 @return		The union bounding sphere of @a sphere and @a point.
		 */
		[[nodiscard]] static const BoundingSphere XM_CALLCONV 
			Union(const BoundingSphere &sphere, const Point3 &point) noexcept {

			return Union(sphere, XMLoad(point));
		}

		/**
		 Returns the union bounding sphere of the given bounding sphere and the 
		 given vertex.

		 @tparam		VertexT
						The vertex type.
		 @param[in]		sphere
						A reference to the bounding sphere.
		 @param[in]		vertex
						A reference to the vertex.
		 @return		The union bounding sphere of @a sphere and @a vertex.
		 */
		template< typename VertexT >
		[[nodiscard]] static const BoundingSphere XM_CALLCONV 
			Union(const BoundingSphere &sphere, const VertexT &vertex) noexcept {

			return Union(sphere, vertex.m_p);
		}

		/**
		 Returns the union bounding sphere of the given bounding sphere and the 
		 given point.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @param[in]		point
						The point.
		 @return		The union bounding sphere of @a sphere and @a point.
		 */
		[[nodiscard]] static const BoundingSphere XM_CALLCONV 
			Union(const BoundingSphere &sphere, FXMVECTOR point) noexcept {

			const auto length = XMVector3Length(point - sphere.m_pr);
			const auto radius = std::max(sphere.Radius(), XMVectorGetX(length));
			return BoundingSphere(sphere.m_pr, radius);
		}

		/**
		 Returns the maximum bounding sphere (i.e. the bounding sphere that is
		 invariant for union operations).

		 @return		The maximum bounding sphere.
		 */
		[[nodiscard]] static const BoundingSphere XM_CALLCONV Maximum() noexcept {
			return BoundingSphere(g_XMZero, 
				                  std::numeric_limits< float >::infinity());
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a bounding sphere.
		 */
		BoundingSphere() noexcept
			: m_pr(g_XMZero) {}

		/**
		 Constructs a bounding sphere of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit BoundingSphere(const Point3 &p) noexcept 
			: BoundingSphere(p, 0.0f) {}

		/**
		 Constructs a bounding sphere of the given point.

		 @param[in]		p
						The point.
		 */
		explicit BoundingSphere(FXMVECTOR p) noexcept
			: BoundingSphere(p, 0.0f) {}

		/**
		 Constructs a BoundingSphere.

		 @param[in]		p
						A reference to the position.
		 @param[in]		r
						The radius.
		 */
		BoundingSphere(const Point3 &p, F32 r) noexcept
			: BoundingSphere(XMLoad(p), r) {}

		/**
		 Constructs a bounding sphere.

		 @param[in]		p
						The position.
		 @param[in]		r
						The radius.
		 */
		BoundingSphere(FXMVECTOR p, F32 r) noexcept
			: m_pr(XMVectorSetW(p, r)) {}

		/**
		 Constructs a bounding sphere from the given AABB.

		 @param[in]		aabb
						A reference to the aabb.
		 */
		explicit BoundingSphere(const AABB &aabb) noexcept;

		/**
		 Constructs a bounding sphere from the given bounding sphere.

		 @param[in]		sphere
						A reference to the sphere to copy.
		 */
		BoundingSphere(const BoundingSphere &sphere) noexcept = default;

		/**
		 Constructs a bounding sphere by moving the given bounding sphere.

		 @param[in]		sphere
						A reference to the sphere to move.
		 */
		BoundingSphere(BoundingSphere &&sphere) noexcept = default;

		/**
		 Destructs this bounding sphere.
		 */
		~BoundingSphere() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bounding sphere to this bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere to copy.
		 @return		A reference to the copy of the given bounding sphere 
						(i.e. this bounding sphere).
		 */
		BoundingSphere &operator=(const BoundingSphere &sphere) noexcept = default;

		/**
		 Moves the given bounding sphere to this bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere to move.
		 @return		A reference to the moved bounding sphere (i.e. this 
						bounding sphere).
		 */
		BoundingSphere &operator=(BoundingSphere &&sphere) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the centroid of this bounding sphere.

		 @return		The centroid of this bounding sphere.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV Centroid() const noexcept {
			return XMVectorSetW(m_pr, 1.0f);
		}

		/**
		 Returns the radius of this bounding sphere.

		 @return		The radius of this bounding sphere.
		 */
		[[nodiscard]] F32 Radius() const noexcept {
			return XMVectorGetW(m_pr);
		}

		//---------------------------------------------------------------------
		// Member Methods: Enclosing = Full Coverage
		//---------------------------------------------------------------------

		/**
		 Checks whether this bounding sphere completely encloses the given 
		 point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this bounding sphere completely encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding sphere.
		 */
		[[nodiscard]] bool Encloses(const Point3 &point) const noexcept {
			return Encloses(XMLoad(point));
		}

		/**
		 Checks whether this bounding sphere completely, strictly encloses the 
		 given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this bounding sphere completely, strictly 
						encloses @a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding sphere.
		 */
		[[nodiscard]] bool EnclosesStrict(const Point3 &point) const noexcept {
			return EnclosesStrict(XMLoad(point));
		}

		/**
		 Checks whether this bounding sphere completely encloses the given 
		 point.

		 @param[in]		point
						The point.
		 @return		@c true if this bounding sphere completely encloses
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding sphere.
		 */
		[[nodiscard]] bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept {
			const auto length = XMVector3Length(point - m_pr);
			return XMVectorGetX(length) <= Radius();
		}

		/**
		 Checks whether this bounding sphere completely, strictly encloses the 
		 given point.

		 @param[in]		point
						The point.
		 @return		@c true if this bounding sphere completely, strictly 
						encloses @a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding sphere.
		 */
		[[nodiscard]] bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept {
			const auto length = XMVector3Length(point - m_pr);
			return XMVectorGetX(length) < Radius();
		}

		/**
		 Checks whether this bounding sphere completely encloses the given 
		 AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this bounding sphere completely encloses 
						@a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						a bounding sphere.
		 */
		[[nodiscard]] bool Encloses(const AABB &aabb) const noexcept;

		/**
		 Checks whether this bounding sphere completely, strictly encloses the 
		 given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this bounding sphere completely, strictly 
						encloses @a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						a bounding sphere.
		 */
		[[nodiscard]] bool EnclosesStrict(const AABB &aabb) const noexcept;

		/**
		 Checks whether this bounding sphere completely encloses the given 
		 bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this bounding sphere completely encloses 
						@a sphere. @c false otherwise.
		 @note			This is a full coverage test of a bounding sphere with 
						regard to a bounding sphere.
		 */
		[[nodiscard]] bool Encloses(const BoundingSphere &sphere) const noexcept;

		/**
		 Checks whether this bounding sphere completely, strictly encloses the 
		 given bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this bounding sphere completely, strictly 
						encloses @a sphere. @c false otherwise.
		 @note			This is a full coverage test of a bounding sphere with 
						regard to a bounding sphere.
		 */
		[[nodiscard]] bool EnclosesStrict(const BoundingSphere &sphere) const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Operators
		//---------------------------------------------------------------------

		/**
		 Checks whether the given bounding sphere is equal to this bounding 
		 sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if the given bounding sphere is equal to this 
						bounding sphere. @c false otherwise.
		 */
		[[nodiscard]] bool operator==(const BoundingSphere &sphere) const noexcept {
			return XMVector4Equal(m_pr, sphere.m_pr);
		}

		/**
		 Checks whether the given bounding sphere is not equal to this bounding 
		 sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if the given bounding sphere is equal to this 
						bounding sphere. @c false otherwise.
		 */
		[[nodiscard]] bool operator!=(const BoundingSphere &sphere) const noexcept {
			return !(*this == sphere);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position and radus of this bounding sphere.
		 */
		XMVECTOR m_pr;
	};

	static_assert(16 == sizeof(BoundingSphere));

	#pragma endregion

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of Axis-Aligned Bounding Boxes (AABBs).
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
		[[nodiscard]] static const AABB XM_CALLCONV 
			Union(const AABB &aabb, const Point3 &point) noexcept {

			return Union(aabb, XMLoad(point));
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
		[[nodiscard]] static const AABB XM_CALLCONV 
			Union(const AABB &aabb, const VertexT &vertex) noexcept {

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
		[[nodiscard]] static const AABB XM_CALLCONV 
			Union(const AABB &aabb, FXMVECTOR point) noexcept {

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
		[[nodiscard]] static const AABB XM_CALLCONV 
			Union(const AABB &aabb1, const AABB &aabb2) noexcept {

			const auto p_min = XMVectorMin(aabb1.m_min, aabb2.m_min);
			const auto p_max = XMVectorMax(aabb1.m_max, aabb2.m_max);
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
		[[nodiscard]] static const AABB XM_CALLCONV 
			Overlap(const AABB &aabb1, const AABB &aabb2) noexcept {

			const auto p_min = XMVectorMax(aabb1.m_min, aabb2.m_min);
			const auto p_max = XMVectorMin(aabb1.m_max, aabb2.m_max);
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
		[[nodiscard]] static const AABB XM_CALLCONV 
			OverlapStrict(const AABB &aabb1, const AABB &aabb2) noexcept {

			const auto p_min = XMVectorMax(aabb1.m_min, aabb2.m_min);
			const auto p_max = XMVectorMin(aabb1.m_max, aabb2.m_max);
			return aabb1.OverlapsStrict(aabb2) ? AABB(p_min, p_max) : AABB();
		}
	
		/**
		 Returns the minimum AABB (i.e. the AABB that is variant for union 
		 operations).

		 @return		The minimum AABB.
		 */
		[[nodiscard]] static const AABB XM_CALLCONV Minimum() noexcept {
			return AABB();
		}

		/**
		 Returns the maximum AABB (i.e. the AABB that is invariant for union 
		 operations).

		 @return		The maximum AABB.
		 */
		[[nodiscard]] static const AABB XM_CALLCONV Maximum() noexcept {
			return AABB(-g_XMInfinity, g_XMInfinity);
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an AABB.
		 */
		AABB() noexcept 
			: AABB(g_XMInfinity, -g_XMInfinity) {}

		/**
		 Constructs an AABB of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit AABB(const Point3 &p) noexcept
			: AABB(XMLoad(p)) {}

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
			: AABB(XMLoad(p_min), XMLoad(p_max)) {}

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
		 Constructs an AABB of the given bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 */
		explicit AABB(const BoundingSphere &sphere) noexcept;

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
		[[nodiscard]] const XMVECTOR XM_CALLCONV MinPoint() const noexcept {
			return m_min;
		}

		/**
		 Returns the maximum point of this AABB.
 
		 @return		The maximum point of this AABB.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV MaxPoint() const noexcept {
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
			                                       XMVECTOR &pmin, 
			                                       XMVECTOR &pmax) const noexcept {
			
			const auto control = XMVectorGreaterOrEqual(n, XMVectorZero());
			pmin = XMVectorSelect(m_max, m_min, control);
			pmax = XMVectorSelect(m_min, m_max, control);
		}

		/**
		 Returns the minimum point of this AABB along a given normal.

		 @param[in]		n
						The normal.
		 @return		The minimum point of this AABB along @a n.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV 
			MinPointAlongNormal(FXMVECTOR n) const noexcept {

			const auto control = XMVectorGreaterOrEqual(n, XMVectorZero());
			return XMVectorSelect(m_max, m_min, control);
		}

		/**
		 Returns the maximum point of this AABB along a given normal.

		 @param[in]		n
						The normal.
		 @return		The minimum point of this AABB along @a n.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV 
			MaxPointAlongNormal(FXMVECTOR n) const noexcept {

			const auto control = XMVectorGreaterOrEqual(n, XMVectorZero());
			return XMVectorSelect(m_min, m_max, control);
		}

		/**
		 Returns the centroid of this AABB.
 
		 @return		The centroid of this AABB.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV Centroid() const noexcept {
			return 0.5f * (m_min + m_max);
		}

		/**
		 Returns the radius of this AABB.

		 @return		The radius of this AABB.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV Radius() const noexcept {
			return 0.5f * Diagonal();
		}

		/**
		 Returns the diagonal of this AABB.

		 @return		The diagonal of this AABB.
		 */
		[[nodiscard]] const XMVECTOR XM_CALLCONV Diagonal() const noexcept {
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
		[[nodiscard]] bool Encloses(const Point3 &point) const noexcept {
			return Encloses(XMLoad(point));
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
		[[nodiscard]] bool EnclosesStrict(const Point3 &point) const noexcept {
			return EnclosesStrict(XMLoad(point));
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
		[[nodiscard]] bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept {
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
		[[nodiscard]] bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept {
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
		[[nodiscard]] bool Encloses(const AABB &aabb) const noexcept {
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
		[[nodiscard]] bool EnclosesStrict(const AABB &aabb) const noexcept {
			if (!EnclosesStrict(aabb.m_min)) {
				return false;
			}
			if (!EnclosesStrict(aabb.m_max)) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB completely encloses the given bounding 
		 sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this AABB completely encloses @a sphere.
						@c false otherwise.
		 @note			This is a full coverage test of a bounding sphere with 
						regard to an AABB.
		 */
		[[nodiscard]] bool Encloses(const BoundingSphere &sphere) const noexcept;

		/**
		 Checks whether this AABB completely, strictly encloses the given 
		 bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this AABB completely, strictly encloses 
						@a sphere. @c false otherwise.
		 @note			This is a full coverage test of a bounding sphere with 
						regard to an AABB.
		 */
		[[nodiscard]] bool EnclosesStrict(const BoundingSphere &sphere) const noexcept;

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
		[[nodiscard]] bool Overlaps(const AABB &aabb) const noexcept {
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
		[[nodiscard]] bool OverlapsStrict(const AABB &aabb) const noexcept {
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
		 Checks whether this AABB overlaps the given bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this AABB overlaps @a sphere.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of a bounding 
						sphere with regard to an AABB.
		 */
		[[nodiscard]] bool Overlaps(const BoundingSphere &sphere) const noexcept;

		/**
		 Checks whether this AABB strictly overlaps the given bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this AABB strictly overlaps @a sphere.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of a bounding 
						sphere with regard to an AABB.
		 */
		[[nodiscard]] bool OverlapsStrict(const BoundingSphere &sphere) const noexcept;

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
		[[nodiscard]] bool operator==(const AABB &aabb) const noexcept {
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
		[[nodiscard]] bool operator!=(const AABB &aabb) const noexcept {
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

	static_assert(32 == sizeof(AABB));

	/**
	 A class of Axis-Aligned Bounding Boxes (AABBs).
	 */
	using AxisAlignedBoundingBox = AABB;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Bounding Frustum
	//-------------------------------------------------------------------------
	#pragma region

	#pragma warning( push )
	#pragma warning( disable : 4201 ) // Anonymous struct.

	/**
	 A class of bounding frustums.
	 */
	class alignas(16) BoundingFrustum final {

	public:

		/**
		 Checks if the given bounding volume is culled by the bounding frustum 
		 constructed from the given object-to-projection transformation matrix.

		 @tparam		BoundingVolumeT
						The bounding volume type.
		 @param[in]		object_to_projection
						The object-to-projection transformation matrix.
		 @param[in]		volume
						A reference to the bounding volume.
		 @return		@c true if the given bounding volume is culled by the 
						bounding frustum constructed from the given 
						object-to-projection transformation matrix. @c false 
						otherwise.
		 */
		template< typename BoundingVolumeT >
		[[nodiscard]] static bool XM_CALLCONV 
			Cull(FXMMATRIX object_to_projection,
			     const BoundingVolumeT &volume) noexcept {

			const BoundingFrustum frustum(object_to_projection);
			return !frustum.Overlaps(volume);
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------
		
		/**
		 Constructs a bounding frustum from the given transform.
		 
		 If the given transform represents the view-to-projection 
		 transformation matrix, the planes of the bounding frustum are 
		 represented by view space coordinates.

		 If the given transform represents the world-to-view-to-projection 
		 transformation matrix, the planes of the bounding frustum are 
		 represented by world space coordinates.

		 If the given transform represents the object-to-world-to-view-projection 
		 transformation matrix, the planes of the bounding frustum are 
		 represented by object space coordinates.

		 @param[in]		transform
						The transform.
		 */
		explicit BoundingFrustum(CXMMATRIX transform) noexcept;

		/**
		 Constructs a bounding frustum from the given bounding frustum.

		 @param[in]		frustum
						A reference to the bounding frustum to copy.
		 */
		BoundingFrustum(const BoundingFrustum &frustum) noexcept = default;

		/**
		 Constructs a bounding frustum by moving the given bounding frustum.

		 @param[in]		frustum
						A reference to the bounding frustum to move.
		 */
		BoundingFrustum(BoundingFrustum &&frustum) noexcept = default;

		/**
		 Destructs this bounding frustum.
		 */
		~BoundingFrustum() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given bounding frustum to this bounding frustum.

		 @param[in]		frustum
						A reference to the bounding frustum to copy.
		 @return		A reference to the copy of the given bounding frustum 
						(i.e. this bounding frustum).
		 */
		BoundingFrustum &operator=(const BoundingFrustum &frustum) noexcept = default;

		/**
		 Moves the given bounding frustum to this bounding frustum.

		 @param[in]		frustum
						A reference to the bounding frustum to move.
		 @return		A reference to the moved bounding frustum (i.e. this 
						bounding frustum).
		 */
		BoundingFrustum &operator=(BoundingFrustum &&frustum) noexcept = default;
		
		//---------------------------------------------------------------------
		// Member Methods: Enclosing = Full Coverage
		//---------------------------------------------------------------------
		
		/**
		 Checks whether this bounding frustum completely encloses the given 
		 point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this bounding frustum completely encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding frustum.
		 */
		[[nodiscard]] bool Encloses(const Point3 &point) const noexcept {
			return Encloses(XMLoad(point));
		}

		/**
		 Checks whether this bounding frustum completely, strictly encloses the 
		 given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this bounding frustum completely, strictly 
						encloses @a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding frustum.
		 */
		[[nodiscard]] bool EnclosesStrict(const Point3 &point) const noexcept {
			return EnclosesStrict(XMLoad(point));
		}

		/**
		 Checks whether this bounding frustum completely encloses the given 
		 point.

		 @param[in]		point
						The point.
		 @return		@c true if this bounding frustum completely encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding frustum.
		 */
		[[nodiscard]] bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept;

		/**
		 Checks whether this bounding frustum completely, strictly encloses the 
		 given point.

		 @param[in]		point
						The point.
		 @return		@c true if this bounding frustum completely, strictly 
						encloses @a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a bounding frustum.
		 */
		[[nodiscard]] bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept;

		/**
		 Checks whether this bounding frustum completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this bounding frustum completely encloses 
						@a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						a bounding frustum.
		 */
		[[nodiscard]] bool Encloses(const AABB &aabb) const noexcept;

		/**
		 Checks whether this bounding frustum completely, strictly encloses the 
		 given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this bounding frustum completely, strictly 
						encloses @a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						a bounding frustum.
		 */
		[[nodiscard]] bool EnclosesStrict(const AABB &aabb) const noexcept;

		/**
		 Checks whether this bounding frustum completely encloses the given 
		 bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this bounding frustum completely encloses 
						@a sphere.
						@c false otherwise.
		 @note			This is a full coverage test of a bounding sphere with 
						regard to a bounding frustum.
		 */
		[[nodiscard]] bool Encloses(const BoundingSphere &sphere) const noexcept;

		/**
		 Checks whether this bounding frustum completely, strictly encloses the 
		 given bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this bounding frustum completely, strictly 
						encloses @a sphere. @c false otherwise.
		 @note			This is a full coverage test of a bounding sphere with 
						regard to a bounding frustum.
		 */
		[[nodiscard]] bool EnclosesStrict(const BoundingSphere &sphere) const noexcept;
		
		//---------------------------------------------------------------------
		// Member Methods: Overlapping = Partial | Full Coverage
		//---------------------------------------------------------------------
		
		/**
		 Checks whether this bounding frustum overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this bounding frustum overlaps @a aabb.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of an AABB 
						with regard to a bounding frustum.
		 */
		[[nodiscard]] bool Overlaps(const AABB &aabb) const noexcept;

		/**
		 Checks whether this bounding frustum strictly overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this bounding frustum strictly overlaps 
						@a aabb.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of an AABB 
						with regard to a bounding frustum.
		 */
		[[nodiscard]] bool OverlapsStrict(const AABB &aabb) const noexcept;

		/**
		 Checks whether this bounding frustum overlaps the given bounding 
		 sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this bounding frustum overlaps @a sphere.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of a bounding 
						sphere with regard to a bounding frustum.
		 */
		[[nodiscard]] bool Overlaps(const BoundingSphere &sphere) const noexcept;

		/**
		 Checks whether this bounding frustum strictly overlaps the given 
		 bounding sphere.

		 @param[in]		sphere
						A reference to the bounding sphere.
		 @return		@c true if this bounding frustum strictly overlaps 
						@a sphere.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of a bounding 
						sphere with regard to a bounding frustum.
		 */
		[[nodiscard]] bool OverlapsStrict(const BoundingSphere &sphere) const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Operators
		//---------------------------------------------------------------------

		/**
		 Checks whether the given bounding frustum is equal to this bounding 
		 frustum.

		 @param[in]		frustum
						A reference to the bounding frustum.
		 @return		@c true if the given bounding frustum is equal to this 
						bounding frustum. @c false otherwise.
		 */
		[[nodiscard]] bool operator==(const BoundingFrustum &frustum) const noexcept;

		/**
		 Checks whether the given bounding frustum is not equal to this 
		 bounding frustum.

		 @param[in]		frustum
						A reference to the bounding frustum.
		 @return		@c true if the given bounding frustum is equal to this 
						bounding frustum. @c false otherwise.
		 */
		[[nodiscard]] bool operator!=(const BoundingFrustum &frustum) const noexcept {
			return !(*this == frustum);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		union {
			
			struct {

				/**
				 The left plane of this bounding frustum.
				 */
				XMVECTOR m_left_plane;

				/**
				 The right plane of this bounding frustum.
				 */
				XMVECTOR m_right_plane;

				/**
				 The bottom plane of this bounding frustum.
				 */
				XMVECTOR m_bottom_plane;

				/**
				 The top plane of this bounding frustum.
				 */
				XMVECTOR m_top_plane;

				/**
				 The near plane of this bounding frustum.
				 */
				XMVECTOR m_near_plane;

				/**
				 The far plane of this bounding frustum.
				 */
				XMVECTOR m_far_plane;
			};
			
			/**
			 The six planes of this bounding frustum. 
			 */
			XMVECTOR m_planes[6];
		};
	};

	static_assert(96 == sizeof(BoundingFrustum));

	#pragma warning( pop )

	#pragma endregion

	//-------------------------------------------------------------------------
	// Coverage
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different coverages for bounding volumes.

	 This contains:
	 @c NoCoverage,
	 @c PartialCoverage and
	 @c FullCoverage.
	 */
	enum class [[nodiscard]] Coverage : U8 {
		NoCoverage,		 // No coverage      (i.e. no overlap)
		PartialCoverage, // Partial coverage (i.e. overlap + not enclosing)
		FullCoverage	 // Full coverage    (i.e. overlap + enclosing)
	};

	/**
     Classifies the second given bounding volume with regard to the first given
	 bounding volume.

	 @tparam		BoundingVolumeT
					The first bounding volume type.
	 @tparam		BoundingVolumeU
					The second bounding volume type.
	 @param[in]		volume1
					A reference to the first bounding volume.
	 @param[in]		volume2
					A reference to the second bounding volume.
     @return		The coverage of @a volume2 with regard to @a volume1.
	 */
	template< typename BoundingVolumeT, typename BoundingVolumeU >
	inline Coverage Classify(const BoundingVolumeT &volume1,
		                     const BoundingVolumeU &volume2) noexcept {

		return volume1.Encloses(volume2) ? Coverage::FullCoverage 
			: (volume1.Overlaps(volume2) ? Coverage::PartialCoverage 
				                         : Coverage::NoCoverage);
	}

	/**
     Classifies the given point with regard to the given bounding volume.

	 @tparam		BoundingVolumeT
					The bounding volume type.
	 @param[in]		volume
					A reference to the bounding volume.
	 @param[in]		point
					The point.
	 @param[in]		epsilon
					The epsilon value.
     @return		The coverage of @a point with regard to @a volume.
	 */
	template< typename BoundingVolumeT >
	inline Coverage XM_CALLCONV Classify(const BoundingVolumeT &volume,
		                                 FXMVECTOR point,
		                                 F32 epsilon) noexcept {

		return Classify(volume, BoundingSphere(point, epsilon));
	}

	/**
     Classifies the given point with regard to the given bounding volume.

	 @tparam		BoundingVolumeT
					The bounding volume type.
	 @param[in]		volume
					A reference to the bounding volume.
	 @param[in]		point
					A reference to the point.
	 @param[in]		epsilon
					The epsilon value.
     @return		The coverage of @a point with regard to @a volume.
	 */
	template< typename BoundingVolumeT >
	inline Coverage Classify(const BoundingVolumeT &volume,
		                     const Point3 &point,
		                     F32 epsilon) noexcept {

		return Classify(volume, XMLoad(point), epsilon);
	}

	#pragma endregion
}