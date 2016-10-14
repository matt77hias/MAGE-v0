#pragma once

//-----------------------------------------------------------------------------
// DirectX Includes
//-----------------------------------------------------------------------------
#include <d3dx9.h>

//-----------------------------------------------------------------------------
// Vertex
//-----------------------------------------------------------------------------
struct Vertex {

public:
	Vertex() : p(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), n(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), tu(0.0f), tv(0.0f) {}
	Vertex(D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv) : p(p), n(n), tu(tu), tv(tv) {}

	// Position of the vertex (in world space)
	D3DXVECTOR3 p;
	// Normal of this vertex
	D3DXVECTOR3 n;
	// Texture UV coordinates
	float tu, tv;
};
#define VERTEX_FVF ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
#define VERTEX_FVF_SIZE D3DXGetFVFVertexSize( VERTEX_FVF )

//-----------------------------------------------------------------------------
// Lit Vertex
//-----------------------------------------------------------------------------
struct LVertex {
	
public:
	LVertex() : p(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), diffuse(D3DCOLOR(0xFFFFFFFF)), tu(0.0f), tv(0.0f) {}
	LVertex(D3DXVECTOR3 p, D3DCOLOR diffuse, float tu, float tv) : p(p), diffuse(diffuse), tu(tu), tv(tv) {}

	// Position of the vertex (in world space)
	D3DXVECTOR3 p;
	// Colour of this vertex
	D3DCOLOR diffuse;
	// Texture UV coordinates
	float tu, tv;

};
#define L_VERTEX_FVF ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define L_VERTEX_FVF_SIZE D3DXGetFVFVertexSize( L_VERTEX_FVF )

//-----------------------------------------------------------------------------
// Transformed & Lit Vertex
//-----------------------------------------------------------------------------
struct TLVertex {

public:
	TLVertex() : p(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f)), diffuse(D3DCOLOR(0xFFFFFFFF)), tu(0.0f), tv(0.0f) {}
	TLVertex(D3DXVECTOR4 p, D3DCOLOR diffuse, float tu, float tv) : p(p), diffuse(diffuse), tu(tu), tv(tv) {}

	// Position of the vertex (in screen space)
	D3DXVECTOR4 p;
	// Colour of this vertex
	D3DCOLOR diffuse;
	// Texture UV coordinates
	float tu, tv;
};
#define TL_VERTEX_FVF ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define TL_VERTEX_FVF_SIZE D3DXGetFVFVertexSize( TL_VERTEX_FVF )

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