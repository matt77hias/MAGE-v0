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
namespace mage::rendering::loader {

	template< typename VertexT, typename IndexT >
	void ImportMDLModelFromFile(const std::filesystem::path& path,
								ResourceManager& resource_manager,
								ModelOutput< VertexT, IndexT >& model_output) {

		MDLReader< VertexT, IndexT > reader(resource_manager, model_output);
		reader.ReadFromFile(path);
	}

	template< typename VertexT, typename IndexT >
	void ExportMDLModelToFile(const std::filesystem::path& path,
							  const ModelOutput< VertexT, IndexT >& model_output) {

		MDLWriter< VertexT, IndexT > writer(model_output);
		writer.WriteToFile(path);
	}
}