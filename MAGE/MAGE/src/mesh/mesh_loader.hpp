#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads a mesh from file.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		fname
					A reference to the file name.
	 @param[in,out]	vertex_buffer
					A reference to the empty vertex buffer.
	 @param[in,out]	index_buffer
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
	HRESULT LoadMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer,
		bool invert_handedness = false, bool clockwise_order = true) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return LoadOBJMeshFromFile< Vertex >(fname, vertex_buffer, index_buffer, invert_handedness, clockwise_order);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}

	/**
	 Loads a mesh from file.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		fname
					A reference to the file name.
	 @param[in,out]	vertex_buffer
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
	HRESULT LoadMeshFromFile(const wstring &fname,
		vector< Vertex > &vertex_buffer,
		bool invert_handedness = false, bool clockwise_order = true) {
		
		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return LoadOBJMeshFromFile< Vertex >(fname, vertex_buffer, invert_handedness, clockwise_order);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}