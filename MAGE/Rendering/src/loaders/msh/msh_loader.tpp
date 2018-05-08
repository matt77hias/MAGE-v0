#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_reader.hpp"
#include "loaders\msh\msh_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	template< typename VertexT, typename IndexT >
	void ImportMSHMeshFromFile(const std::filesystem::path& path, 
		                       std::vector< VertexT >& vertices, 
		                       std::vector< IndexT >& indices) {
		
		MSHReader< VertexT, IndexT > reader(vertices, indices);
		reader.ReadFromFile(path);
	}

	template< typename VertexT, typename IndexT >
	void ExportMSHMeshToFile(const std::filesystem::path& path, 
		                     const std::vector< VertexT >& vertices, 
		                     const std::vector< IndexT >& indices) {
		
		MSHWriter< VertexT, IndexT > writer(vertices, indices);
		writer.WriteToFile(path);
	}
}