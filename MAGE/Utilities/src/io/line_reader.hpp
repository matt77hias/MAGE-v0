#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\token.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of line readers for reading (non-binary) text files line by line.
	 */
	class LineReader {

	public:

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given line reader to this line reader.

		 @param[in]		reader
						A reference to a line reader to copy.
		 @return		A reference to the copy of the given line reader (i.e. 
						this line reader).
		 */
		LineReader &operator=(const LineReader &reader) = delete;

		/**
		 Moves the given line reader to this line reader.

		 @param[in]		reader
						A reference to a line reader to move.
		 @return		A reference to the moved line reader (i.e. this line 
						reader).
		 */
		LineReader &operator=(LineReader &&reader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the given file.

		 @param[in]		fname
						The file name.
		 @param[in]		delimiters
						The string containing the token delimiters (single 
						characters).
		 @throws		Exception
						Failed to read from the given file.
		 */
		void ReadFromFile(wstring fname, 
			string delimiters = g_default_delimiters);
		
		/**
		 Reads the input string.

		 @pre			@a input is not equal to @c nullptr.
		 @param[in]		input
						A pointer to the input null-terminated byte string.
		 @param[in]		delimiters
						The string containing the token delimiters (single 
						characters).
		 @throws		Exception
						Failed to read from the given input string.
		 */
		void ReadFromMemory(const char *input, 
			                string delimiters = g_default_delimiters);

		/**
		 Returns the current filename of this line reader.

		 @return		A reference to the current filename of this line 
						reader.
		 */
		[[nodiscard]]
		const wstring &GetFilename() const noexcept {
			return m_fname;
		}

		/**
		 Returns the current delimiters of this line reader.

		 @return		A reference to the current delimiters of this line 
						reader.
		 */
		[[nodiscard]]
		const string &GetDelimiters() const noexcept {
			return m_delimiters;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a line reader.
		 */
		LineReader();

		/**
		 Constructs a line reader from the given line reader.

		 @param[in]		reader
						A reference to the line reader to copy.
		 */
		LineReader(const LineReader &reader) = delete;

		/**
		 Constructs a line reader by moving the given line reader.

		 @param[in]		reader
						A reference to the line reader to move.
		 */
		LineReader(LineReader &&reader) noexcept;

		/**
		 Destructs this line reader.
		 */
		~LineReader();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the current line number of this line reader.

		 @return		The current line number of this line reader.
		 */
		[[nodiscard]]
		U32 GetCurrentLineNumber() const noexcept {
			return m_line_number;
		}
		
		/**
		 Reads the remaining tokens of the current line of this line reader.
		 */
		void ReadLineRemaining();

		/**
		 Reads and converts the next token of this line reader to a string.

		 @return		The string represented by the next token of this line 
						reader.
		 @throws		Exception
						There is no next token.
		 */
		const char *ReadChars();

		/**
		 Reads and converts the next token of this line reader to a quoted 
		 string.

		 @return		The quoted string represented by the next token of this 
						line reader.
		 @throws		Exception
						There is no next token or the next token does not 
						represent a quoted string.
		 */
		const string ReadQuotedString();
		
		/**
		 Reads and converts the next token of this line reader to @c DataT 
		 element.

		 @tparam		DataT
						The data type.
		 @return		The @c DataT represented by the next token of this line 
						reader.
		 @throws		Exception
						There is no next token or the next token does not 
						represent a @c DataT element.
		 */
		template< typename DataT >
		const DataT Read();

		/**
		 Checks whether this line reader has a next token.

		 @return		@c true if this line reader has a next token. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool ContainsChars() const;
		
		/**
		 Checks whether the next token of this line reader is a quoted string.

		 @return		@c true if the next token of this line reader is a 
						quoted string. @c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsQuotedString() const;

		/**
		 Checks whether the next token of this line reader is a @c DataT 
		 element.

		 @tparam		DataT
						The data type.
		 @return		@c true if the next token of this line reader is a 
						@c DataT element. @c false otherwise.
		 */
		template< typename DataT >
		[[nodiscard]]
		bool Contains() const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current context of this line reader.
		 */
		char *m_context;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Pre-processes before reading the current file of this line reader.

		 @throws		Exception
						Failed to finish the pre-processing successfully.
		 */
		virtual void Preprocess() {}

		/**
		 Reads the given line.

		 @pre			@a line is not equal to @c nullptr.
		 @param[in,out] line
						A pointer to the null-terminated byte string to read.
		 @throws		Exception
						Failed to read the given line.
		 */
		virtual void ReadLine(char *line) = 0;

		/**
		 Post-processes after reading the current file of this line reader.

		 @throws		Exception
						Failed to finish post-processing successfully.
		 */
		virtual void Postprocess() {}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the file stream of this line reader.
		 */
		UniqueFileStream m_file_stream;

		/**
		 The current filename of this line reader.
		 */
		wstring m_fname;

		/**
		 The current delimiters of this line reader.
		 */
		string m_delimiters;

		/**
		 The current line number of this line reader.
		 */
		U32 m_line_number;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.tpp"

#pragma endregion