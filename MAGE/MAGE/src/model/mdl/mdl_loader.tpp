#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_reader.hpp"
#include "model\mdl\mdl_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	void ImportMDLModelFromFile(const wstring &fname,
		ModelOutput< VertexT > &model_output) {
		
		MDLReader< VertexT > reader(model_output);
		reader.ReadFromFile(fname);
	}

	template < typename VertexT >
	void ExportMDLModelToFile(const wstring &fname,
		const ModelOutput< VertexT > &model_output) {
		
		MDLWriter< VertexT > writer(model_output);
		writer.WriteToFile(fname);
	}
}