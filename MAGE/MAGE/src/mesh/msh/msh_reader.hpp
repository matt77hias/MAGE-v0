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

	/**
	 A class of MSH file readers for reading meshes.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT >
	class MSHReader final : public BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a MSH reader.

		 @param[in]		vertices
						A reference to a vector for storing the read vertices
						from file.
		 @param[in]		indices
						A reference to a vector for storing the read indices
						from file.
		 */
		explicit MSHReader(vector< VertexT > &vertices, vector< IndexT > &indices);

		/**
		 Constructs a MSH reader from the given MSH reader.

		 @param[in]		reader
						A reference to the MSH reader to copy.
		 */
		MSHReader(const MSHReader &reader) = delete;

		/**
		 Constructs a MSH reader by moving the given MSH reader.

		 @param[in]		reader
						A reference to the MSH reader to move.
		 */
		MSHReader(MSHReader &&reader) = delete;

		/**
		 Destructs this MSH reader.
		 */
		virtual ~MSHReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given MSH reader to this MSH reader.

		 @param[in]		reader
						A reference to a MSH reader to copy.
		 @return		A reference to the copy of the given MSH reader
						(i.e. this MSH reader).
		 */
		MSHReader &operator=(const MSHReader &reader) = delete;

		/**
		 Moves the given MSH reader to this MSH reader.

		 @param[in]		reader
						A reference to a MSH reader to move.
		 @return		A reference to the moved MSH reader
						(i.e. this MSH reader).
		 */
		MSHReader &operator=(MSHReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		FormattedException
						Failed to read to the given file.
		 */
		virtual void Read() override;

		/**
		 Checks whether the header of the file is valid.

		 @return		@c true if the header of the file is valid.
						@c false otherwise.
		 */
		bool IsHeaderValid();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a vector containing the read vertices of this MSH reader.
		 */
		vector< VertexT > &m_vertices;

		/**
		 A reference to a vector containing the read indices of this MSH reader.
		 */
		vector< IndexT > &m_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\msh\msh_reader.tpp"

#pragma endregion