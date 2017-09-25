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
		 @return		A reference to the copy of the given line reader
						(i.e. this line reader).
		 */
		LineReader &operator=(const LineReader &reader) = delete;

		/**
		 Moves the given line reader to this line reader.

		 @param[in]		reader
						A reference to a line reader to move.
		 @return		A reference to the moved line reader
						(i.e. this line reader).
		 */
		LineReader &operator=(LineReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the given file.

		 @param[in]		fname
						A reference to the file name.
		 @param[in]		delimiters
						A reference to a string containing the token delimiters
						(single characters).
		 @throws		FormattedException
						Failed to read from the given file.
		 */
		void ReadFromFile(const wstring &fname, const string &delimiters = mage_default_delimiters);
		
		/**
		 Reads the input string.

		 @pre			@a input is not equal to @c nullptr.
		 @param[in]		input
						A pointer to the input null-terminated byte string.
		 @param[in]		delimiters
						A reference to a string containing the token delimiters
						(single characters).
		 @throws		FormattedException
						Failed to read from the given input string.
		 */
		void ReadFromMemory(const char *input, const string &delimiters = mage_default_delimiters);

		/**
		 Returns the current filename of this line reader.

		 @return		A reference to the current filename of this line reader.
		 */
		const wstring &GetFilename() const noexcept {
			return m_fname;
		}

		/**
		 Returns the current delimiters of this line reader.

		 @return		A reference to the current delimiters of this line reader.
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
		u32 GetCurrentLineNumber() const noexcept {
			return m_line_number;
		}
		
		/**
		 Reads the remaining tokens of the current line of this line reader.
		 */
		void ReadLineRemaining();

		/**
		 Reads and converts the next token of this line reader to a string.

		 @return		The string represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token.
		 */
		const char *ReadChars();

		/**
		 Reads and converts the next token of this line reader to a string.

		 @return		The string represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token.
		 */
		const string ReadString();

		/**
		 Reads and converts the next token of this line reader to a quoted string.

		 @return		The quoted string represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a quoted string.
		 */
		const string ReadQuotedString();

		/**
		 Reads and converts the next token of this line reader to a @c bool.

		 @return		The @c bool represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c bool.
		 */
		bool ReadBool();

		/**
		 Reads and converts the next token of this line reader to a @c i8.

		 @return		The @c i8 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c i8.
		 */
		i8 ReadI8();

		/**
		 Reads and converts the next token of this line reader to a @c u8.

		 @return		The @c u8 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c u8.
		 */
		u8 ReadU8();

		/**
		 Reads and converts the next token of this line reader to a @c i16.

		 @return		The @c i16 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c i16.
		 */
		i16 ReadI16();

		/**
		 Reads and converts the next token of this line reader to a @c u16.

		 @return		The @c u16 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c u16.
		 */
		u16 ReadU16();

		/**
		 Reads and converts the next token of this line reader to a @c i32.

		 @return		The @c i32 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c i32.
		 */
		i32 ReadI32();

		/**
		 Reads and converts the next token of this line reader to a @c u32.

		 @return		The @c u32 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c u32.
		 */
		u32 ReadU32();

		/**
		 Reads and converts the next token of this line reader to a @c i64.

		 @return		The @c i64 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c i64.
		 */
		i64 ReadI64();

		/**
		 Reads and converts the next token of this line reader to a @c u64.

		 @return		The @c u64 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c u64.
		 */
		u64 ReadU64();

		/**
		 Reads and converts the next token of this line reader to a @c float.

		 @return		The @c float represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c float.
		 */
		float ReadF32();

		/**
		 Reads and converts the next token of this line reader to a @c f64.

		 @return		The @c f64 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c f64.
		 */
		f64 ReadF64();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT2.

		 @return		The @c XMFLOAT2 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c XMFLOAT2.
		 */
		const XMFLOAT2 ReadFloat2();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT3.

		 @return		The @c XMFLOAT3 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c XMFLOAT3.
		 */
		const XMFLOAT3 ReadFloat3();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT4.

		 @return		The @c XMFLOAT4 represented by the next token of this line reader.
		 @throws		FormattedException
						There is no next token or the next token does not represent
						a @c XMFLOAT4.
		*/
		const XMFLOAT4 ReadFloat4();

		/**
		 Checks whether this line reader has a next token.

		 @return		@c true if this line reader has a next token.
						@c false otherwise.
		 */
		bool HasChars() const;

		/**
		 Checks whether the next token of this line reader is a string.

		 @return		@c true if the next token of this line reader is a string.
						@c false otherwise.
		 */
		bool HasString() const;

		/**
		 Checks whether the next token of this line reader is a quoted string.

		 @return		@c true if the next token of this line reader is a quoted string.
						@c false otherwise.
		 */
		bool HasQuotedString() const;

		/**
		 Checks whether the next token of this line reader is a @c bool.

		 @return		@c true if the next token of this line reader is a @c bool.
						@c false otherwise.
		 */
		bool HasBool() const;

		/**
		 Checks whether the next token of this line reader is a @c i8.

		 @return		@c true if the next token of this line reader is a @c i8.
						@c false otherwise.
		 */
		bool HasI8() const;

		/**
		 Checks whether the next token of this line reader is a @c u8.
 
		 @return		@c true if the next token of this line reader is a @c u8.
						@c false otherwise.
		 */
		bool HasU8() const;

		/**
		 Checks whether the next token of this line reader is a @c i16.

		 @return		@c true if the next token of this line reader is a @c i16.
						@c false otherwise.
		 */
		bool HasI16() const;

		/**
		 Checks whether the next token of this line reader is a @c u16.

		 @return		@c true if the next token of this line reader is a @c u16.
						@c false otherwise.
		 */
		bool HasU16() const;

		/**
		 Checks whether the next token of this line reader is a @c i32.

		 @return		@c true if the next token of this line reader is a @c i32.
						@c false otherwise.
		*/
		bool HasI32() const;

		/**
		 Checks whether the next token of this line reader is a @c u32.

		 @return		@c true if the next token of this line reader is a @c u32.
						@c false otherwise.
		 */
		bool HasU32() const;

		/**
		 Checks whether the next token of this line reader is a @c i64.

		 @return		@c true if the next token of this line reader is a @c i64.
						@c false otherwise.
		 */
		bool HasI64() const;

		/**
		 Checks whether the next token of this line reader is a @c u64.

		 @return		@c true if the next token of this line reader is a @c u64.
						@c false otherwise.
		 */
		bool HasU64() const;

		/**
		 Checks whether the next token of this line reader is a @c float.

		 @return		@c true if the next token of this line reader is a @c float.
						@c false otherwise.
		 */
		bool HasF32() const;

		/**
		 Checks whether the next token of this line reader is a @c f64.

		 @return		@c true if the next token of this line reader is a @c f64.
						@c false otherwise.
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
		u32 m_line_number;
	};
}