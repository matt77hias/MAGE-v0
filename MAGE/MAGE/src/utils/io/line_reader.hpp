#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\string\token.hpp"

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
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this line reader.
		 */
		virtual ~LineReader();

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
		LineReader &operator=(LineReader &&reader) = delete;

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
		 @throws		FormattedException
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
		 @throws		FormattedException
						Failed to read from the given input string.
		 */
		void ReadFromMemory(const char *input, 
			string delimiters = g_default_delimiters);

		/**
		 Returns the current filename of this line reader.

		 @return		A reference to the current filename of this line 
						reader.
		 */
		const wstring &GetFilename() const noexcept {
			return m_fname;
		}

		/**
		 Returns the current delimiters of this line reader.

		 @return		A reference to the current delimiters of this line 
						reader.
		 */
		const string &GetDelimiters() const noexcept {
			return m_delimiters;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
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
		LineReader(LineReader &&reader);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the current line number of this line reader.

		 @return		The current line number of this line reader.
		 */
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
		 @throws		FormattedException
						There is no next token.
		 */
		const char *ReadChars();

		/**
		 Reads and converts the next token of this line reader to a string.

		 @return		The string represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token.
		 */
		const string ReadString();
		
		/**
		 Reads and converts the next token of this line reader to a quoted 
		 string.

		 @return		The quoted string represented by the next token of this 
						line reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a quoted string.
		 */
		const string ReadQuotedString();
		
		/**
		 Reads and converts the next token of this line reader to a @c bool.

		 @return		The @c bool represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c bool.
		 */
		bool ReadBool();

		/**
		 Reads and converts the next token of this line reader to a @c S8.

		 @return		The @c S8 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c S8.
		 */
		S8 ReadS8();

		/**
		 Reads and converts the next token of this line reader to an @c U8.

		 @return		The @c U8 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent an @c U8.
		 */
		U8 ReadU8();

		/**
		 Reads and converts the next token of this line reader to a @c S16.

		 @return		The @c S16 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c S16.
		 */
		S16 ReadS16();

		/**
		 Reads and converts the next token of this line reader to an @c U16.

		 @return		The @c U16 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent an @c U16.
		 */
		U16 ReadU16();

		/**
		 Reads and converts the next token of this line reader to a @c S32.

		 @return		The @c S32 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c S32.
		 */
		S32 ReadS32();

		/**
		 Reads and converts the next token of this line reader to an @c U32.

		 @return		The @c U32 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent an @c U32.
		 */
		U32 ReadU32();

		/**
		 Reads and converts the next token of this line reader to a @c S64.

		 @return		The @c S64 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c S64.
		 */
		S64 ReadS64();

		/**
		 Reads and converts the next token of this line reader to an @c U64.

		 @return		The @c U64 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent an @c U64.
		 */
		U64 ReadU64();

		/**
		 Reads and converts the next token of this line reader to an @c F32.

		 @return		The @c F32 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent an @c F32.
		 */
		F32 ReadF32();

		/**
		 Reads and converts the next token of this line reader to an @c F64.

		 @return		The @c F64 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent an @c F64.
		 */
		F64 ReadF64();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT2.

		 @return		The @c XMFLOAT2 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c XMFLOAT2.
		 */
		const XMFLOAT2 ReadF32x2();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT3.

		 @return		The @c XMFLOAT3 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c XMFLOAT3.
		 */
		const XMFLOAT3 ReadF32x3();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT4.

		 @return		The @c XMFLOAT4 represented by the next token of this line 
						reader.
		 @throws		FormattedException
						There is no next token or the next token does not 
						represent a @c XMFLOAT4.
		*/
		const XMFLOAT4 ReadF32x4();
		
		/**
		 Checks whether this line reader has a next token.

		 @return		@c true if this line reader has a next token. @c false
						otherwise.
		 */
		bool HasChars() const;
		
		/**
		 Checks whether the next token of this line reader is a string.

		 @return		@c true if the next token of this line reader is a 
						string. @c false otherwise.
		 */
		bool HasString() const;
		
		/**
		 Checks whether the next token of this line reader is a quoted string.

		 @return		@c true if the next token of this line reader is a 
						quoted string. @c false otherwise.
		 */
		bool HasQuotedString() const;

		/**
		 Checks whether the next token of this line reader is a @c bool.

		 @return		@c true if the next token of this line reader is a 
						@c bool. @c false otherwise.
		 */
		bool HasBool() const;

		/**
		 Checks whether the next token of this line reader is a @c S8.

		 @return		@c true if the next token of this line reader is an 
						@c S8. @c false otherwise.
		 */
		bool HasS8() const;

		/**
		 Checks whether the next token of this line reader is an @c U8.
 
		 @return		@c true if the next token of this line reader is an 
						@c U8. @c false otherwise.
		 */
		bool HasU8() const;

		/**
		 Checks whether the next token of this line reader is a @c S16.

		 @return		@c true if the next token of this line reader is an 
						@c S16. @c false otherwise.
		 */
		bool HasS16() const;

		/**
		 Checks whether the next token of this line reader is an @c U16.

		 @return		@c true if the next token of this line reader is an 
						@c U16. @c false otherwise.
		 */
		bool HasU16() const;

		/**
		 Checks whether the next token of this line reader is a @c S32.

		 @return		@c true if the next token of this line reader is an 
						@c S32. @c false otherwise.
		*/
		bool HasS32() const;

		/**
		 Checks whether the next token of this line reader is an @c U32.

		 @return		@c true if the next token of this line reader is an 
						@c U32. @c false otherwise.
		 */
		bool HasU32() const;

		/**
		 Checks whether the next token of this line reader is a @c S64.

		 @return		@c true if the next token of this line reader is an
						@c S64. @c false otherwise.
		 */
		bool HasS64() const;

		/**
		 Checks whether the next token of this line reader is an @c U64.

		 @return		@c true if the next token of this line reader is an 
						@c U64. @c false otherwise.
		 */
		bool HasU64() const;

		/**
		 Checks whether the next token of this line reader is an @c F32.

		 @return		@c true if the next token of this line reader is an 
						@c F32. @c false otherwise.
		 */
		bool HasF32() const;

		/**
		 Checks whether the next token of this line reader is an @c F64.

		 @return		@c true if the next token of this line reader is an 
						@c F64. @c false otherwise.
		 */
		bool HasF64() const;

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

		 @throws		FormattedException
						Failed to finish the pre-processing successfully.
		 */
		virtual void Preprocess() {}

		/**
		 Reads the given line.

		 @pre			@a line is not equal to @c nullptr.
		 @param[in,out] line
						A pointer to the null-terminated byte string to read.
		 @throws		FormattedException
						Failed to read the given line.
		 */
		virtual void ReadLine(char *line) = 0;

		/**
		 Post-processes after reading the current file of this line reader.

		 @throws		FormattedException
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