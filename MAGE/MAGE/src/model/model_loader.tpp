#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_loader.hpp"
#include "mesh\obj\obj_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT ImportModelFromFile(const wstring &fname, ModelOutput< VertexT > &model_output, const MeshDescriptor< VertexT > &mesh_desc) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"mdl" || extension == L"MDL") {
			return ImportMDLModelFromFile(fname, model_output);
		}

		if (extension == L"obj" || extension == L"OBJ") {
			return ImportOBJMeshFromFile(fname, model_output, mesh_desc);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}

	template < typename VertexT >
	HRESULT ExportModelToFile(const wstring &fname, ModelOutput< VertexT > &model_output) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"mdl" || extension == L"MDL") {
			return ExportMDLModelToFile(fname, model_output);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}