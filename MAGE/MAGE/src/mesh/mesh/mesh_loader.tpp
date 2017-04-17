#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh\mesh_reader.hpp"
#include "mesh\mesh\mesh_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT ImportMESHFromFile(const wstring &fname,
		vector< VertexT > &vertices, vector < uint32_t > &indices) {
		MESHReader reader(vertices, indices);
		return reader.ReadFromFile(fname);
	}

	template < typename VertexT >
	HRESULT ExportMESHToFile(const wstring &fname,
		const vector< VertexT > &vertices, const vector< uint32_t > &indices) {
		MESHWriter writer(vertices, indices);
		return writer.WriteToFile(fname);
	}
}