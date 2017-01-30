#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\vertex.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

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
		 Constructs an AABB.

		 @param[in]		p_min
						The minimum extents.
		 @param[in]		p_max
						The maximum extents.
		 */
		AABB(const Point3 &p_min, const Point3 &p_max) 
			: p_min(p_min), p_max(p_max) {}

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
		 Checks whether this AABB completely encloses the given face.

		 @param[in]		face
						A reference to the face.
		 @return		@c true if this AABB completely encloses @a face.
						@c false otherwise.
		 */
		bool Encloses(const Face &face) const;

		/**
		 Checks whether this AABB completely, strictly encloses the given face.

		 @param[in]		face
						A reference to the face.
		 @return		@c true if this AABB completely, strictly encloses @a face.
						@c false otherwise.
		 */
		bool EnclosesStrict(const Face &face) const;

		/**
		 Checks whether this AABB is completely enclosed by the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this AABB is completely enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedBy(const list< XMFLOAT4 > &planes) const;

		/**
		 Checks whether this AABB is completely, strictly enclosed by the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this AABB is completely, stricly enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedStrictBy(const list< XMFLOAT4 > &planes) const;

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

	/**
	 A struct of Bounding Spheres (BS).
	 */
	struct BS final {

	public:

		/**
		 Constructs a sphere.
		 */
		BS() 
			: p(Point3(0.0f, 0.0f, 0.0f)), r(1.0f) {}

		/**
		 Constructs a sphere.

		 @param[in]		p
						The position
		 @param[in]		r
						The radius.
		 */
		BS(const Point3 &p, float r) 
			: p(p), r(r) {}

		/**
		 Checks whether this sphere completely encloses the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this sphere completely encloses @a planes.
						@c false otherwise.
		*/
		bool Encloses(const list< XMFLOAT4 > &planes) const;

		/**
		 Checks whether this sphere completely, strictly encloses the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this sphere completely encloses @a planes.
						@c false otherwise.
		 */
		bool EnclosesStrict(const list< XMFLOAT4 > &planes) const;

		/**
		 Checks whether this sphere collides with a given sphere.

		 @param[in]		sphere
						The sphere.
		 @param[in]		velocity_sum
						The sum of the velocities of both spheres.
		 @param[out]	collision_distance
						The collision distance (in case of collision).
		 @return		@c true if this sphere collides with @a sphere.
						@c false otherwise.
		 */
		bool Collides(const BS &sphere, const XMFLOAT3 velocity_sum, float *collision_distance) const;

		/**
		 The position of this sphere.
		 */
		Point3 p;

		/**
		 The radius of this sphere.
		 */
		float r;
	};
}