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
	void ImportModelFromFile(const wstring& fname, 
							 ResourceManager& resource_manager, 
							 ModelOutput< VertexT, IndexT >& model_output, 
							 const MeshDescriptor< VertexT, IndexT >& mesh_desc) {

		auto extension = GetFileExtension(fname);
		TransformToLowerCase(extension);

		if (L"mdl" == extension) {
			ImportMDLModelFromFile(fname, resource_manager, model_output);
		} 
		else if (L"obj" == extension) {
			ImportOBJMeshFromFile(fname, resource_manager, model_output, mesh_desc);
		}
		else {
			throw Exception("Unknown model file extension: %ls", fname.c_str());
		}
	}

	template< typename VertexT, typename IndexT >
	void ExportModelToFile(const wstring& fname, 
						   const ModelOutput< VertexT, IndexT >& model_output) {

		auto extension = GetFileExtension(fname);
		TransformToLowerCase(extension);

		if (L"mdl" == extension) {
			ExportMDLModelToFile(fname, model_output);
		}
		else {
			throw Exception("Unknown model file extension: %ls", fname.c_str());
		}
	}
}