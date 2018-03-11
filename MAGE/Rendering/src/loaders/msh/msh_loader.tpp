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
	void ImportMSHMeshFromFile(const wstring& fname, 
		                       std::vector< VertexT >& vertices, 
		                       std::vector< IndexT >& indices) {
		
		MSHReader< VertexT, IndexT > reader(vertices, indices);
		reader.ReadFromFile(fname);
	}

	template< typename VertexT, typename IndexT >
	void ExportMSHMeshToFile(const wstring& fname,
		                     const std::vector< VertexT >& vertices, 
		                     const std::vector< IndexT >& indices) {
		
		MSHWriter< VertexT, IndexT > writer(vertices, indices);
		writer.WriteToFile(fname);
	}
}