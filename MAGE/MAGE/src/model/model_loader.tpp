#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj\obj_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	HRESULT LoadModelFromFile(const wstring &fname, ModelOutput< VertexT > &model_output, const MeshDescriptor< VertexT > &mesh_desc) {

		const wstring extension = GetFileExtension(fname);

		if (extension == L"obj" || extension == L"OBJ") {
			return ImportOBJMeshFromFile< VertexT >(fname, model_output, mesh_desc);
		}

		Warning("Unknown model file extension: %ls", fname.c_str());
		return E_FAIL;
	}
}