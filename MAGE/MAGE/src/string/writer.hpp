#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of writers for writing (non-binary) text files.
	 */
	class Writer {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this writer.
		 */
		virtual ~Writer();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given writer to this writer.

		 @param[in]		writer
						A reference to a writer to copy.
		 @return		A reference to the copy of the given writer
						(i.e. this writer).
		 */
		Writer &operator=(const Writer &writer) = delete;

		/**
		 Moves the given writer to this writer.

		 @param[in]		writer
						A reference to a writer to move.
		 @return		A reference to the moved writer
						(i.e. this writer).
		 */
		Writer &operator=(Writer &&writer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes to the given file.

		 @param[in]		fname
						A reference to the file name.
		 @throws		FormattedException
						Failed to write to the given file.
		 */
		void WriteToFile(const wstring &fname);

		/**
		 Returns the current filename of this writer.

		 @return		A reference to the current filename of this writer.
		 */
		const wstring &GetFilename() const {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a writer.
		 */
		Writer()
			: m_file(nullptr), m_fname() {}

		/**
		 Constructs a writer from the given writer.

		 @param[in]		writer
						A reference to the writer to copy.
		 */
		Writer(const Writer &writer) = delete;

		/**
		 Constructs a writer by moving the given writer.

		 @param[in]		writer
						A reference to the writer to move.
		 */
		Writer(Writer &&writer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes the given character.

		 @param[in]		c
						The character to write.
		 @throws		FormattedException
						Failed to write the given character.
		 */
		void WriteCharacter(char c);

		/**
		 Writes the given string.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string to write.
		 @throws		FormattedException
						Failed to write the given string.
		 */
		void WriteString(const char *str);
		
		/**
		 Writes the given string.

		 @param[in]		str
						A reference to the string to write.
		 @throws		FormattedException
						Failed to write the given string.
		 */
		void WriteString(const string &str) {
			WriteString(str.c_str());
		}
		
		/**
		 Writes the given string and ends the current line.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string to write.
		 @throws		FormattedException
						Failed to write the given string.
		 */
		void WriteStringLine(const char *str);
		
		/**
		 Writes the given string and ends the current line.

		 @param[in]		str
						A reference to the string to write.
		 @throws		FormattedException
						Failed to write the given string.
		 */
		void WriteStringLine(const string &str) {
			WriteStringLine(str.c_str());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		FormattedException
						Failed to write.
		 */
		virtual void Write() = 0;

		/**
		 Closes the current file of this writer.
		 */
		void CloseFile();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current file of this writer.
		 */
		FILE *m_file;

		/**
		 The current filename of this writer.
		 */
		wstring m_fname;
	};
}