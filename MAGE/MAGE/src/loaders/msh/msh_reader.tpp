#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_tokens.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	template< typename VertexT, typename IndexT >
	MSHReader< VertexT, IndexT >
		::MSHReader(std::vector< VertexT > &vertices, 
		            std::vector< IndexT >  &indices)
		: BigEndianBinaryReader(), 
		m_vertices(vertices), 
		m_indices(indices) {}

	template< typename VertexT, typename IndexT >
	MSHReader< VertexT, IndexT >::MSHReader(
		MSHReader &&reader) noexcept = default;

	template< typename VertexT, typename IndexT >
	MSHReader< VertexT, IndexT >::~MSHReader() = default;

	template< typename VertexT, typename IndexT >
	void MSHReader< VertexT, IndexT >::ReadData() {

		// Read the header.
		{
			const bool result = IsHeaderValid();
			ThrowIfFailed(result, 
				"%ls: invalid mesh header.", GetFilename().c_str());
		}

		const U32 nb_vertices = Read< U32 >();
		const U32 nb_indices  = Read< U32 >();
		
		const VertexT *vertices = ReadArray< VertexT >(nb_vertices);
		m_vertices.assign(vertices, vertices + nb_vertices);

		const IndexT *indices   = ReadArray< IndexT >(nb_indices);
		m_indices.assign(indices, indices + nb_indices);
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]] bool MSHReader< VertexT, IndexT >::IsHeaderValid() {
		const char *magic = g_msh_token_magic;
		
		while (*magic != L'\0') {
			if (Read< U8 >() != *magic) {
				return false;
			}
			++magic;
		}
		
		return true;
	}
}