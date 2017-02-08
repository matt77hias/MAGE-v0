#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp"
#include "math\vertex.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads an OBJ mesh from file.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		fname
					A reference to the file name.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[out]	index_buffer
					A reference to the empty index buffer.
	 @param[in]		invert_handedness
					Flag indicating whether the handness of the
					coordinate system of the mesh should be inverted.
	 @param[in]		clockwise_order
					Flag indicating whether the vertices of triangles
					should be in clockwise order.
	 @return		A success/error value.
	 */
	template < typename Vertex >
	HRESULT LoadOBJMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer,
		bool invert_handedness, bool clockwise_order);

	/**
	 Loads an OBJ mesh from memory.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		input
					A pointer to an array of chars that represents
					the input
					.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[out]	index_buffer
					A reference to the empty index buffer.
	 @param[in]		invert_handedness
					Flag indicating whether the handness of the
					coordinate system of the mesh should be inverted.
	 @param[in]		clockwise_order
					Flag indicating whether the vertices of triangles
					should be in clockwise order.
	 @return		A success/error value.
	 */
	template < typename Vertex >
	HRESULT LoadOBJMeshFromMemory(const char *input,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer,
		bool invert_handedness, bool clockwise_order);

	/**
	 Loads an OBJ mesh from file.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		fname
					A reference to the file name.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[in]		invert_handedness
					Flag indicating whether the handness of the
					coordinate system of the mesh should be inverted.
	 @param[in]		clockwise_order
					Flag indicating whether the vertices of triangles
					should be in clockwise order.
	 @return		A success/error value.
	 */
	template < typename Vertex >
	HRESULT LoadOBJMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer,
		bool invert_handedness, bool clockwise_order);

	/**
	 Loads an OBJ mesh from memory.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		input
					A pointer to an array of chars that represents
					the input string.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[in]		invert_handedness
					Flag indicating whether the handness of the
					coordinate system of the mesh should be inverted.
	 @param[in]		clockwise_order
					Flag indicating whether the vertices of triangles
					should be in clockwise order.
	 @return		A success/error value.
	 */
	template < typename Vertex >
	HRESULT LoadOBJMeshFromMemory(const char *input,
		vector< Vertex > &vertex_buffer,
		bool invert_handedness, bool clockwise_order);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj_loader.tpp"

#pragma endregion