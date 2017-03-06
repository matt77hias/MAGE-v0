#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_output.hpp"
#include "mesh\mesh_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Loads a mesh from file.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		fname
					A reference to the filename.
	 @param[in,out]	model_output
					A reference to the model output.
	 @param[in]		mesh_desc
					A reference to the mesh descriptor.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT LoadModelFromFile(const wstring &fname, ModelOutput< VertexT > &model_output, const MeshDescriptor< VertexT > &mesh_desc = MeshDescriptor< VertexT >());
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.tpp"

#pragma endregion