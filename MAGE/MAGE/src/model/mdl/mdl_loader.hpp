#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_output.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the model from the given MDL file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the MDL filename.
	 @param[in,out]	model_output
					A reference to the model output.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT ImportMDLModelFromFile(const wstring &fname,
		ModelOutput< VertexT > &model_output);

	/**
	 Exports the given model to the given MDL file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the MDL filename.
	 @param[in,out]	model_output
					A reference to the model output.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT ExportMDLModelToFile(const wstring &fname,
		const ModelOutput< VertexT > &model_output);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_loader.tpp"

#pragma endregion