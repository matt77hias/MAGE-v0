#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh\mesh_tokens.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	HRESULT MESHWriter< VertexT, IndexT >::Write() {

		Write(MAGE_MESH_MAGIC);

		const uint32_t nb_vertices = static_cast< uint32_t >(vertices.size());
		const uint32_t nb_indices  = static_cast< uint32_t >(indices.size());
		WriteValue(nb_vertices);
		WriteValue(nb_indices);
		
		WriteValueArray(vertices.get(), vertices.size());
		WriteValueArray(indices.get(), indices.size());
		
		return S_OK;
	}
}