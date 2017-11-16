#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\binary_writer.hpp"
#include "utils\collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of MSH file writers for writing meshes.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.

	 */
	template< typename VertexT, typename IndexT >
	class MSHWriter final : public BigEndianBinaryWriter {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a MSH writer.

		 @param[in]		vertices
						A reference to a vector containing the vertices.
		 @param[in]		indices
						A reference to a vector containing the indices.
		 */
		explicit MSHWriter(
			const vector< VertexT > &vertices, const vector< IndexT > &indices);
		
		/**
		 Constructs a MSH writer from the given MSH writer.

		 @param[in]		writer
						A reference to the MSH writer to copy.
		 */
		MSHWriter(const MSHWriter< VertexT, IndexT > &writer) = delete;

		/**
		 Constructs a MSH writer by moving the given MSH writer.

		 @param[in]		writer
						A reference to the MSH writer to move.
		 */
		MSHWriter(MSHWriter< VertexT, IndexT > &&writer);

		/**
		 Destructs this MSH writer.
		 */
		virtual ~MSHWriter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given MSH writer to this MSH writer.

		 @param[in]		writer
						A reference to a MSH writer to copy.
		 @return		A reference to the copy of the given MSH writer (i.e. 
						this MSH writer).
		 */
		MSHWriter< VertexT, IndexT > &operator=(
			const MSHWriter< VertexT, IndexT > &writer) = delete;

		/**
		 Moves the given MSH writer to this MSH writer.

		 @param[in]		writer
						A reference to a MSH writer to move.
		 @return		A reference to the moved MSH writer (i.e. this MSH 
						writer).
		 */
		MSHWriter< VertexT, IndexT > &operator=(
			MSHWriter< VertexT, IndexT > &&writer) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		FormattedException
						Failed to write.
		 */
		virtual void Write() override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a vector containing the vertices to write by this VS 
		 writer.
		 */
		const vector< VertexT > &m_vertices;
		
		/**
		 A reference to a vector containing the indices to write by this VS 
		 writer.
		 */
		const vector< IndexT > &m_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_writer.tpp"

#pragma endregion