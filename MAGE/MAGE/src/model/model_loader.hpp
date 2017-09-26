#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_output.hpp"
#include "mesh\mesh_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports the model from the given file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the filename.
	 @param[in,out]	model_output
					A reference to the model output.
	 @param[in]		mesh_desc
					A reference to the mesh descriptor.
	 @throws		FormattedException
					Failed to import the model from file.
	 */
	template < typename VertexT >
	void ImportModelFromFile(const wstring &fname, 
		ModelOutput< VertexT > &model_output, 
		const MeshDescriptor< VertexT > &mesh_desc = MeshDescriptor< VertexT >());

	/**
	 Exports the model to the given file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the filename.
	 @param[in]		model_output
					A reference to the model output.
	 @throws		FormattedException
					Failed to export the model to file.
	 */
	template < typename VertexT >
	void ExportModelToFile(const wstring &fname, 
		const ModelOutput< VertexT > &model_output);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.tpp"

#pragma endregion