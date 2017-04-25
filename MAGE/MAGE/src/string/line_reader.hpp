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
						A reference to a line reader to copy from.
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
		 Reads the given file.

		 @param[in]		fname
						A reference to the file name.
		 @param[in]		delimiters
						A reference to a string containing the token delimiters
						(single characters).
		 @throws		FormattedException
						The file reading failed.
		 */
		void ReadFromFile(const wstring &fname, const string &delimiters = mage_default_delimiters);
		
		/**
		 Reads the input string.

		 @param[in]		input
						A pointer to the input null-terminated byte string.
		 @param[in]		delimiters
						A reference to a string containing the token delimiters
						(single characters).
		 @throws		FormattedException
						The string reading failed.
		 */
		void ReadFromMemory(const char *input, const string &delimiters = mage_default_delimiters);

		/**
		 Returns the current filename of this line reader.

		 @return		A reference to the current filename of this line reader.
		 */
		const wstring &GetFilename() const {
			return m_fname;
		}

		/**
		 Returns the current delimiters of this line reader.

		 @return		A reference to the current delimiters of this line reader.
		 */
		const string &GetDelimiters() const {
			return m_delimiters;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a line reader.
		 */
		LineReader()
			: m_context(nullptr), m_file(nullptr), m_fname(), 
			m_delimiters(mage_default_delimiters), m_line_number(0) {}

		/**
		 Constructs a line reader from the given line reader.

		 @param[in]		reader
						A reference to the line reader to copy from.
		 */
		LineReader(const LineReader &reader) = delete;

		/**
		 Constructs a line reader by moving the given line reader.

		 @param[in]		reader
						A reference to the line reader to move.
		 */
		LineReader(LineReader &&reader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the current line number of this line reader.

		 @return		The current line number of this line reader.
		 */
		uint32_t GetCurrentLineNumber() const {
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
						If there is no next token.
		 */
		const char *ReadChars();

		/**
		 Reads and converts the next token of this line reader to a string.

		 @return		The string represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token.
		 */
		const string ReadString();

		/**
		 Reads and converts the next token of this line reader to a quoted string.

		 @return		The quoted string represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a quoted string.
		 */
		const string ReadQuotedString();

		/**
		 Reads and converts the next token of this line reader to a @c bool.

		 @return		The @c bool represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c bool.
		 */
		bool ReadBool();

		/**
		 Reads and converts the next token of this line reader to a @c int8_t.

		 @return		The @c int8_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c int8_t.
		 */
		int8_t ReadInt8();

		/**
		 Reads and converts the next token of this line reader to a @c uint8_t.

		 @return		The @c uint8_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c uint8_t.
		 */
		uint8_t ReadUInt8();

		/**
		 Reads and converts the next token of this line reader to a @c int16_t.

		 @return		The @c int16_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c int16_t.
		 */
		int16_t ReadInt16();

		/**
		 Reads and converts the next token of this line reader to a @c uint16_t.

		 @return		The @c uint16_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c uint16_t.
		 */
		uint16_t ReadUInt16();

		/**
		 Reads and converts the next token of this line reader to a @c int32_t.

		 @return		The @c int32_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c int32_t.
		 */
		int32_t ReadInt32();

		/**
		 Reads and converts the next token of this line reader to a @c uint32_t.

		 @return		The @c uint32_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c uint32_t.
		 */
		uint32_t ReadUInt32();

		/**
		 Reads and converts the next token of this line reader to a @c int64_t.

		 @return		The @c int64_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c int64_t.
		 */
		int64_t ReadInt64();

		/**
		 Reads and converts the next token of this line reader to a @c uint64_t.

		 @return		The @c uint64_t represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c uint64_t.
		 */
		uint64_t ReadUInt64();

		/**
		 Reads and converts the next token of this line reader to a @c float.

		 @return		The @c float represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c float.
		 */
		float ReadFloat();

		/**
		 Reads and converts the next token of this line reader to a @c double.

		 @return		The @c double represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c double.
		 */
		double ReadDouble();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT2.

		 @return		The @c XMFLOAT2 represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c XMFLOAT2.
		 */
		const XMFLOAT2 ReadFloat2();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT3.

		 @return		The @c XMFLOAT3 represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
						a @c XMFLOAT3.
		 */
		const XMFLOAT3 ReadFloat3();

		/**
		 Reads and converts the next token of this line reader to a @c XMFLOAT4.

		 @return		The @c XMFLOAT4 represented by the next token of this line reader.
		 @throws		FormattedException
						If there is no next token or the next token does not represent
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
		 Checks whether the next token of this line reader is a @c int8_t.

		 @return		@c true if the next token of this line reader is a @c int8_t.
						@c false otherwise.
		 */
		bool HasInt8() const;

		/**
		 Checks whether the next token of this line reader is a @c uint8_t.
 
		 @return		@c true if the next token of this line reader is a @c uint8_t.
						@c false otherwise.
		 */
		bool HasUInt8() const;

		/**
		 Checks whether the next token of this line reader is a @c int16_t.

		 @return		@c true if the next token of this line reader is a @c int16_t.
						@c false otherwise.
		 */
		bool HasInt16() const;

		/**
		 Checks whether the next token of this line reader is a @c uint16_t.

		 @return		@c true if the next token of this line reader is a @c uint16_t.
						@c false otherwise.
		 */
		bool HasUInt16() const;

		/**
		 Checks whether the next token of this line reader is a @c int32_t.

		 @return		@c true if the next token of this line reader is a @c int32_t.
						@c false otherwise.
		*/
		bool HasInt32() const;

		/**
		 Checks whether the next token of this line reader is a @c uint32_t.

		 @return		@c true if the next token of this line reader is a @c uint32_t.
						@c false otherwise.
		 */
		bool HasUInt32() const;

		/**
		 Checks whether the next token of this line reader is a @c int64_t.

		 @return		@c true if the next token of this line reader is a @c int64_t.
						@c false otherwise.
		 */
		bool HasInt64() const;

		/**
		 Checks whether the next token of this line reader is a @c uint64_t.

		 @return		@c true if the next token of this line reader is a @c uint64_t.
						@c false otherwise.
		 */
		bool HasUInt64() const;

		/**
		 Checks whether the next token of this line reader is a @c float.

		 @return		@c true if the next token of this line reader is a @c float.
						@c false otherwise.
		 */
		bool HasFloat() const;

		/**
		 Checks whether the next token of this line reader is a @c double.

		 @return		@c true if the next token of this line reader is a @c double.
						@c false otherwise.
		 */
		bool HasDouble() const;

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
		 Pre-process before reading the current file of this line reader.

		 @throws		FormattedException
						The pre-processing failed.
		 */
		virtual void Preprocess() {}

		/**
		 Reads the given line.

		 @param[in, out]line
						A pointer to the null-terminated byte string to read.
		 @throws		FormattedException
						The reading of the line failed.
		 */
		virtual void ReadLine(char *line) = 0;

		/**
		 Post-process after reading the current file of this line reader.

		 @throws		FormattedException
						The post-processing failed.
		 */
		virtual void Postprocess() {}

		/**
		 Closes the current file of this line reader.
		 */
		void CloseFile();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		The file of this line reader.
		*/
		FILE *m_file;

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
		uint32_t m_line_number;
	};
}