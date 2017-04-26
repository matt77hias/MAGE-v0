#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	class MSHReader final : public BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MSHReader(vector< VertexT > &vertices, vector< IndexT > &indices)
			: BigEndianBinaryReader(), m_vertices(vertices), m_indices(indices) {}
		MSHReader(const MSHReader &reader) = delete;
		MSHReader(MSHReader &&reader) = delete;
		virtual ~MSHReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		MSHReader &operator=(const MSHReader &reader) = delete;
		MSHReader &operator=(MSHReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Read() override;

		bool IsHeaderValid();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< VertexT > &m_vertices;
		vector< IndexT > &m_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_reader.tpp"

#pragma endregion