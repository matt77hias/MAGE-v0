#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_loader.hpp"
#include "mesh\obj\obj_loader.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	void ImportModelFromFile(const wstring &fname, ModelOutput< VertexT > &model_output, const MeshDescriptor< VertexT > &mesh_desc) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"mdl" || extension == L"MDL") {
			ImportMDLModelFromFile(fname, model_output);
		} 
		else if (extension == L"obj" || extension == L"OBJ") {
			ImportOBJMeshFromFile(fname, model_output, mesh_desc);
		}
		else {
			throw FormattedException("Unknown model file extension: %ls", fname.c_str());
		}
	}

	template < typename VertexT >
	void ExportModelToFile(const wstring &fname, const ModelOutput< VertexT > &model_output) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"mdl" || extension == L"MDL") {
			ExportMDLModelToFile(fname, model_output);
		}
		else {
			throw FormattedException("Unknown model file extension: %ls", fname.c_str());
		}
	}
}