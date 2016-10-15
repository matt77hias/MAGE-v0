#pragma once

//-----------------------------------------------------------------------------
// DirectX Includes
//-----------------------------------------------------------------------------
#include <DirectXMath.h>
#include <d3d11.h>
using namespace DirectX;

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
D3D11_INPUT_ELEMENT_DESC vertex_input_element_desc[] = {
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
D3D11_INPUT_ELEMENT_DESC lvertex_input_element_desc[] = {
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
D3D11_INPUT_ELEMENT_DESC tlvertex_input_element_desc[] = {
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