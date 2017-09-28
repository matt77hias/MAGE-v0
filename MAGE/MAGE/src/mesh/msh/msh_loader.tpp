#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_reader.hpp"
#include "mesh\msh\msh_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	void ImportMSHMeshFromFile(const wstring &fname,
		vector< VertexT > &vertices, vector < U32 > &indices) {
		
		MSHReader< VertexT, U32 > reader(vertices, indices);
		reader.ReadFromFile(fname);
	}

	template < typename VertexT >
	void ExportMSHMeshToFile(const wstring &fname,
		const vector< VertexT > &vertices, const vector< U32 > &indices) {
		
		MSHWriter< VertexT, U32 > writer(vertices, indices);
		writer.WriteToFile(fname);
	}
}