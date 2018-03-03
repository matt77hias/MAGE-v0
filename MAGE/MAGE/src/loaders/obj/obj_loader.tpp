#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\obj\obj_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	void ImportOBJMeshFromFile(const wstring& fname, 
							   ResourceManager& resource_manager, 
							   ModelOutput< VertexT, IndexT >& model_output, 
							   const MeshDescriptor< VertexT, IndexT >& mesh_desc) {
		
		OBJReader< VertexT, IndexT > reader(resource_manager, model_output, mesh_desc);
		reader.ReadFromFile(fname);
	}
}