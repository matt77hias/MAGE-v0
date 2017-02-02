#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <string>
namespace mage {
	using std::string;
	using std::wstring;
}

#include <windows.h>

#pragma endregion

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
	 Loads an OBJ mesh from file.

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
	HRESULT LoadOBJMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer,
		bool invert_handedness = false, bool clockwise_order = true);

	/**
	 Loads an OBJ mesh from memory.

	 @param[in]		input
					A pointer to an array of chars that represents
					the input string.
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
	HRESULT LoadOBJMeshFromMemory(const char *input,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer,
		bool invert_handedness = false, bool clockwise_order = true);

	/**
	 Loads an OBJ mesh from file.

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
	HRESULT LoadOBJMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer,
		bool invert_handedness = false, bool clockwise_order = true);

	/**
	 Loads an OBJ mesh from memory.

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
	HRESULT LoadOBJMeshFromMemory(const char *input,
		vector< Vertex > &vertex_buffer,
		bool invert_handedness = false, bool clockwise_order = true);
}
