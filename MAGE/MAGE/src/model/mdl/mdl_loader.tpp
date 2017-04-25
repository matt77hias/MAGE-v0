#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_reader.hpp"
#include "model\mdl\mdl_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT ImportMDLModelFromFile(const wstring &fname,
		ModelOutput< VertexT > &model_output) {
		MDLReader< VertexT > reader(model_output);
		reader.ReadFromFile(fname);
		return S_OK;
	}

	template < typename VertexT >
	HRESULT ExportMDLModelToFile(const wstring &fname,
		const ModelOutput< VertexT > &model_output) {
		MDLWriter< VertexT > writer(model_output);
		writer.WriteToFile(fname);
		return S_OK;
	}
}