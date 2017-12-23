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
	void MSHWriter< VertexT, IndexT >::WriteData() {

		WriteString(g_msh_token_magic);

		const U32 nb_vertices = static_cast< U32 >(m_vertices.size());
		Write< U32 >(nb_vertices);
		const U32 nb_indices  = static_cast< U32 >(m_indices.size());
		Write< U32 >(nb_indices);
		
		WriteArray(m_vertices.data(), m_vertices.size());
		WriteArray(m_indices.data(), m_indices.size());
	}
}