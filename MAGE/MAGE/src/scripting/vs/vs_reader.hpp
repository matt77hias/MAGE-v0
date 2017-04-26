#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "collection\collection.hpp"
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of VS file readers for reading variable scripts.
	 */
	class VSReader final : public LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a VS reader.

		 @param[in]		variable_buffer
						A reference to a vector for storing the read variables
						from file.
		 */
		explicit VSReader(vector< Variable > &variable_buffer)
			: LineReader(), m_variable_buffer(variable_buffer) {}
		
		/**
		 Constructs a VS reader from the given VS reader.

		 @param[in]		reader
						A reference to the VS reader to copy.
		 */
		VSReader(const VSReader &reader) = delete;
		
		/**
		 Constructs a VS reader by moving the given VS reader.

		 @param[in]		reader
						A reference to the VS reader to move.
		 */
		VSReader(VSReader &&reader) = delete;

		/**
		 Destructs this VS reader.
		 */
		virtual ~VSReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given VS reader to this VS reader.

		 @param[in]		reader
						A reference to a VS reader to copy.
		 @return		A reference to the copy of the given VS reader
						(i.e. this VS reader).
		 */
		VSReader &operator=(const VSReader &reader) = delete;

		/**
		 Moves the given VS reader to this VS reader.

		 @param[in]		reader
						A reference to a VS reader to move.
		 @return		A reference to the moved VS reader
						(i.e. this VS reader).
		 */
		VSReader &operator=(VSReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads the given line.

		 @param[in,out] line
						A pointer to the null-terminated byte string to read.
		 @throws		FormattedException
						The reading of the line failed.
		 */
		virtual void ReadLine(char *line) override;

		/**
		 Reads a Bool variable.

		 @throws		FormattedException
						The reading of the Bool variable failed.
		 */
		void ReadVSBool();

		/**
		 Reads an Int variable.

		 @throws		FormattedException
						The reading of the Int variable failed.
		 */
		void ReadVSInt();

		/**
		 Reads an Int2 variable.

		 @throws		FormattedException
						The reading of the Int2 variable failed.
		 */
		void ReadVSInt2();

		/**
		 Reads an Int variable.

		 @throws		FormattedException
						The reading of the Int3 variable failed.
		 */
		void ReadVSInt3();

		/**
		 Reads a Float variable.

		 @throws		FormattedException
						The reading of the Float variable failed.
		 */
		void ReadVSFloat();

		/**
		 Reads a Float2 variable.

		 @throws		FormattedException
						The reading of the Float2 variable failed.
		 */
		void ReadVSFloat2();

		/**
		 Reads a Float3 variable.

		 @throws		FormattedException
						The reading of the Float3 variable failed.
		 */
		void ReadVSFloat3();

		/**
		 Reads a Float4 variable.

		 @throws		FormattedException
						The reading of the Float4 variable failed.
		 */
		void ReadVSFloat4();

		/**
		 Reads a Color variable.

		 @throws		FormattedException
						The reading of the Color variable failed.
		 */
		void ReadVSColor();

		/**
		 Reads a String variable.

		 @throws		FormattedException
						The reading of the String variable failed.
		 */
		void ReadVSString();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a vector containing the read variables of this VS reader.
		 */
		vector< Variable > &m_variable_buffer;
	};
}