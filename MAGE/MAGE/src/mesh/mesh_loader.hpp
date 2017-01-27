#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\vertex.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads a mesh from file.

	 @param[in]		fname
					A reference to the file name.
	 @param[in,out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[in,out]	index_buffer
					A reference to the empty index buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadMeshFromFile(const string &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer);

	/**
	 Loads a mesh from file.

	 @param[in]		fname
					A reference to the file name.
	 @param[in,out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadMeshFromFile(const string &fname,
		vector< Vertex > &vertex_buffer);
}