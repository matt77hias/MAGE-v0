#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\model\model_output.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	// Forward declaration.
	class ResourceManager;

	/**
	 Imports the model from the given MDL file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		fname
					A reference to the MDL filename.
	 @param[out]	model_output
					A reference to the model output.
	 @throws		Exception
					Failed to import the model from file.
	 */
	template< typename VertexT, typename IndexT >
	void ImportMDLModelFromFile(const wstring& fname, 
								const ResourceManager& resource_manager, 
								ModelOutput< VertexT, IndexT >& model_output);

	/**
	 Exports the given model to the given MDL file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		fname
					A reference to the MDL filename.
	 @param[in]		model_output
					A reference to the model output.
	 @throws		Exception
					Failed to export the model to file.
	 */
	template< typename VertexT, typename IndexT >
	void ExportMDLModelToFile(const wstring& fname, 
							  const ModelOutput< VertexT, IndexT >& model_output);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_loader.tpp"

#pragma endregion