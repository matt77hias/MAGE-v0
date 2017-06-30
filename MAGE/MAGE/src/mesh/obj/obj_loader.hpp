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
namespace mage {

	/**
	 Imports a mesh from the given OBJ file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the OBJ filename.
	 @param[in,out]	model_output
					A reference to the model output.
	 @param[in]		mesh_desc
					A reference to the mesh descriptor.
	 @throws		FormattedException
					Failed to import the mesh from file.
	 */
	template < typename VertexT >
	void ImportOBJMeshFromFile(const wstring &fname, ModelOutput< VertexT > &model_output, 
		const MeshDescriptor< VertexT > &mesh_desc = MeshDescriptor< VertexT >());
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj\obj_loader.tpp"

#pragma endregion