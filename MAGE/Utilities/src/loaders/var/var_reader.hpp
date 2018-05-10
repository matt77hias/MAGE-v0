#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "resource\script\variable_value.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 A class of VAR file readers for reading variable scripts.
	 */
	class VARReader final : private LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a VAR reader.

		 @param[in]		variable_buffer
						A reference to a map for storing the read variables 
						from file.
		 */
		explicit VARReader(std::map< string, Value >& variable_buffer);
		
		/**
		 Constructs a VAR reader from the given VAR reader.

		 @param[in]		reader
						A reference to the VAR reader to copy.
		 */
		VARReader(const VARReader& reader) = delete;
		
		/**
		 Constructs a VAR reader by moving the given VAR reader.

		 @param[in]		reader
						A reference to the VAR reader to move.
		 */
		VARReader(VARReader&& reader) noexcept;

		/**
		 Destructs this VAR reader.
		 */
		~VARReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given VAR reader to this VAR reader.

		 @param[in]		reader
						A reference to a VAR reader to copy.
		 @return		A reference to the copy of the given VAR reader (i.e. 
						this VAR reader).
		 */
		VARReader& operator=(const VARReader& reader) = delete;

		/**
		 Moves the given VAR reader to this VAR reader.

		 @param[in]		reader
						A reference to a VAR reader to move.
		 @return		A reference to the moved VAR reader (i.e. this VAR 
						reader).
		 */
		VARReader& operator=(VARReader&& reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		using LineReader::ReadFromFile;

		using LineReader::ReadFromMemory;

		using LineReader::GetPath;

		using LineReader::GetDelimiters;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads the given line.

		 @param[in,out] line
						A pointer to the null-terminated string to read.
		 @throws		Exception
						Failed to read the given line.
		 */
		virtual void ReadLine(NotNull< zstring > line) override;

		/**
		 Reads a variable definition.

		 @tparam		T
						The variable type.
		 @throws		Exception
						Failed to read a variable definition.
		 */
		template< typename T >
		void ReadVARVariable();

		/**
		 Reads an array variable definition.

		 @tparam		T
						The variable type.
		 @tparam		N
						The number of values in the array.
		@tparam			A
						The alignment of the array.
		 @throws		Exception
						Failed to read an array variable definition.
		 */
		template< typename T, size_t N, size_t A = alignof(T) >
		void ReadVARVariable();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a map containing the read variables of this VAR reader.
		 */
		std::map< string, Value >& m_variable_buffer;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_reader.tpp"

#pragma endregion