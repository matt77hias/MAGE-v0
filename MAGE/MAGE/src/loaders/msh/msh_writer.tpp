#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_tokens.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	MSHWriter< VertexT, IndexT >
		::MSHWriter(const std::vector< VertexT > &vertices, 
		            const std::vector< IndexT >  &indices)
		: BigEndianBinaryWriter(), 
		m_vertices(vertices), 
		m_indices(indices) {}

	template< typename VertexT, typename IndexT >
	MSHWriter< VertexT, IndexT >
		::MSHWriter(MSHWriter &&writer) noexcept = default;

	template< typename VertexT, typename IndexT >
	MSHWriter< VertexT, IndexT >::~MSHWriter() = default;

	template< typename VertexT, typename IndexT >
	void MSHWriter< VertexT, IndexT >::Write() {

		WriteString(g_msh_token_magic);

		const U32 nb_vertices = static_cast< U32 >(m_vertices.size());
		WriteValue(nb_vertices);
		const U32 nb_indices  = static_cast< U32 >(m_indices.size());
		WriteValue(nb_indices);
		
		WriteValueArray(m_vertices.data(), m_vertices.size());
		WriteValueArray(m_indices.data(), m_indices.size());
	}
}