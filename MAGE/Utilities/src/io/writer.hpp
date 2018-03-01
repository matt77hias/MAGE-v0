#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

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
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given writer to this writer.

		 @param[in]		writer
						A reference to a writer to copy.
		 @return		A reference to the copy of the given writer (i.e. this 
						writer).
		 */
		Writer &operator=(const Writer &writer) = delete;

		/**
		 Moves the given writer to this writer.

		 @param[in]		writer
						A reference to a writer to move.
		 @return		A reference to the moved writer (i.e. this writer).
		 */
		Writer &operator=(Writer &&writer) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes to the given file.

		 @param[in]		fname
						The file name.
		 @throws		Exception
						Failed to write to the given file.
		 */
		void WriteToFile(wstring fname);

		/**
		 Returns the current filename of this writer.

		 @return		A reference to the current filename of this writer.
		 */
		[[nodiscard]]const wstring &GetFilename() const noexcept {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a writer.
		 */
		Writer();

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
		Writer(Writer &&writer) noexcept;

		/**
		 Destructs this writer.
		 */
		~Writer();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes the given character.

		 @param[in]		c
						The character to write.
		 @throws		Exception
						Failed to write the given character.
		 */
		void WriteCharacter(char c);

		/**
		 Writes the given string.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string to 
						write.
		 @throws		Exception
						Failed to write the given string.
		 */
		void WriteString(const char *str);
		
		/**
		 Writes the given string.

		 @param[in]		str
						A reference to the string to write.
		 @throws		Exception
						Failed to write the given string.
		 */
		void WriteString(const string &str) {
			WriteString(str.c_str());
		}
		
		/**
		 Writes the given string and ends the current line.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string to 
						write.
		 @throws		Exception
						Failed to write the given string.
		 */
		void WriteStringLine(const char *str);
		
		/**
		 Writes the given string and ends the current line.

		 @param[in]		str
						A reference to the string to write.
		 @throws		Exception
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

		 @throws		Exception
						Failed to write.
		 */
		virtual void Write() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the file stream of this writer.
		 */
		UniqueFileStream m_file_stream;

		/**
		 The current filename of this writer.
		 */
		wstring m_fname;
	};
}