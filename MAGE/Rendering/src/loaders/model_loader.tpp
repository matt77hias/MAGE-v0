#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_loader.hpp"
#include "loaders\obj\obj_loader.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	void ImportModelFromFile(const wstring& fname, 
							 ResourceManager& resource_manager, 
							 ModelOutput< VertexT, IndexT >& model_output, 
							 const MeshDescriptor< VertexT, IndexT >& mesh_desc) {

		const auto extension = GetFileExtension(fname);

		if (extension == L"mdl" || extension == L"MDL") {
			ImportMDLModelFromFile(fname, resource_manager, model_output);
		} 
		else if (extension == L"obj" || extension == L"OBJ") {
			ImportOBJMeshFromFile(fname, resource_manager, model_output, mesh_desc);
		}
		else {
			throw Exception("Unknown model file extension: %ls", fname.c_str());
		}
	}

	template< typename VertexT, typename IndexT >
	void ExportModelToFile(const wstring& fname, 
						   const ModelOutput< VertexT, IndexT >& model_output) {

		const auto extension = GetFileExtension(fname);

		if (extension == L"mdl" || extension == L"MDL") {
			ExportMDLModelToFile(fname, model_output);
		}
		else {
			throw Exception("Unknown model file extension: %ls", fname.c_str());
		}
	}
}