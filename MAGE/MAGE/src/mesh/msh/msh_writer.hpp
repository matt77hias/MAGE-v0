#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_writer.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	class MSHWriter final : public BigEndianBinaryWriter {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MSHWriter(const vector< VertexT > &vertices, const vector< IndexT > &indices)
			: BigEndianBinaryWriter(), m_vertices(vertices), m_indices(indices) {}
		MSHWriter(const MSHWriter &writer) = delete;
		MSHWriter(MSHWriter &&writer) = delete;
		virtual ~MSHWriter() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		MSHWriter &operator=(const MSHWriter &writer) = delete;
		MSHWriter &operator=(MSHWriter &&writer) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Write() override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		const vector< VertexT > &m_vertices;
		const vector< IndexT > &m_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_writer.tpp"

#pragma endregion