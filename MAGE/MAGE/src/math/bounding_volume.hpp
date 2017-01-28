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
			: p_min(XMFLOAT3(-INFINITY, -INFINITY, -INFINITY)), p_max(XMFLOAT3(INFINITY, INFINITY, INFINITY)) {}

		/**
		 Constructs an AABB.

		 @param[in]		p_min
						The minimum extents.
		 @param[in]		p_max
						The maximum extents.
		 */
		AABB(const XMFLOAT3 &p_min, const XMFLOAT3 &p_max) 
			: p_min(p_min), p_max(p_max) {}

		/**
		 Checks whether this AABB completely encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely encloses @a aabb.
						@c false otherwise.
		 */
		bool Encloses(const AABB &aabb) const {
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

		/**
		 Checks whether this AABB completely, strictly encloses the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB completely, strictly encloses @a aabb.
						@c false otherwise.
		 */
		bool EnclosesStrict(const AABB &aabb) const {
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

		/**
		 Checks whether this AABB completely encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely encloses @a point.
						@c false otherwise.
		 */
		bool Encloses(const XMFLOAT3 &point) const {
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

		/**
		 Checks whether this AABB completely, strictly encloses the given point.

		 @param[in]		point
						A reference to the point.
		 @return		@c true if this AABB completely, strictly encloses @a point.
						@c false otherwise.
		 */
		bool EnclosesStrict(const XMFLOAT3 &point) const {
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

		/**
		 Checks whether this AABB completely encloses the given face.

		 @param[in]		face
						A reference to the face.
		 @return		@c true if this AABB completely encloses @a face.
						@c false otherwise.
		 */
		bool Encloses(const Face &face) const {
			// Find the minimum and maximum points of the face along the x axis. 
			// Then check if these two points are within this AABB's x axis extents.
			const float min_x = min(face.v0->p.x, min(face.v1->p.x, face.v2->p.x));
			const float max_x = max(face.v0->p.x, max(face.v1->p.x, face.v2->p.x));
			if (max_x < p_min.x) {
				return false;
			}
			if (min_x > p_max.x) {
				return false;
			}

			// Find the minimum and maximum points of the face along the y axis. 
			// Then check if these two points are within this AABB's y axis extents.
			const float min_y = min(face.v0->p.y, min(face.v1->p.y, face.v2->p.y));
			const float max_y = max(face.v0->p.y, max(face.v1->p.y, face.v2->p.y));
			if (max_y < p_min.y) {
				return false;
			}
			if (min_y > p_max.y) {
				return false;
			}

			// Find the minimum and maximum points of the face along the z axis. 
			// Then check if these two points are within this AABB's z axis extents.
			const float min_z = min(face.v0->p.z, min(face.v1->p.z, face.v2->p.z));
			const float max_z = max(face.v0->p.z, max(face.v1->p.z, face.v2->p.z));
			if (max_z < p_min.z) {
				return false;
			}
			if (min_z > p_max.z) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB completely, strictly encloses the given face.

		 @param[in]		face
						A reference to the face.
		 @return		@c true if this AABB completely, strictly encloses @a face.
						@c false otherwise.
		 */
		bool EnclosesStrict(const Face &face) const {
			// Find the minimum and maximum points of the face along the x axis. 
			// Then check if these two points are within this AABB's x axis extents.
			const float min_x = min(face.v0->p.x, min(face.v1->p.x, face.v2->p.x));
			const float max_x = max(face.v0->p.x, max(face.v1->p.x, face.v2->p.x));
			if (max_x <= p_min.x) {
				return false;
			}
			if (min_x >= p_max.x) {
				return false;
			}

			// Find the minimum and maximum points of the face along the y axis. 
			// Then check if these two points are within this AABB's y axis extents.
			const float min_y = min(face.v0->p.y, min(face.v1->p.y, face.v2->p.y));
			const float max_y = max(face.v0->p.y, max(face.v1->p.y, face.v2->p.y));
			if (max_y <= p_min.y) {
				return false;
			}
			if (min_y >= p_max.y) {
				return false;
			}

			// Find the minimum and maximum points of the face along the z axis. 
			// Then check if these two points are within this AABB's z axis extents.
			const float min_z = min(face.v0->p.z, min(face.v1->p.z, face.v2->p.z));
			const float max_z = max(face.v0->p.z, max(face.v1->p.z, face.v2->p.z));
			if (max_z <= p_min.z) {
				return false;
			}
			if (min_z >= p_max.z) {
				return false;
			}

			return true;
		}

		/**
		 Checks whether this AABB is completely enclosed by the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this AABB is completely enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedBy(const list< XMFLOAT4 > &planes) const {
			for (list< XMFLOAT4 >::const_iterator it = planes.cbegin(); it != planes.cend(); ++it) {
				const XMVECTOR point = XMLoadFloat4(&(*it));

				// 000
				const XMFLOAT3 corner_000_f3(p_min.x, p_min.y, p_min.z);
				const XMVECTOR corner_000_v = XMLoadFloat3(&corner_000_f3);
				const XMVECTOR result_000_v = XMPlaneDotCoord(point, corner_000_v);
				float result_000;
				XMStoreFloat(&result_000, result_000_v);
				if (result_000 < 0.0f) {
					return false;
				}

				// 001
				const XMFLOAT3 corner_001_f3(p_min.x, p_min.y, p_max.z);
				const XMVECTOR corner_001_v = XMLoadFloat3(&corner_001_f3);
				const XMVECTOR result_001_v = XMPlaneDotCoord(point, corner_001_v);
				float result_001;
				XMStoreFloat(&result_001, result_001_v);
				if (result_001 < 0.0f) {
					return false;
				}

				// 010
				const XMFLOAT3 corner_010_f3(p_min.x, p_max.y, p_min.z);
				const XMVECTOR corner_010_v = XMLoadFloat3(&corner_010_f3);
				const XMVECTOR result_010_v = XMPlaneDotCoord(point, corner_010_v);
				float result_010;
				XMStoreFloat(&result_010, result_010_v);
				if (result_010 < 0.0f) {
					return false;
				}

				// 011
				const XMFLOAT3 corner_011_f3(p_min.x, p_max.y, p_max.z);
				const XMVECTOR corner_011_v = XMLoadFloat3(&corner_011_f3);
				const XMVECTOR result_011_v = XMPlaneDotCoord(point, corner_011_v);
				float result_011;
				XMStoreFloat(&result_011, result_011_v);
				if (result_011 < 0.0f) {
					return false;
				}

				// 100
				const XMFLOAT3 corner_100_f3(p_max.x, p_min.y, p_min.z);
				const XMVECTOR corner_100_v = XMLoadFloat3(&corner_100_f3);
				const XMVECTOR result_100_v = XMPlaneDotCoord(point, corner_100_v);
				float result_100;
				XMStoreFloat(&result_100, result_100_v);
				if (result_100 < 0.0f) {
					return false;
				}

				// 101
				const XMFLOAT3 corner_101_f3(p_max.x, p_min.y, p_max.z);
				const XMVECTOR corner_101_v = XMLoadFloat3(&corner_101_f3);
				const XMVECTOR result_101_v = XMPlaneDotCoord(point, corner_101_v);
				float result_101;
				XMStoreFloat(&result_101, result_101_v);
				if (result_101 < 0.0f) {
					return false;
				}

				// 110
				const XMFLOAT3 corner_110_f3(p_max.x, p_max.y, p_min.z);
				const XMVECTOR corner_110_v = XMLoadFloat3(&corner_110_f3);
				const XMVECTOR result_110_v = XMPlaneDotCoord(point, corner_110_v);
				float result_110;
				XMStoreFloat(&result_110, result_110_v);
				if (result_110 < 0.0f) {
					return false;
				}

				// 111
				const XMFLOAT3 corner_111_f3(p_max.x, p_max.y, p_max.z);
				const XMVECTOR corner_111_v = XMLoadFloat3(&corner_111_f3);
				const XMVECTOR result_111_v = XMPlaneDotCoord(point, corner_111_v);
				float result_111;
				XMStoreFloat(&result_111, result_111_v);
				if (result_111 < 0.0f) {
					return false;
				}
			}

			return true;
		}

		/**
		 Checks whether this AABB is completely, strictly enclosed by the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this AABB is completely, stricly enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedStrictBy(const list< XMFLOAT4 > &planes) const {
			for (list< XMFLOAT4 >::const_iterator it = planes.cbegin(); it != planes.cend(); ++it) {
				const XMVECTOR point = XMLoadFloat4(&(*it));

				// 000
				const XMFLOAT3 corner_000_f3(p_min.x, p_min.y, p_min.z);
				const XMVECTOR corner_000_v = XMLoadFloat3(&corner_000_f3);
				const XMVECTOR result_000_v = XMPlaneDotCoord(point, corner_000_v);
				float result_000;
				XMStoreFloat(&result_000, result_000_v);
				if (result_000 <= 0.0f) {
					return false;
				}

				// 001
				const XMFLOAT3 corner_001_f3(p_min.x, p_min.y, p_max.z);
				const XMVECTOR corner_001_v = XMLoadFloat3(&corner_001_f3);
				const XMVECTOR result_001_v = XMPlaneDotCoord(point, corner_001_v);
				float result_001;
				XMStoreFloat(&result_001, result_001_v);
				if (result_001 <= 0.0f) {
					return false;
				}

				// 010
				const XMFLOAT3 corner_010_f3(p_min.x, p_max.y, p_min.z);
				const XMVECTOR corner_010_v = XMLoadFloat3(&corner_010_f3);
				const XMVECTOR result_010_v = XMPlaneDotCoord(point, corner_010_v);
				float result_010;
				XMStoreFloat(&result_010, result_010_v);
				if (result_010 <= 0.0f) {
					return false;
				}

				// 011
				const XMFLOAT3 corner_011_f3(p_min.x, p_max.y, p_max.z);
				const XMVECTOR corner_011_v = XMLoadFloat3(&corner_011_f3);
				const XMVECTOR result_011_v = XMPlaneDotCoord(point, corner_011_v);
				float result_011;
				XMStoreFloat(&result_011, result_011_v);
				if (result_011 <= 0.0f) {
					return false;
				}

				// 100
				const XMFLOAT3 corner_100_f3(p_max.x, p_min.y, p_min.z);
				const XMVECTOR corner_100_v = XMLoadFloat3(&corner_100_f3);
				const XMVECTOR result_100_v = XMPlaneDotCoord(point, corner_100_v);
				float result_100;
				XMStoreFloat(&result_100, result_100_v);
				if (result_100 <= 0.0f) {
					return false;
				}

				// 101
				const XMFLOAT3 corner_101_f3(p_max.x, p_min.y, p_max.z);
				const XMVECTOR corner_101_v = XMLoadFloat3(&corner_101_f3);
				const XMVECTOR result_101_v = XMPlaneDotCoord(point, corner_101_v);
				float result_101;
				XMStoreFloat(&result_101, result_101_v);
				if (result_101 <= 0.0f) {
					return false;
				}

				// 110
				const XMFLOAT3 corner_110_f3(p_max.x, p_max.y, p_min.z);
				const XMVECTOR corner_110_v = XMLoadFloat3(&corner_110_f3);
				const XMVECTOR result_110_v = XMPlaneDotCoord(point, corner_110_v);
				float result_110;
				XMStoreFloat(&result_110, result_110_v);
				if (result_110 <= 0.0f) {
					return false;
				}

				// 111
				const XMFLOAT3 corner_111_f3(p_max.x, p_max.y, p_max.z);
				const XMVECTOR corner_111_v = XMLoadFloat3(&corner_111_f3);
				const XMVECTOR result_111_v = XMPlaneDotCoord(point, corner_111_v);
				float result_111;
				XMStoreFloat(&result_111, result_111_v);
				if (result_111 <= 0.0f) {
					return false;
				}
			}

			return true;
		}

		/**
		 Checks whether this AABB overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB overlaps @a aabb.
						@c false otherwise.
		 */
		bool Overlaps(const AABB &aabb) const {
			const bool x = (p_max.x >= aabb.p_min.x) && (p_min.x <= aabb.p_max.x);
			const bool y = (p_max.y >= aabb.p_min.y) && (p_min.y <= aabb.p_max.y);
			const bool z = (p_max.z >= aabb.p_min.z) && (p_min.z <= aabb.p_max.z);
			return (x && y && z);
		}

		/**
		 Checks whether this AABB strictly overlaps the given AABB.

		 @param[in]		aabb
						A reference to the AABB.
		 @return		@c true if this AABB strictly overlaps @a aabb.
						@c false otherwise.
		 */
		bool OverlapsStrict(const AABB &aabb) const {
			const bool x = (p_max.x > aabb.p_min.x) && (p_min.x < aabb.p_max.x);
			const bool y = (p_max.y > aabb.p_min.y) && (p_min.y < aabb.p_max.y);
			const bool z = (p_max.z > aabb.p_min.z) && (p_min.z < aabb.p_max.z);
			return (x && y && z);
		}

		/**
		 Returns the diagonal of this AABB.

		 @return		The diagonal of this AABB.
		 */
		XMFLOAT3 Diagonal() const {
			const XMVECTOR p_min_v = XMLoadFloat3(&p_min);
			const XMVECTOR p_max_v = XMLoadFloat3(&p_max);
			const XMVECTOR diagonal_v = p_max_v - p_min_v;
			XMFLOAT3 diagonal;
			XMStoreFloat3(&diagonal, diagonal_v);
			return diagonal;
		}

		/**
		 The minimum extents of this AABB.
		 */
		XMFLOAT3 p_min;

		/**
		 The maximum extents of this AABB.
		 */
		XMFLOAT3 p_max;
	};

	/**
	 Returns the union AABB of the given AABB and the given point.

	 @param[in]		aabb
					A reference to the AABB.
	 @param[in]		point
					A reference to the point.
	 @return		The union AABB of @a aabb and @a point.
	 */
	inline AABB Union(const AABB &aabb, const XMFLOAT3 &point) {
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb.p_max);
		const XMVECTOR p_v2 = XMLoadFloat3(&point);
		const XMVECTOR p_min_v = XMVectorMin(p_min_v1, p_v2);
		const XMVECTOR p_max_v = XMVectorMax(p_max_v1, p_v2);
		XMFLOAT3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
	}
	
	/**
	 Returns the union AABB of the two given AABBs.

	 @param[in]		aabb1
					A reference to the first AABB.
	 @param[in]		aabb2
					A reference to the second AABB.
	 @return		The union AABB of @a aabb1 and @a aabb2.
	 */
	inline AABB Union(const AABB &aabb1, const AABB &aabb2) {
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb1.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb1.p_max);
		const XMVECTOR p_min_v2 = XMLoadFloat3(&aabb2.p_min);
		const XMVECTOR p_max_v2 = XMLoadFloat3(&aabb2.p_max);
		const XMVECTOR p_min_v = XMVectorMin(p_min_v1, p_min_v2);
		const XMVECTOR p_max_v = XMVectorMax(p_max_v1, p_max_v2);
		XMFLOAT3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
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
	inline AABB Overlap(const AABB &aabb1, const AABB &aabb2) {
		if (!aabb1.Overlaps(aabb2)) {
			return AABB();
		}
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb1.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb1.p_max);
		const XMVECTOR p_min_v2 = XMLoadFloat3(&aabb2.p_min);
		const XMVECTOR p_max_v2 = XMLoadFloat3(&aabb2.p_max);
		const XMVECTOR p_min_v = XMVectorMax(p_min_v1, p_min_v2);
		const XMVECTOR p_max_v = XMVectorMin(p_max_v1, p_max_v2);
		XMFLOAT3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
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
	inline AABB OverlapStrict(const AABB &aabb1, const AABB &aabb2) {
		if (!aabb1.OverlapsStrict(aabb2)) {
			return AABB();
		}
		const XMVECTOR p_min_v1 = XMLoadFloat3(&aabb1.p_min);
		const XMVECTOR p_max_v1 = XMLoadFloat3(&aabb1.p_max);
		const XMVECTOR p_min_v2 = XMLoadFloat3(&aabb2.p_min);
		const XMVECTOR p_max_v2 = XMLoadFloat3(&aabb2.p_max);
		const XMVECTOR p_min_v = XMVectorMax(p_min_v1, p_min_v2);
		const XMVECTOR p_max_v = XMVectorMin(p_max_v1, p_max_v2);
		XMFLOAT3 p_min, p_max;
		XMStoreFloat3(&p_min, p_min_v);
		XMStoreFloat3(&p_max, p_max_v);
		return AABB(p_min, p_max);
	}

	/**
	 A struct of Bounding Spheres (BS).
	 */
	struct BS final {

	public:

		/**
		 Constructs a sphere.
		 */
		BS() : p(XMFLOAT3(0.0f, 0.0f, 0.0f)), r(1.0f) {}

		/**
		 Constructs a sphere.

		 @param[in]		p
						The position
		 @param[in]		r
						The radius.
		 */
		BS(const XMFLOAT3 &p, float r) 
			: p(p), r(r) {}

		/**
		 Checks whether this sphere completely encloses the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this sphere completely encloses @a planes.
						@c false otherwise.
		*/
		bool Encloses(const list< XMFLOAT4 > &planes) const {
			for (list< XMFLOAT4 >::const_iterator it = planes.cbegin(); it != planes.cend(); ++it) {
				const XMVECTOR point = XMLoadFloat4(&(*it));

				const XMVECTOR p_v = XMLoadFloat3(&p);
				const XMVECTOR result_v = XMPlaneDotCoord(point, p_v);
				float result;
				XMStoreFloat(&result, result_v);
				if (result < -r) {
					return false;
				}
			}

			return true;
		}

		/**
		 Checks whether this sphere completely, strictly encloses the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this sphere completely encloses @a planes.
						@c false otherwise.
		 */
		bool EnclosesStrict(const list< XMFLOAT4 > &planes) const {
			for (list< XMFLOAT4 >::const_iterator it = planes.cbegin(); it != planes.cend(); ++it) {
				const XMVECTOR point = XMLoadFloat4(&(*it));

				const XMVECTOR p_v = XMLoadFloat3(&p);
				const XMVECTOR result_v = XMPlaneDotCoord(point, p_v);
				float result;
				XMStoreFloat(&result, result_v);
				if (result <= -r) {
					return false;
				}
			}

			return true;
		}

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
		bool Collides(const BS &sphere, const XMFLOAT3 velocity_sum, float *collision_distance) const {
			const XMVECTOR p1_v = XMLoadFloat3(&p);
			const XMVECTOR p2_v = XMLoadFloat3(&sphere.p);

			// Calculate the direction vector from the second sphere to the first sphere.
			const XMVECTOR direction_v = p1_v - p2_v;

			// Calculate the distance between the two spheres.
			const XMVECTOR dist_v = XMVector3Length(direction_v);
			float dist;
			XMStoreFloat(&dist, dist_v);
			const float radii_sum = r + sphere.r;
			const float dist_between = dist - radii_sum;

			// Calculate the length of the sum of the velocity vectors of the two spheres.
			const XMVECTOR velocity_sum_v = XMLoadFloat3(&velocity_sum);
			const XMVECTOR velocity_sum_length_v = XMVector3Length(velocity_sum_length_v);
			float velocity_sum_length;
			XMStoreFloat(&velocity_sum_length, velocity_sum_length_v);

			// If the spheres are not touching each other and the velocity sum length is
			// less than the distance between them, then they cannot collide.
			if (0.0f < dist_between && velocity_sum_length < dist_between) {
				return false;
			}

			// Calculate the normalized sum of the velocity vectors of the two spheres.
			const XMVECTOR velocity_sum_normalized_v = XMVector3Normalize(velocity_sum_v);

			// Calculate the angle between the normalized sum of the velocity vectors and direction vectors.
			const XMVECTOR angle_between_v = XMVector3Dot(velocity_sum_normalized_v, direction_v);
			float angle_between;
			XMStoreFloat(&angle_between, angle_between_v);

			// Check whether the spheres are moving away from one another.
			if (angle_between <= 0.0f) {
				// Check whether the spheres are touching (or inside) each other. 
				// If not then they cannot collide since they are moving away from one another.
				if (dist_between < 0.0f) {
					// If the velocity sum length is greater than the distance between the
					// spheres then they are moving away from each other fast enough that 
					// they will not be touching when they complete their move.
					if (velocity_sum_length > -dist_between) {
						return false;
					}
				}
				else {
					return false;
				}
			}

			// The vector between the two spheres and the velocity sum vector produce two sides of a triangle. 
			// Now use Pythagorean Theorem to find the length of the third side of the triangle (i.e. the hypotenuse).
			const float hypotenuse = (dist * dist) - (angle_between * angle_between);

			// Ensure that the spheres come closer than the sum of their radii.
			const float squared_radii_sum = radii_sum * radii_sum;
			if (hypotenuse >= squared_radii_sum) {
				return false;
			}

			// Calculate the distance along the velocity vector that the spheres collide.
			// Then use this distance to calculate the distance to the collision.
			const float d = squared_radii_sum - hypotenuse;
			*collision_distance = angle_between - (float)sqrt(d);

			// Ensure that the sphere will not travel more than the velocity allows.
			return (velocity_sum_length >= *collision_distance);
		}

		/**
		 The position of this sphere.
		 */
		XMFLOAT3 p;

		/**
		 The radius of this sphere.
		 */
		float r;
	};
}