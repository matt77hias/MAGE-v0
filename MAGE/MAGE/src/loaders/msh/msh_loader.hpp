#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"
#include "utils\collection\collection.hpp" 

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
	 @param[out]	vertices
					A reference to a vector containing the vertices of the 
					mesh.
	 @param[out]	indices
					A reference to a vector containing the indices of the mesh.
	 @throws		FormattedException
					Failed to import the mesh from file.
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
					A reference to a vector containing the vertices of the 
					mesh.
	 @param[in]		indices
					A reference to a vector containing the indices of the mesh.
	 @throws		FormattedException
					Failed to export the mesh to file.
	 */
	template < typename VertexT, typename IndexT >
	void ExportMSHMeshToFile(const wstring &fname,
		const vector< VertexT > &vertices, const vector< IndexT > &indices);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_loader.tpp"

#pragma endregion