#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3d11_2.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of vertices.
	 */
	struct Vertex final {

	public:

		/**
		 Constructs a vertex.
		 */
		Vertex() : p(Point3(0.0f, 0.0f, 0.0f)), n(Normal3(0.0f, 0.0f, 0.0f)), tex(XMFLOAT2(0.0f, 0.0f)) {}

		/**
		 Constructs a vertex.

		 @pre			The length (L2-norm) of the normal must be equal to one
						(i.e. the normal vector is normalized) 
						or zero if no normal is specified.
		 @param[in]		p
						The position of the vertex (in object space).
		 @param[in]		n
						The normal of the vertex.
		 @param[in]		tex
						The texture coordinates of the vertex.
		 */
		Vertex(Point3 p, Normal3 n, XMFLOAT2 tex) : p(p), n(n), tex(tex) {}

		/**
		 The position of this vertex (in object space).
		 */
		Point3 p;

		/**
		 The normal of this vertex.
		 */
		Normal3 n;

		/**
		 The texture coordinates of this vertex.
		 */
		XMFLOAT2 tex;

		/**
		 The input element descriptor for a vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[];
	};

	const D3D11_INPUT_ELEMENT_DESC Vertex::input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(Vertex, p)),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",	  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, UINT(offsetof(Vertex, n)),   D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, UINT(offsetof(Vertex, tex)), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/**
	 A struct of lit vertices.
	 */
	struct LVertex final {

	public:

		/**
		 Constructs a lit vertex.
		 */
		LVertex() : p(Point3(0.0f, 0.0f, 0.0f)), diffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)), tex(XMFLOAT2(0.0f, 0.0f)) {}

		/**
		 Constructs a lit vertex.

		 @param[in]		p
						The position of the lit vertex (in object space).
		 @param[in]		diffuse
						The diffuse color of the lit vertex.
		 @param[in]		tex
						The texture coordinate of the lit vertex.
		 */
		LVertex(Point3 p, XMFLOAT4 diffuse, XMFLOAT2 tex) : p(p), diffuse(diffuse), tex(tex) {}

		/**
		 The position of this lit vertex (in object space).
		 */
		Point3 p;

		/**
		 The diffuse color of this lit vertex.
		 */
		XMFLOAT4 diffuse;

		/**
		 The texture coordinates of this lit vertex.
		 */
		XMFLOAT2 tex;

		/**
		 The input element descriptor for a lit vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[];
	};

	const D3D11_INPUT_ELEMENT_DESC LVertex::input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, UINT(offsetof(LVertex, p)),       D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIFFUSE",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(LVertex, diffuse)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, UINT(offsetof(LVertex, tex)),     D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/**
	 A struct of transformed and lit vertices.
	 */
	struct TLVertex final {

	public:

		/**
		 Constructs a transformed and lit vertex.
		 */
		TLVertex() : p(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)), diffuse(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)), tex(XMFLOAT2(0.0f, 0.0f)) {}
		
		/**
		 Constructs a transformed and lit vertex.

		 @param[in]		p
						The position of the transformed and lit vertex (in projection space).
		 @param[in]		diffuse
						The diffuse color of the transformed and lit vertex.
		 @param[in]		tex
						The texture coordinates of the transformed and lit vertex.
		 */
		TLVertex(XMFLOAT4 p, XMFLOAT4 diffuse, XMFLOAT2 tex) : p(p), diffuse(diffuse), tex(tex) {}

		/**
		 The position of this transformed and lit vertex (in projection space).
		 */
		XMFLOAT4 p;

		/**
		 The diffuse color of this transformed and lit vertex.
		 */
		XMFLOAT4 diffuse;

		/**
		 The texture coordinates of this transformed and lit vertex.
		 */
		XMFLOAT2 tex;

		/**
		 The input element descriptor for a transformed and lit vertex.
		 */
		static const D3D11_INPUT_ELEMENT_DESC input_element_desc[];
	};

	/**
	 The input element descriptor for a transformed and lit vertex.
	 */
	const D3D11_INPUT_ELEMENT_DESC TLVertex::input_element_desc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(TLVertex, p)),       D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "DIFFUSE",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, UINT(offsetof(TLVertex, diffuse)), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, UINT(offsetof(TLVertex, tex)),     D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	/**
	 A struct of edges.
	 */
	struct Edge final {

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
	struct IndexedEdge final {

	public:

		/**
		 The index of the edge's first vertex.
		 */
		uint32_t iv0;

		/**
		 The index of the edge's second vertex.
		 */
		uint32_t iv1;
	};

	/**
	 A struct of faces.
	 */
	struct Face final {

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
	struct IndexedFace final {

	public:

		/**
		 Index of the face's first vertex.
		 */
		uint32_t iv0;

		/**
		 Index of the face's second vertex.
		 */
		uint32_t iv1;

		/**
		 Index of the face's third vertex.
		 */
		uint32_t iv2;
	};
}