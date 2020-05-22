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
namespace mage::rendering::loader {

	template< typename VertexT, typename IndexT >
	MSHWriter< VertexT, IndexT >
		::MSHWriter(const std::vector< VertexT >& vertices,
		            const std::vector< IndexT >& indices)
		: BigEndianBinaryWriter(),
		m_vertices(vertices),
		m_indices(indices) {}

	template< typename VertexT, typename IndexT >
	MSHWriter< VertexT, IndexT >
		::MSHWriter(MSHWriter&& writer) noexcept = default;

	template< typename VertexT, typename IndexT >
	MSHWriter< VertexT, IndexT >::~MSHWriter() = default;

	template< typename VertexT, typename IndexT >
	void MSHWriter< VertexT, IndexT >::WriteData() {

		WriteString(NotNull< const_zstring >(g_msh_token_magic));

		const auto nb_vertices = static_cast< U32 >(m_vertices.size());
		Write< U32 >(nb_vertices);
		const auto nb_indices  = static_cast< U32 >(m_indices.size());
		Write< U32 >(nb_indices);

		WriteArray(gsl::make_span(m_vertices));
		WriteArray(gsl::make_span(m_indices));
	}
}