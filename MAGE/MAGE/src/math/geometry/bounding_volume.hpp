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
		NoCoverage,		 // No coverage (i.e. no overlap)
		PartialCoverage, // Partial coverage (i.e. intersection, overlap)
		FullCoverage	 // Full coverage (i.e. enclosing, overlap)
	};

	// Forward declaration
	struct BS;

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box
	//-------------------------------------------------------------------------

	/**
	 A struct of Axis-Aligned Bounding Boxes (AABBs).
	 */
	struct AABB final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an (identity) AABB.
		 */
		AABB() 
			: m_p_min( std::numeric_limits< float >::infinity(),
				       std::numeric_limits< float >::infinity(),
				       std::numeric_limits< float >::infinity()),
			  m_p_max(-std::numeric_limits< float >::infinity(),
				      -std::numeric_limits< float >::infinity(),
				      -std::numeric_limits< float >::infinity()) {}

		/**
		 Constructs an AABB of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit AABB(const Point3 &p)
			: m_p_min(p), m_p_max(p) {}

		/**
		 Constructs an AABB of the given extents.

		 @pre			@a p_min is entrywise smaller or equal to @a p_max.
		 @param[in]		p_min
						A reference to the minimum extents.
		 @param[in]		p_max
						A reference to the maximum extents.
		 */
		explicit AABB(const Point3 &p_min, const Point3 &p_max)
			: m_p_min(p_min), m_p_max(p_max) {}

		/**
		 Constructs an AABB from the given AABB.

		 @param[in]		aabb
						A reference to the AABB to copy.
		 */
		AABB(const AABB &aabb) = default;

		/**
		 Constructs an AABB by moving the given AABB.

		 @param[in]		aabb
						A reference to the AABB to move.
		 */
		AABB(AABB &&aabb) = default;

		/**
		 Constructs an AABB of the given BS.

		 @param[in]		bs
						A reference to the BS.
		 */
		explicit AABB(const BS &bs);

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
		AABB &operator=(const AABB &aabb) = default;

		/**
		 Moves the given AABB to this AABB.

		 @param[in]		aabb
						A reference to the AABB to move.
		 @return		A reference to the moved AABB (i.e. this AABB).
		 */
		AABB &operator=(AABB &&aabb) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the centroid of this AABB.
 
		 @return		The centroid of this AABB.
		 */
		const Point3 Centroid() const noexcept;

		/**
		 Returns the radius of this AABB.

		 @return		The radius of this AABB.
		 */
		const Direction3 Radius() const noexcept;

		/**
		 Returns the diagonal of this AABB.

		 @return		The diagonal of this AABB.
		 */
		const Direction3 Diagonal() const noexcept;

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
		bool Encloses(const Point3 &point) const noexcept;

		/**
		 Checks whether this AABB completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool EnclosesStrict(const Point3 &point) const noexcept;

		/**
		 Checks whether this AABB completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely encloses @a point.
						@c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept;

		/**
		 Checks whether this AABB completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						an AABB.
		 */
		bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept;

		/**
		 Checks whether this AABB completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely encloses @a aabb.
						@c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						an AABB.
		 */
		bool Encloses(const AABB &aabb) const noexcept;

		/**
		 Checks whether this AABB completely, strictly encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely, strictly encloses 
						@a aabb. @c false otherwise.
		 @note			This is a full coverage test of an AABB with regard to 
						an AABB.
		 */
		bool EnclosesStrict(const AABB &aabb) const noexcept;

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
		bool Overlaps(const AABB &aabb) const noexcept;

		/**
		 Checks whether this AABB strictly overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB strictly overlaps @a aabb.
						@c false otherwise.
		 @note			This is a (partial or full) coverage test of an AABB 
						with regard to an AABB.
		 */
		bool OverlapsStrict(const AABB &aabb) const noexcept;

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
		// Member Methods: Intersecting = Partial Coverage
		//---------------------------------------------------------------------

		/**
		 Checks whether this AABB intersects the given point.

		 @param[in]		point
						A reference to the point.
		 @param[in]		epsilon
						The epsilon value for F32 comparisons.
		 @return		@c true if this AABB intersects @a point. @c false 
						otherwise.
		 @note			This is a partial coverage test of a point with regard 
						to an AABB.
		 */
		bool Intersects(const Point3 &point, 
			F32 epsilon = 0.0f) const noexcept;

		/**
		 Checks whether this AABB intersects the given point.

		 @param[in]		point
						The point.
		 @param[in]		epsilon
						The epsilon value for F32 comparisons.
		 @return		@c true if this AABB intersects @a point. @c false
						otherwise.
		 @note			This is a partial coverage test of a point with regard 
						to an AABB.
		 */
		bool XM_CALLCONV Intersects(FXMVECTOR point,
			F32 epsilon = 0.0f) const noexcept;

		/**
		 Checks whether this AABB intersects the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB intersects @a aabb. @c false 
						otherwise.
		 @note			This is a partial coverage test of an AABB with regard 
						to an AABB.
		 */
		bool Intersects(const AABB &aabb) const noexcept;

		/**
		 Checks whether this AABB intersects the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB intersects @a bs. @c false 
						otherwise.
		 @note			This is a partial coverage test of a BS with regard to 
						an AABB.
		 */
		bool Intersects(const BS &bs) const noexcept;

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
			F32 epsilon = 0.0f) const noexcept;

		/**
		 Classifies the coverage of the given point with regard to this AABB.

		 @param[in]		point
						The point.
		 @param[in]		epsilon
						The epsilon value for F32 comparisons.
		 @return		The coverage of @a point with regard to this AABB.
		 */
		Coverage XM_CALLCONV Classify(FXMVECTOR point,
			F32 epsilon = 0.0f) const noexcept;

		/**
		 Classifies the coverage of the given AABB with regard to this AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		The coverage of @a aabb with regard to this AABB.
		 */
		Coverage Classify(const AABB &aabb) const noexcept;
		
		/**
		 Classifies the coverage of the given BS with regard to this AABB.

		 @param[in]		bs
						A reference to the BS.
		 @return		The coverage of @a bs with regard to this AABB.
		 */
		Coverage Classify(const BS &bs) const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The minimum extents of this AABB.
		 */
		Point3 m_p_min;

		/**
		 The maximum extents of this AABB.
		 */
		Point3 m_p_max;
	};

	//-------------------------------------------------------------------------
	// Axis-Aligned Bounding Box: Non-Members
	//-------------------------------------------------------------------------

	/**
	 Returns the union AABB of the given AABB and the given point.

	 @param[in]		aabb
					A reference to the AABB.
	 @param[in]		point
					A reference to the point.
	 @return		The union AABB of @a aabb and @a point.
	 */
	const AABB Union(const AABB &aabb, const Point3 &point) noexcept;

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
	inline const AABB Union(const AABB &aabb, const VertexT &vertex) noexcept {
		return Union(aabb, vertex.p);
	}
	
	/**
	 Returns the union AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The union AABB of @a aabb1 and @a aabb2.
	 */
	const AABB Union(const AABB &aabb1, const AABB &aabb2) noexcept;
	
	/**
	 Returns the overlap AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The identity AABB in case of no overlap.
	 @return		The overlap AABB of @a aabb1 and @a aabb2.
	 */
	const AABB Overlap(const AABB &aabb1, const AABB &aabb2) noexcept;
	
	/**
	 Returns the strict overlap AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The identity AABB in case of no strict overlap.
	 @return		The strict overlap AABB of @a aabb1 and @a aabb2.
	 */
	const AABB OverlapStrict(const AABB &aabb1, const AABB &aabb2) noexcept;
	
	/**
	 Returns the minimum AABB (i.e. variant for union operations).

	 @return		The minimum AABB.
	 */
	inline const AABB MinimumAABB() noexcept {
		return AABB();
	}

	/**
	 Returns the maximum AABB (i.e. invariant for union operations).

	 @return		The maximum AABB.
	 */
	inline const AABB MaximumAABB() noexcept {
		return AABB(Point3(-std::numeric_limits< float >::infinity(), 
			               -std::numeric_limits< float >::infinity(), 
			               -std::numeric_limits< float >::infinity()),
					Point3( std::numeric_limits< float >::infinity(), 
						    std::numeric_limits< float >::infinity(), 
						    std::numeric_limits< float >::infinity()));
	}

	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------

	/**
	 A struct of Bounding Spheres (BS).
	 */
	struct BS final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a BS.
		 */
		BS() 
			: m_p(), m_r(0.0f) {}

		/**
		 Constructs a BS of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit BS(const Point3 &p)
			: m_p(p), m_r(0.0f) {}

		/**
		 Constructs a BS.

		 @param[in]		p
						A reference to the position.
		 @param[in]		r
						The radius.
		 */
		explicit BS(const Point3 &p, F32 r)
			: m_p(p), m_r(r) {}

		/**
		 Constructs a BS from the given AABB.

		 @param[in]		aabb
						A reference to the aabb.
		 */
		explicit BS(const AABB &aabb);

		/**
		 Constructs a BS from the given BS.

		 @param[in]		bs
						A reference to the bs.
		 */
		BS(const BS &bs) = default;

		/**
		 Constructs a BS from the given BS.

		 @param[in]		bs
						A reference to the bs.
		 */
		BS(BS &&bs) = default;

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
		BS &operator=(const BS &bs) = default;

		/**
		 Copies the given BS to this BS.

		 @param[in]		bs
						A reference to the BS to copy from.
		 @return		A reference to the copy of the given BS (i.e. this BS).
		 */
		BS &operator=(BS &&bs) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the centroid of this AABB.

		 @return		The centroid of this AABB.
		 */
		const Point3 Centroid() const noexcept {
			return m_p;
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
		bool Encloses(const Point3 &point) const noexcept;

		/**
		 Checks whether this BS completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this BS completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool EnclosesStrict(const Point3 &point) const noexcept;

		/**
		 Checks whether this BS completely encloses the given point.

		 @param[in]		point
						The point.
		 @return		@c true if this BS completely encloses
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool XM_CALLCONV Encloses(FXMVECTOR point) const noexcept;

		/**
		 Checks whether this BS completely, strictly encloses the given point.

		 @param[in]		point
						The point.
		 @return		@c true if this BS completely, strictly encloses 
						@a point. @c false otherwise.
		 @note			This is a full coverage test of a point with regard to 
						a BS.
		 */
		bool XM_CALLCONV EnclosesStrict(FXMVECTOR point) const noexcept;

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
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of this BS.
		 */
		Point3 m_p;

		/**
		 The radius of this BS.
		 */
		F32 m_r;
	};

	//-------------------------------------------------------------------------
	// Bounding Sphere: Non-Members
	//-------------------------------------------------------------------------

	/**
	 Returns the union BS of the given BS and the given point.

	 @param[in]		bs
					A reference to the BS.
	 @param[in]		point
					A reference to the point.
	 @return		The union BS of @a bs and @a point.
	 */
	const BS Union(const BS &bs, const Point3 &point) noexcept;

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
	inline const BS Union(const BS &bs, const VertexT &vertex) noexcept {
		return Union(bs, vertex.p);
	}

	/**
	 Returns the maximum BS (i.e. invariant for union operations).

	 @return		The maximum BS.
	 */
	inline const BS MaximumBS() noexcept {
		return BS(Point3(), std::numeric_limits< float >::infinity());
	}
}