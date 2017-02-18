#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\obj\obj_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Imports a mesh from an OBJ file.

	 @tparam		Vertex
					The vertex type.
	 @param[in]		fname
					A reference to the OBJ file name.
	 @param[in,out]	model_output
					A reference to the model output.
	 @param[in]		mesh_desc
					A reference to the mesh descriptor.
	 @return		A success/error value.
	 */
	template < typename Vertex >
	HRESULT ImportOBJMeshFromFile(const wstring &fname, ModelOutput< Vertex > &model_output, const MeshDescriptor &mesh_desc = MeshDescriptor()) {
		OBJReader< Vertex > reader(model_output, mesh_desc);
		return reader.ReadFromFile(fname);
	}
}