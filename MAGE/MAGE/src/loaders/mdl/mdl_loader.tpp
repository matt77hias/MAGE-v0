#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_reader.hpp"
#include "loaders\mdl\mdl_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	void ImportMDLModelFromFile(const wstring &fname,
		ModelOutput< VertexT, IndexT > &model_output) {
		
		MDLReader< VertexT, IndexT > reader(model_output);
		reader.ReadFromFile(fname);
	}

	template< typename VertexT, typename IndexT >
	void ExportMDLModelToFile(const wstring &fname,
		const ModelOutput< VertexT, IndexT > &model_output) {
		
		MDLWriter< VertexT, IndexT > writer(model_output);
		writer.WriteToFile(fname);
	}
}