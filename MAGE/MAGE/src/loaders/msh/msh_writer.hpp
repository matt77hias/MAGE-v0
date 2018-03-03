#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_writer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 A class of MSH file writers for writing meshes.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.

	 */
	template< typename VertexT, typename IndexT >
	class MSHWriter final : private BigEndianBinaryWriter {

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
		explicit MSHWriter(const std::vector< VertexT >& vertices, 
			               const std::vector< IndexT > & indices);
		
		/**
		 Constructs a MSH writer from the given MSH writer.

		 @param[in]		writer
						A reference to the MSH writer to copy.
		 */
		MSHWriter(const MSHWriter& writer) = delete;

		/**
		 Constructs a MSH writer by moving the given MSH writer.

		 @param[in]		writer
						A reference to the MSH writer to move.
		 */
		MSHWriter(MSHWriter&& writer) noexcept;

		/**
		 Destructs this MSH writer.
		 */
		~MSHWriter();

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
		MSHWriter& operator=(const MSHWriter& writer) = delete;

		/**
		 Moves the given MSH writer to this MSH writer.

		 @param[in]		writer
						A reference to a MSH writer to move.
		 @return		A reference to the moved MSH writer (i.e. this MSH 
						writer).
		 */
		MSHWriter& operator=(MSHWriter&& writer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		using BigEndianBinaryWriter::WriteToFile;

		using BigEndianBinaryWriter::GetFilename;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		Exception
						Failed to write.
		 */
		virtual void WriteData() override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a vector containing the vertices to write by this VS 
		 writer.
		 */
		const std::vector< VertexT >& m_vertices;
		
		/**
		 A reference to a vector containing the indices to write by this VS 
		 writer.
		 */
		const std::vector< IndexT >& m_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\msh\msh_writer.tpp"

#pragma endregion