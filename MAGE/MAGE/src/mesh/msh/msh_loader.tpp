#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_reader.hpp"
#include "mesh\msh\msh_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT ImportMSHMeshFromFile(const wstring &fname,
		vector< VertexT > &vertices, vector < uint32_t > &indices) {
		MSHReader< VertexT, uint32_t > reader(vertices, indices);
		return reader.ReadFromFile(fname);
	}

	template < typename VertexT >
	HRESULT ExportMSHMeshToFile(const wstring &fname,
		const vector< VertexT > &vertices, const vector< uint32_t > &indices) {
		MSHWriter< VertexT, uint32_t > writer(vertices, indices);
		return writer.WriteToFile(fname);
	}
}