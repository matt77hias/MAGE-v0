#pragma once

//-----------------------------------------------------------------------------
// DirectX Includes
//-----------------------------------------------------------------------------
#include <DirectXMath.h>
#include <d3d11.h>
using namespace DirectX;

namespace mage {

	// No use of d3dx
	// @src		https://blogs.msdn.microsoft.com/chuckw/2013/08/20/living-without-d3dx/

	// D3D11_INPUT_ELEMENT_DESC
	// @src		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476180(v=vs.85).aspx
	// @param	SemanticName:
	//			The HLSL semantic associated with this element in a shader input-signature.
	// @param	SemanticIndex:
	//			The semantic index for the element. 
	//			A semantic index modifies a semantic, with an integer index number. 
	//			A semantic index is only needed in a case where there is more than one element with the same semantic.
	// @param	Format:
	//			DXGI_FORMAT_R32G32B32_FLOAT:
	//			A three component, 96 bit floating point format that supports 32 bits per color channel.
	//			DXGI_FORMAT_R32G32_FLOAT
	//			A two component, 64 bit floating point format that supports 32 bits for the red channel and 32 bits for the green channel.
	//			DXGI_FORMAT_R32G32B32A32_FLOAT
	//			A four component, 128 bit floating point format that supports 32 bits per channel including alpha.
	// @param	InputSlot:
	//			An integer value that identifies the input assembler.Valid values are between 0 and 15.
	// @param	AlignedByteOffset:
	//			Offset (in bytes) between each element.
	// @param	InputSlotClass:
	//			Identifies the input data class for a single input slot.
	//			D3D11_INPUT_PER_VERTEX_DATA:
	//			Input data is per vertex data.
	// @param	InstanceDataStepRate:
	//			The number of instances to draw using the same per instance data before advancing in the buffer by one element.
	//			This value must be 0 for an element that contains per vertex data.

	//-----------------------------------------------------------------------------
	// Vertex
	//-----------------------------------------------------------------------------
	struct Vertex {

	public:
		Vertex() : p(XMFLOAT3(0.0f, 0.0f, 0.0f)), n(XMFLOAT3(0.0f, 0.0f, 0.0f)), tu(0.0f), tv(0.0f) {}
		Vertex(XMFLOAT3 p, XMFLOAT3 n, float tu, float tv) : p(p), n(n), tu(tu), tv(tv) {}

		// Position of the vertex (in world space)
		XMFLOAT3 p;
		// Normal of this vertex
		XMFLOAT3 n;
		// Texture UV coordinates
		float tu, tv;
	};

	// Input element descriptor for a Vertex
	const D3D11_INPUT_ELEMENT_DESC vertex_input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(Vertex, p)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(Vertex, n)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, UINT(offsetof(Vertex, tu)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//-----------------------------------------------------------------------------
	// Lit Vertex
	//-----------------------------------------------------------------------------
	struct LVertex {

	public:
		LVertex() : p(XMFLOAT3(0.0f, 0.0f, 0.0f)), diffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)), tu(0.0f), tv(0.0f) {}
		LVertex(XMFLOAT3 p, XMFLOAT4 diffuse, float tu, float tv) : p(p), diffuse(diffuse), tu(tu), tv(tv) {}

