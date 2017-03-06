#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

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

		/**
		 Constructs an (identity) AABB.
		 */
		AABB() 
			: p_min(Point3(-INFINITY, -INFINITY, -INFINITY)), p_max(Point3(INFINITY, INFINITY, INFINITY)) {}

		/**
		 Constructs an AABB of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit AABB(const Point3 &p)
			: p_min(p), p_max(p) {}

		/**
		 Constructs an AABB of the given extents.

		 @pre			@a p_min is entrywise smaller or equal to @a p_max.
		 @param[in]		p_min
						A reference to the minimum extents.
		 @param[in]		p_max
						A reference to the maximum extents.
		 */
		AABB(const Point3 &p_min, const Point3 &p_max) 
			: p_min(p_min), p_max(p_max) {}

		/**
		 Constructs an AABB from the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 */
		AABB(const AABB &aabb) = default;

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

		/**
		 Copies the given AABB to this AABB.

		 @param[in]		aabb
						A reference to the AABB to copy from.
		 @return		A reference to the copy of the given AABB
						(i.e. this AABB).
		 */
		AABB &operator=(const AABB &aabb) = default;

		/**
		 Checks whether this AABB completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely encloses @a point.
						@c false otherwise.
		 */
		bool Encloses(const Point3 &point) const;

		/**
		 Checks whether this AABB completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely, strictly encloses @a point.
						@c false otherwise.
		 */
		bool EnclosesStrict(const Point3 &point) const;

		/**
		 Checks whether this AABB completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely encloses @a aabb.
						@c false otherwise.
		 */
		bool Encloses(const AABB &aabb) const;

		/**
		 Checks whether this AABB completely, strictly encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely, strictly encloses @a aabb.
						@c false otherwise.
		 */
		bool EnclosesStrict(const AABB &aabb) const;

		/**
		 Checks whether this AABB completely encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB completely encloses @a bs.
						@c false otherwise.
		 */
		bool Encloses(const BS &bs) const;

		/**
		 Checks whether this AABB completely, strictly encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this AABB completely, strictly encloses @a bs.
						@c false otherwise.
		 */
		bool EnclosesStrict(const BS &bs) const;

		/**
		 Checks whether this AABB is completely enclosed by the given (closed) volume.

		 @param[in]		planes
						A pointer to the planes of the volume.
						(each plane's coefficients are represented as a @c XMFLOAT4)
		 @param[in]		nb_planes
						The number of planes.
		 @return		@c true if this AABB is completely enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedBy(const XMFLOAT4 *planes, size_t nb_planes) const;

		/**
		 Checks whether this AABB is completely, strictly enclosed by the given (closed) volume.

		 @param[in]		planes
						A pointer to the planes of the volume.
						(each plane's coefficients are represented as a @c XMFLOAT4)
		 @param[in]		nb_planes
						The number of planes.
		 @return		@c true if this AABB is completely, stricly enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedStrictBy(const XMFLOAT4 *planes, size_t nb_planes) const;

		/**
		 Checks whether this AABB overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB overlaps @a aabb.
						@c false otherwise.
		 */
		bool Overlaps(const AABB &aabb) const;

		/**
		 Checks whether this AABB strictly overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB strictly overlaps @a aabb.
						@c false otherwise.
		 */
		bool OverlapsStrict(const AABB &aabb) const;

		/**
		 Returns the centroid of this AABB.

		 @return		The centroid of this AABB.
		 */
		Point3 Centroid() const;

		/**
		 Returns the diagonal of this AABB.

		 @return		The diagonal of this AABB.
		 */
		Direction3 Diagonal() const;

		/**
		 The minimum extents of this AABB.
		 */
		Point3 p_min;

		/**
		 The maximum extents of this AABB.
		 */
		Point3 p_max;
	};

	/**
	 Returns the union AABB of the given AABB and the given point.

	 @param[in]		aabb
					A reference to the AABB.
	 @param[in]		point
					A reference to the point.
	 @return		The union AABB of @a aabb and @a point.
	 */
	AABB Union(const AABB &aabb, const Point3 &point);
	
	/**
	 Returns the union AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The union AABB of @a aabb1 and @a aabb2.
	 */
	AABB Union(const AABB &aabb1, const AABB &aabb2);
	
	/**
	 Returns the overlap AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The identity AABB in case of no overlap.
	 @return		The overlap AABB of @a aabb1 and @a aabb2.
	 */
	AABB Overlap(const AABB &aabb1, const AABB &aabb2);
	
	/**
	 Returns the strict overlap AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The identity AABB in case of no strict overlap.
	 @return		The strict overlap AABB of @a aabb1 and @a aabb2.
	 */
	AABB OverlapStrict(const AABB &aabb1, const AABB &aabb2);

	//-------------------------------------------------------------------------
	// Bounding Sphere
	//-------------------------------------------------------------------------

	/**
	 A struct of Bounding Spheres (BS).
	 */
	struct BS final {

	public:

		/**
		 Constructs a BS.
		 */
		BS() 
			: p(Point3(0.0f, 0.0f, 0.0f)), r(0.0f) {}

		/**
		 Constructs a BS of the given point.

		 @param[in]		p
						A reference to the point.
		 */
		explicit BS(const Point3 &p)
			: p(p), r(0.0f) {}

		/**
		 Constructs a BS.

		 @param[in]		p
						A reference to the position.
		 @param[in]		r
						The radius.
		 */
		BS(const Point3 &p, float r) 
			: p(p), r(r) {}

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
		 Destructs this BS.
		 */
		~BS() = default;

		/**
		 Copies the given BS to this BS.

		 @param[in]		bs
						A reference to the BS to copy from.
		 @return		A reference to the copy of the given BS
						(i.e. this BS).
		 */
		BS &operator=(const BS &bs) = default;

		/**
		 Checks whether this BS completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this BS completely encloses @a point.
						@c false otherwise.
		 */
		bool Encloses(const Point3 &point) const;

		/**
		 Checks whether this BS completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this BS completely, strictly encloses @a point.
						@c false otherwise.
		 */
		bool EnclosesStrict(const Point3 &point) const;

		/**
		 Checks whether this BS completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this BS completely encloses @a aabb.
						@c false otherwise.
		 */
		bool Encloses(const AABB &aabb) const;

		/**
		 Checks whether this BS completely, strictly encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this BS completely, strictly encloses @a aabb.
						@c false otherwise.
		 */
		bool EnclosesStrict(const AABB &aabb) const;

		/**
		 Checks whether this BS completely encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this BS completely encloses @a bs.
						@c false otherwise.
		 */
		bool Encloses(const BS &bs) const;

		/**
		 Checks whether this BS completely, strictly encloses the given BS.

		 @param[in]		bs
						A reference to the BS.
		 @return		@c true if this BS completely, strictly encloses @a bs.
						@c false otherwise.
		 */
		bool EnclosesStrict(const BS &bs) const;

		/**
		 Checks whether this BS completely encloses the given (closed) volume.

		 @param[in]		planes
						A pointer to the planes of the volume.
						(each plane's coefficients are represented as a @c XMFLOAT4)
		 @param[in]		nb_planes
						The number of planes.
		 @return		@c true if this BS completely encloses @a planes.
						@c false otherwise.
		 */
		bool EnclosedBy(const XMFLOAT4 *planes, size_t nb_planes) const;

		/**
		 Checks whether this BS completely, strictly encloses the given (closed) volume.

		 @param[in]		planes
						A pointer to the planes of the volume.
						(each plane's coefficients are represented as a @c XMFLOAT4)
		 @param[in]		nb_planes
						The number of planes.
		 @return		@c true if this BS completely, stricly encloses @a planes.
						@c false otherwise.
		 */
		bool EnclosedStrictBy(const XMFLOAT4 *planes, size_t nb_planes) const;

		/**
		 Returns the centroid of this AABB.

		 @return		The centroid of this AABB.
		 */
		Point3 Centroid() const {
			return p;
		}

		/**
		 The position of this BS.
		 */
		Point3 p;

		/**
		 The radius of this BS.
		 */
		float r;
	};
}