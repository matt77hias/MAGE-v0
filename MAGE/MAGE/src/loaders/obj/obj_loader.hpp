#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_output.hpp"
#include "mesh\mesh_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 Imports a mesh from the given OBJ file.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		fname
					A reference to the OBJ filename.
	 @param[in,out]	model_output
					A reference to the model output.
	 @param[in]		mesh_desc
					A reference to the mesh descriptor.
	 @throws		Exception
					Failed to import the mesh from file.
	 */
	template< typename VertexT, typename IndexT >
	void ImportOBJMeshFromFile(const wstring &fname, 
		ModelOutput< VertexT, IndexT > &model_output,
		const MeshDescriptor< VertexT, IndexT > &mesh_desc 
		    = MeshDescriptor< VertexT, IndexT >());
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\obj\obj_loader.tpp"

#pragma endregion