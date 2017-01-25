//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"
#include "file\file_utils.hpp"
#include "model\model_loader.hpp"
#include "model\obj_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT LoadModelFromFile(const string &fname,
		vector< Vertex > &vertex_buffer, vector< uint32_t > &index_buffer) {

		const string extension = GetFileExtension(fname);
		
		if (extension == "obj" || extension == "OBJ") {
			return LoadOBJModelFromFile(fname, vertex_buffer, index_buffer);
		}
		
		Warning("Unknown model file extension: %s", fname.c_str());
		return E_FAIL;
	}
}