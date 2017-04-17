#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh\mesh_tokens.hpp"
#include "logging\error.hpp"

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
	MESHReader< VertexT, IndexT >::HRESULT Read() {

		if (!IsHeaderValid()) {
			Error("%ls: invalid sprite font header.", GetFilename().c_str());
			return E_FAIL;
		}

		const uint32_t nb_vertices = ReadValue< uint32_t >();
		const uint32_t nb_indices  = ReadValue< uint32_t >();
		
		const VertexT *vertices = ReadValueArray< VertexT >(nb_vertices);
		m_vertices.assign(vertices, vertices + nb_vertices);

		const IndexT *indices   = ReadValueArray< IndexT >(nb_indices);
		m_indices.assign(indices, indices + nb_indices);

		return S_OK;
	}

	template< typename VertexT, typename IndexT >
	bool MESHReader< VertexT, IndexT >::IsHeaderValid() {
		const char *magic = MAGE_MESH_MAGIC;
		while (*magic != L'\0') {
			if (ReadValue< uint8_t >() != *magic) {
				return false;
			}
			++magic;
		}
		return true;
	}
}