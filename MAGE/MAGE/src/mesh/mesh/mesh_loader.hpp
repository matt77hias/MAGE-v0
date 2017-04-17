#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "string\string.hpp"
#include "collection\collection.hpp" 

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the mesh from the given MESH file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the MESH filename.
	 @param[in,out]	vertices
					A reference to a vector containing the vertices of the mesh.
	 @param[in,out]	indices
					A reference to a vector containing the indices of the mesh.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT ImportMESHFromFile(const wstring &fname, 
		vector< VertexT > &vertices, vector< uint32_t > &indices);

	/**
	 Exports the given mesh to the given MESH file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the MESH filename.
	 @param[in]		vertices
					A reference to a vector containing the vertices of the mesh.
	 @param[in]		indices
					A reference to a vector containing the indices of the mesh.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT ExportMESHToFile(const wstring &fname, 
		const vector< VertexT > &vertices, const vector< uint32_t > &indices);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh\mesh_loader.tpp"

#pragma endregion