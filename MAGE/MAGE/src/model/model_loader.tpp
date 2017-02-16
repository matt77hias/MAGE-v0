#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj_loader.hpp"
#include "logging\error.hpp"
#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename Vertex >
	HRESULT LoadModelFromFile(const wstring &fname, ModelOutput< Vertex > &model_output, const MeshDescriptor &mesh_desc) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return ImportOBJMeshFromFile< Vertex >(fname, model_output, mesh_desc);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}