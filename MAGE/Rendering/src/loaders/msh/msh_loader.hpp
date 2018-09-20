#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <filesystem>
#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 Imports the mesh from the MSH file associated with the given path.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		path
					A reference to the path.
	 @param[out]	vertices
					A reference to a vector containing the vertices of the
					mesh.
	 @param[out]	indices
					A reference to a vector containing the indices of the mesh.
	 @throws		Exception
					Failed to import the mesh from file.
	 */
	template< typename VertexT, typename IndexT >
	void ImportMSHMeshFromFile(const std::filesystem::path& path,
		                       std::vector< VertexT >& vertices,
		                       std::vector< IndexT >& indices);

	/**
	 Exports the given mesh to the MSH file associated with the given path.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		path
					A reference to the path.
	 @param[in]		vertices
					A reference to a vector containing the vertices of the
					mesh.
	 @param[in]		indices
					A reference to a vector containing the indices of the mesh.
	 @throws		Exception
					Failed to export the mesh to file.
	 */
	template< typename VertexT, typename IndexT >
	void ExportMSHMeshToFile(const std::filesystem::path& path,
		                     const std::vector< VertexT >& vertices,
		                     const std::vector< IndexT >& indices);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_loader.tpp"

#pragma endregion