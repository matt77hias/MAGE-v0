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
namespace mage::rendering {
	// Forward declaration.
	class ResourceManager;
}

namespace mage::rendering::loader {

	/**
	 Imports the model from the MDL file associated with the given path.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in]		path
					A reference to the path.
	 @param[in,out]	model_output
					A reference to the model output.
	 @throws		Exception
					Failed to import the model from file.
	 */
	template< typename VertexT, typename IndexT >
	void ImportMDLModelFromFile(const std::filesystem::path& path,
								const ResourceManager& resource_manager,
								ModelOutput< VertexT, IndexT >& model_output);

	/**
	 Exports the given model to the MDL file associated with the given path.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		path
					A reference to the path.
	 @param[in]		model_output
					A reference to the model output.
	 @throws		Exception
					Failed to export the model to file.
	 */
	template< typename VertexT, typename IndexT >
	void ExportMDLModelToFile(const std::filesystem::path& path,
							  const ModelOutput< VertexT, IndexT >& model_output);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_loader.tpp"

#pragma endregion