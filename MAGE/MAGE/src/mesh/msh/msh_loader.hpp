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
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the mesh from the given MSH file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		fname
					A reference to the MSH filename.
	 @param[in,out]	vertices
					A reference to a vector containing the vertices of the mesh.
	 @param[in,out]	indices
					A reference to a vector containing the indices of the mesh.
	 */
	template < typename VertexT, typename IndexT >
	void ImportMSHMeshFromFile(const wstring &fname, 
		vector< VertexT > &vertices, vector< IndexT > &indices);

	/**
	 Exports the given mesh to the given MSH file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		fname
					A reference to the MSH filename.
	 @param[in]		vertices
					A reference to a vector containing the vertices of the mesh.
	 @param[in]		indices
					A reference to a vector containing the indices of the mesh.
	 */
	template < typename VertexT, typename IndexT >
	void ExportMSHMeshToFile(const wstring &fname,
		const vector< VertexT > &vertices, const vector< IndexT > &indices);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_loader.tpp"

#pragma endregion