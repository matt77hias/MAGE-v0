#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <DirectXMath.h>
#include <d3d11.h>
using namespace DirectX;

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// No use of d3dx
	// @src		https://blogs.msdn.microsoft.com/chuckw/2013/08/20/living-without-d3dx/

	// D3D11_INPUT_ELEMENT_DESC
	// @src		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476180(v=vs.85).aspx
	// 1. The HLSL semantic associated with this element in a shader input-signature.
	// 2. The semantic index for the element. 
	//	  A semantic index modifies a semantic, with an integer index number. 
	//	  A semantic index is only needed in a case where there is more than one element with the same semantic.
	// 3. Format:
	//	  DXGI_FORMAT_R32G32B32_FLOAT: A three component, 96 bit floating point format that supports 32 bits per color channel.
	//	  DXGI_FORMAT_R32G32_FLOAT: A two component, 64 bit floating point format that supports 32 bits for the red channel and 32 bits for the green channel.
	//	  DXGI_FORMAT_R32G32B32A32_FLOAT: A four component, 128 bit floating point format that supports 32 bits per channel including alpha.
	// 4. An integer value that identifies the input assembler.Valid values are between 0 and 15.
	// 5. Offset (in bytes) between each element.
	// 6. Identifies the input data class for a single input slot.
	//	  D3D11_INPUT_PER_VERTEX_DATA: Input data is per vertex data.
	// 7. The number of instances to draw using the same per instance data before advancing in the buffer by one element.
	//	  This value must be 0 for an element that contains per vertex data.

	/**
	 A struct of vertices.
	 */
	struct Vertex {

	public:

		/**
		 Constructs a vertex.
		 */
		Vertex() : p(XMFLOAT3(0.0f, 0.0f, 0.0f)), n(XMFLOAT3(0.0f, 0.0f, 0.0f)), tu(0.0f), tv(0.0f) {}

		/**
		 Constructs a vertex.

		 @param[in]		p
						Position of the vertex (in world space).
		 @param[in]		n
						Normal of the vertex.
		 @param[in]		tu
						Texture u coordinate of the vertex.
		 @param[in]		tv
						Texture v coordinate of the vertex.
		 */
		Vertex(XMFLOAT3 p, XMFLOAT3 n, float tu, float tv) : p(p), n(n), tu(tu), tv(tv) {}

		/**
		 Position of this vertex (in world space).
		 */
		XMFLOAT3 p;

		/**
		 Normal of this vertex.
		 */
		XMFLOAT3 n;

		/**
		 Texture u coordinate of this vertex.
		 */
		float tu;

		/**
		 Texture v coordinate of this vertex.
		 */
		float tv;
	};

	/**
	 Input element descriptor for a Vertex.
	 */
	const D3D11_INPUT_ELEMENT_DESC vertex_input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(Vertex, p)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(Vertex, n)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, UINT(offsetof(Vertex, tu)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/**
	 A struct of lit vertices.
	 */
	struct LVertex {

	public:

		/**
		 Constructs a lit vertex.
		 */
		LVertex() : p(XMFLOAT3(0.0f, 0.0f, 0.0f)), diffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)), tu(0.0f), tv(0.0f) {}

		/**
		 Constructs a lit vertex.

		 @param[in]		p
						Position of the lit vertex (in world space).
		 @param[in]		diffuse
						Diffuse colour of the lit vertex.
		 @param[in]		tu
						Texture u coordinate of the lit vertex.
		 @param[in]		tv
						Texture v coordinate of the lit vertex.
		 */
		LVertex(XMFLOAT3 p, XMFLOAT4 diffuse, float tu, float tv) : p(p), diffuse(diffuse), tu(tu), tv(tv) {}

		/**
		 Position of this lit vertex (in world space).
		 */
		XMFLOAT3 p;

		/**
		 Diffuse colour of this lit vertex.
		 */
		XMFLOAT4 diffuse;

		/**
		 Texture u coordinate of this lit vertex.
		 */
		float tu;

		/**
		 Texture v coordinate of this lit vertex.
		 */
		float tv;
	};

	/**
	 Input element descriptor for a LVertex.
	 */
	const D3D11_INPUT_ELEMENT_DESC lvertex_input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(LVertex, p)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(LVertex, diffuse)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, UINT(offsetof(LVertex, tu)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/**
	 A struct of transformed and lit vertices.
	 */
	struct TLVertex {

	public:

		/**
		 Constructs a transformed and lit vertex.
		 */
		TLVertex() : p(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)), diffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)), tu(0.0f), tv(0.0f) {}
		
		/**
		 Constructs a transformed and lit vertex.

		 @param[in]		p
						Position of the transformed and lit vertex (in screen space).
		 @param[in]		diffuse
						Diffuse colour of the transformed and lit vertex.
		 @param[in]		tu
						Texture u coordinate of the transformed and lit vertex.
		 @param[in]		tv
						Texture v coordinate of the transformed and lit vertex.
		 */
		TLVertex(XMFLOAT4 p, XMFLOAT4 diffuse, float tu, float tv) : p(p), diffuse(diffuse), tu(tu), tv(tv) {}

		/**
		 Position of this transformed and lit vertex (in screen space).
		 */
		XMFLOAT4 p;

		/**
		 Diffuse colour of this transformed and lit vertex.
		 */
		XMFLOAT4 diffuse;

		/**
		 Texture u coordinate of this transformed and lit vertex.
		 */
		float tu;

		/**
		 Texture v coordinate of this transformed and lit vertex.
		 */
		float tv;
	};

	/** 
	 Input element descriptor for a TLVertex
	 */
	const D3D11_INPUT_ELEMENT_DESC tlvertex_input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(TLVertex, p)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(TLVertex, diffuse)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, UINT(offsetof(TLVertex, tu)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/**
	 A struct of edges.
	 */
	struct Edge {

	public:

		/**
		 Constructs an edge between the two given vertices.

		 @param[in]		v0
						A pointer to the first vertex.
		 @param[in]		v1
						A pointer to the second vertex.
		 */
		Edge(Vertex *v0, Vertex *v1) : v0(v0), v1(v1) {}

		/**
		 The first vertex of this edge.
		 */
		Vertex *v0;

		/**
		 The second vertex of this edge.
		 */
		Vertex *v1;
	};

	/**
	 A struct of indexed edges.
	 */
	struct IndexedEdge {

	public:

		/**
		 The index of the edge's first vertex.
		 */
		uint16_t iv0;

		/**
		 The index of the edge's second vertex.
		 */
		uint16_t iv1;
	};

	/**
	 A struct of faces.
	 */
	struct Face {

	public:

		/**
		 Constructs a face for the three given vertices.

		 @param[in]		v0
						A pointer to the first vertex.
		 @param[in]		v1
						A pointer to the second vertex.
		 @param[in]		v2
						A pointer to the third vertex.
		*/
		Face(Vertex *v0, Vertex *v1, Vertex *v2) : v0(v0), v1(v1), v2(v2) {}

		/**
		 The first vertex of this face.
		 */
		Vertex *v0;

		/**
		 The second vertex of this face.
		 */
		Vertex *v1;

		/**
		 The third vertex of this face.
		 */
		Vertex *v2;
	};

	/**
	 A struct of indexed faces.
	 */
	struct IndexedFace {

	public:

		/**
		 Index of the face's first vertex.
		 */
		uint16_t iv0;

		/**
		 Index of the face's second vertex.
		 */
		uint16_t iv1;

		/**
		 Index of the face's third vertex.
		 */
		uint16_t iv2;
	};

	/**
	 A struct of Axis-Aligned Bounding Boxes (AABBs).
	 */
	struct AABB {

		/**
		 Constructs an AABB.
		 */
		AABB() : p_min(XMFLOAT3(-INFINITY, -INFINITY, -INFINITY)), p_max(XMFLOAT3(INFINITY, INFINITY, INFINITY)) {}

		/**
		 Constructs an AABB.

		 @param[in]		p_min
						The minimum extents.
		 @param[in]		p_max
						The maximum extents.
		 */
		AABB(XMFLOAT3 p_min, XMFLOAT3 p_max) : p_min(p_min), p_max(p_max) {}

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
		 Checks whether this AABB is completely enclosed by the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this AABB is completely enclosed by @a planes.
						@c false otherwise.
		 */
		bool EnclosedBy(const LinkedList< XMFLOAT4 > &planes) const {
			LinkedList<XMFLOAT4>::LinkedListIterator it = planes.GetIterator();
			while (it.HasNext()) {
				const XMVECTOR point = XMLoadFloat4(it.Next());

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
		 The minimum extents of this AABB.
		 */
		XMFLOAT3 p_min;

		/**
		 The maximum extents of this AABB.
		 */
		XMFLOAT3 p_max;
	};

	/**
	 A struct of spheres.
	 */
	struct Sphere {

		/**
		 Constructs a sphere.
		 */
		Sphere() : p(XMFLOAT3(0.0f, 0.0f, 0.0f)), r(1.0f) {}

		/**
		 Constructs a sphere.

		 @param[in]		p
						The position
		 @param[in]		r
						The radius.
		 */
		Sphere(XMFLOAT3 p, float r) : p(p), r(r) {}

		/**
		 Checks whether this sphere completely encloses the given (closed) volume.

		 @param[in]		planes
						A reference to a linked list containing the planes of the volume
						(each plane's coefficients are represented as a @c XMFLOAT4).
		 @return		@c true if this sphere completely encloses @a planes.
						@c false otherwise.
		*/
		bool Encloses(const LinkedList< XMFLOAT4 > &planes) {
			LinkedList<XMFLOAT4>::LinkedListIterator it = planes.GetIterator();
			while (it.HasNext()) {
				const XMVECTOR point = XMLoadFloat4(it.Next());

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
		bool Collides(const Sphere &sphere, const XMFLOAT3 velocity_sum, float *collision_distance) {
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