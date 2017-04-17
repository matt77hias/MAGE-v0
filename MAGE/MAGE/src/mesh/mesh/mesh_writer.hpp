#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename VertexT, typename IndexT >
	class MESHWriter final : public Writer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MESHWriter(const vector< VertexT > &vertices, const vector< IndexT > &indices)
			: Writer(), m_vertices(vertices), m_indices(indices) {}
		MESHWriter(const MESHWriter &writer) = delete;
		MESHWriter(MESHWriter &&writer) = delete;
		virtual ~MESHWriter() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		MESHWriter &operator=(const MESHWriter &writer) = delete;
		MESHWriter &operator=(MESHWriter &&writer) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Write() override;

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

#include "mesh\mesh\mesh_writer.tpp"

#pragma endregion