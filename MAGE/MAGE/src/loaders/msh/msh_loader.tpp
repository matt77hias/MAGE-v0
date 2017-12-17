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
namespace mage::loader {

	template < typename VertexT >
	void ImportMSHMeshFromFile(const wstring &fname, 
		                       std::vector< VertexT > &vertices, 
		                       std::vector< U32 >     &indices) {
		
		MSHReader< VertexT, U32 > reader(vertices, indices);
		reader.ReadFromFile(fname);
	}

	template < typename VertexT >
	void ExportMSHMeshToFile(const wstring &fname,
		                     const std::vector< VertexT > &vertices, 
		                     const std::vector< U32 >     &indices) {
		
		MSHWriter< VertexT, U32 > writer(vertices, indices);
		writer.WriteToFile(fname);
	}
}