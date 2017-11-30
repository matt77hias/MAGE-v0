#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\line_reader.hpp"
#include "scripting\variable.hpp"
#include "utils\collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of VAR file readers for reading variable scripts.
	 */
	class VARReader final : public LineReader {

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
		explicit VARReader(map< string, Value > &variable_buffer);
		
		/**
		 Constructs a VAR reader from the given VAR reader.

		 @param[in]		reader
						A reference to the VAR reader to copy.
		 */
		VARReader(const VARReader &reader) = delete;
		
		/**
		 Constructs a VAR reader by moving the given VAR reader.

		 @param[in]		reader
						A reference to the VAR reader to move.
		 */
		VARReader(VARReader &&reader);

		/**
		 Destructs this VAR reader.
		 */
		virtual ~VARReader();

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
		VARReader &operator=(const VARReader &reader) = delete;

		/**
		 Moves the given VAR reader to this VAR reader.

		 @param[in]		reader
						A reference to a VAR reader to move.
		 @return		A reference to the moved VAR reader (i.e. this VAR 
						reader).
		 */
		VARReader &operator=(VARReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads the given line.

		 @pre			@a line is not equal to @c nullptr.
		 @param[in,out] line
						A pointer to the null-terminated byte string to read.
		 @throws		FormattedException
						Failed to read the given line.
		 */
		virtual void ReadLine(char *line) override;

		/**
		 Reads a Bool variable definition.

		 @throws		FormattedException
						Failed to read a Bool variable definition.
		 */
		void ReadVARBool();

		/**
		 Reads an Int variable definition.

		 @throws		FormattedException
						Failed to read a Int variable definition.
		 */
		void ReadVARInt();

		/**
		 Reads an Int2 variable definition.

		 @throws		FormattedException
						Failed to read a Int2 variable definition.
		 */
		void ReadVARInt2();

		/**
		 Reads an Int variable definition.

		 @throws		FormattedException
						Failed to read a Int3 variable definition.
		 */
		void ReadVARInt3();

		/**
		 Reads a Float variable definition.

		 @throws		FormattedException
						Failed to read a Float variable definition.
		 */
		void ReadVARFloat();

		/**
		 Reads a Float2 variable definition.

		 @throws		FormattedException
						Failed to read a Float2 variable definition.
		 */
		void ReadVARFloat2();

		/**
		 Reads a Float3 variable definition.

		 @throws		FormattedException
						Failed to read a Float3 variable definition.
		 */
		void ReadVARFloat3();

		/**
		 Reads a Float4 variable definition.

		 @throws		FormattedException
						Failed to read a Float4 variable definition.
		 */
		void ReadVARFloat4();

		/**
		 Reads a String variable definition.

		 @throws		FormattedException
						Failed to read a String variable definition.
		 */
		void ReadVARString();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a map containing the read variables of this VAR 
		 reader.
		 */
		map< string, Value > &m_variable_buffer;
	};
}