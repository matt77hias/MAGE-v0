#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_loader.hpp"
#include "loaders\obj\obj_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	template< typename VertexT, typename IndexT >
	void ImportModelFromFile(const std::filesystem::path& path, 
							 ResourceManager& resource_manager, 
							 ModelOutput< VertexT, IndexT >& model_output, 
							 const MeshDescriptor< VertexT, IndexT >& mesh_desc) {

		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".mdl" == extension) {
			ImportMDLModelFromFile(path, resource_manager, model_output);
		} 
		else if (L".obj" == extension) {
			ImportOBJMeshFromFile(path, resource_manager, model_output, mesh_desc);
		}
		else {
			throw Exception("Unknown model file extension: %ls", path.c_str());
		}
	}

	template< typename VertexT, typename IndexT >
	void ExportModelToFile(const std::filesystem::path& path, 
						   const ModelOutput< VertexT, IndexT >& model_output) {

		std::wstring extension(path.extension());
		TransformToLowerCase(extension);

		if (L".mdl" == extension) {
			ExportMDLModelToFile(path, model_output);
		}
		else {
			throw Exception("Unknown model file extension: %ls", path.c_str());
		}
	}
}