		// Position of the vertex (in world space)
		XMFLOAT3 p;
		// Colour of this vertex
		XMFLOAT4 diffuse;
		// Texture UV coordinates
		float tu, tv;

	};

	// Input element descriptor for a LVertex
	const D3D11_INPUT_ELEMENT_DESC lvertex_input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(LVertex, p)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(LVertex, diffuse)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, UINT(offsetof(LVertex, tu)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//-----------------------------------------------------------------------------
	// Transformed & Lit Vertex
	//-----------------------------------------------------------------------------
	struct TLVertex {

	public:
		TLVertex() : p(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)), diffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)), tu(0.0f), tv(0.0f) {}
		TLVertex(XMFLOAT4 p, XMFLOAT4 diffuse, float tu, float tv) : p(p), diffuse(diffuse), tu(tu), tv(tv) {}

		// Position of the vertex (in screen space)
		XMFLOAT4 p;
		// Colour of this vertex
		XMFLOAT4 diffuse;
		// Texture UV coordinates
		float tu, tv;
	};

	// Input element descriptor for a TLVertex
	const D3D11_INPUT_ELEMENT_DESC tlvertex_input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(TLVertex, p)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIFFUSE", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(TLVertex, diffuse)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, UINT(offsetof(TLVertex, tu)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//-----------------------------------------------------------------------------
	// Edge
	//-----------------------------------------------------------------------------
	struct Edge {

	public:

		Edge(Vertex *v0, Vertex *v1) : v0(v0), v1(v1) {}

		// First vertex of this edge
		Vertex *v0;
		// Second vertex of this edge
		Vertex *v1;
	};

	//-----------------------------------------------------------------------------
	// Indexed Edge
	//-----------------------------------------------------------------------------
	struct IndexedEdge {

	public:

		// Index of the edge's first vertex
		uint16_t iv0;
		// Index of the edge's second vertex
		uint16_t iv1;
	};

	//-----------------------------------------------------------------------------
	// Face
	//-----------------------------------------------------------------------------
	struct Face {

	public:

		Face(Vertex *v0, Vertex *v1, Vertex *v2) : v0(v0), v1(v1), v2(v2) {}

		// First vertex of this face
		Vertex *v0;
		// Second vertex of this face
		Vertex *v1;
		// Third vertex of this face
		Vertex *v2;
	};

	//-----------------------------------------------------------------------------
	// Indexed Face
	//-----------------------------------------------------------------------------
	struct IndexedFace {

	public:
		// Index of the face's first vertex
		uint16_t iv0;
		// Index of the face's second vertex
		uint16_t iv1;
		// Index of the face's third vertex
		uint16_t iv2;
	};

	//-----------------------------------------------------------------------------
	// Returns true if the first given box is inside the second given box.
	//-----------------------------------------------------------------------------




	struct AABB {

		AABB() : p_min(XMFLOAT3(-INFINITY, -INFINITY, -INFINITY)), p_max(XMFLOAT3(INFINITY, INFINITY, INFINITY)) {}

		bool Inside(AABB &aabb) const {
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
		bool Inside(Face &face) const {
			// Find the minimum and maximum points of the face along the x axis. 
			// Then check if these two points are within the box's x axis extents.
			const float min_x = min(face.v0->p.x, min(face.v1->p.x, face.v2->p.x));
			const float max_x = max(face.v0->p.x, max(face.v1->p.x, face.v2->p.x));
			if (max_x < p_min.x) {
				return false;
			}
			if (min_x > p_max.x) {
				return false;
			}

			// Find the minimum and maximum points of the face along the y axis. 
			// Then check if these two points are within the box's y axis extents.
			const float min_y = min(face.v0->p.y, min(face.v1->p.y, face.v2->p.y));
			const float max_y = max(face.v0->p.y, max(face.v1->p.y, face.v2->p.y));
			if (max_y < p_min.y) {
				return false;
			}
			if (min_y > p_max.y) {
				return false;
			}

			// Find the minimum and maximum points of the face along the z axis. 
			// Then check if these two points are within the box's z axis extents.
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

		/*bool EnclosedBy(LinkedList< XMFLOAT4 > *planes) const {
			LinkedList<XMFLOAT4>::LinkedListIterator it = planes->GetIterator();
			while (it.HasNext()) {
				const XMVECTOR next = DirectX::XMLoadFloat4(it.Next());
				float a;

				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_min.x, p_min.y, p_min.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_max.x, p_min.y, p_min.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_min.x, p_max.y, p_min.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_max.x, p_max.y, p_min.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_min.x, p_min.y, p_max.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_max.x, p_min.y, p_max.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_min.x, p_max.y, p_max.z))));
				if (a < 0.0f) {
					return false;
				}
				DirectX::XMStoreFloat(&a, DirectX::XMPlaneDotCoord(next, DirectX::XMLoadFloat3(&XMFLOAT3(p_max.x, p_max.y, p_max.z))));
				if (a < 0.0f) {
					return false;
				}
			}

			return true;
		}*/

		XMFLOAT3 p_min;
		XMFLOAT3 p_max;
	};

}