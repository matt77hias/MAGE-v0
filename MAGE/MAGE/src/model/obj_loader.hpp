#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads an OBJ model from file.

	 @param[in]		fname
					A reference to the file name.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[out]	index_buffer
					A reference to the empty index buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadOBJModelFromFile(const string &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer);

	/**
	 Loads an OBJ model from memory.

	 @param[in]		input
					A pointer to an array of chars that represents
					the input string.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[out]	index_buffer
					A reference to the empty index buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadOBJModelFromMemory(const char *input,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer);

	/**
	 Loads an OBJ model from file.

	 @param[in]		fname
					A reference to the file name.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadOBJModelFromFile(const string &fname,
		vector< Vertex > &vertex_buffer);

	/**
	 Loads an OBJ model from memory.

	 @param[in]		input
					A pointer to an array of chars that represents
					the input string.
	 @param[out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @return		A success/error value.
	 */
	HRESULT LoadOBJModelFromMemory(const char *input,
		vector< Vertex > &vertex_buffer);
}
