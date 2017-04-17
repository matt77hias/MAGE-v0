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
	class MESHReader final : public BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MESHReader(vector< VertexT > &vertices, vector< IndexT > &indices)
			: BigEndianBinaryReader(), m_vertices(vertices), m_indices(indices) {}
		MESHReader(const VSReader &reader) = delete;
		MESHReader(MESHReader &&reader) = delete;
		virtual ~MESHReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		MESHReader &operator=(const MESHReader &reader) = delete;
		MESHReader &operator=(MESHReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Read() override;

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

#include "mesh\mesh\mesh_reader.tpp"

#pragma endregion