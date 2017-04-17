#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_tokens.hpp"

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
	HRESULT MSHWriter< VertexT, IndexT >::Write() {

		WriteString(MAGE_MSH_MAGIC);

		const uint32_t nb_vertices = static_cast< uint32_t >(m_vertices.size());
		const uint32_t nb_indices  = static_cast< uint32_t >(m_indices.size());
		WriteValue(nb_vertices);
		WriteValue(nb_indices);
		
		WriteValueArray(m_vertices.data(), m_vertices.size());
		WriteValueArray(m_indices.data(), m_indices.size());
		
		return S_OK;
	}
}