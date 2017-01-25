#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads a model from file.

	 @param[in]		fname
					A reference to the file name.
	 @param[in,out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[in,out]	index_buffer
					A reference to the empty index buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadModelFromFile(const string &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer);
}