#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
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
		virtual ~LineReader() = default;

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
		 */
		HRESULT ReadFromFile(const wstring &fname, const string &delimiters = mage_default_delimiters);
		
		/**
		 */
		HRESULT ReadFromMemory(const char *input, const string &delimiters = mage_default_delimiters);

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
			: m_context(nullptr), m_fname(), 
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
		
		void ReadLineRemaining();
		const char *ReadChars();
		const string ReadString();
		const string ReadQuotedString();
		bool ReadBool();
		int8_t ReadInt8();
		uint8_t ReadUInt8();
		int16_t ReadInt16();
		uint16_t ReadUInt16();
		int32_t ReadInt32();
		uint32_t ReadUInt32();
		int64_t ReadInt64();
		uint64_t ReadUInt64();
		float ReadFloat();
		double ReadDouble();
		const XMFLOAT2 ReadFloat2();
		const XMFLOAT3 ReadFloat3();
		const XMFLOAT4 ReadFloat4();

		bool HasChars() const;
		bool HasString() const;
		bool HasQuotedString() const;
		bool HasBool() const;
		bool HasInt8() const;
		bool HasUInt8() const;
		bool HasInt16() const;
		bool HasUInt16() const;
		bool HasInt32() const;
		bool HasUInt32() const;
		bool HasInt64() const;
		bool HasUInt64() const;
		bool HasFloat() const;
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

		 @return		A success/error value.
		 */
		virtual HRESULT Preprocess();

		/**
		 Reads the given line.

		 @parm[in,out]	line
						A pointer to the null-terminated byte string to read.
		 @return		A success/error value.
		 */
		virtual HRESULT ReadLine(char *line) = 0;

		/**
		 Post-process after reading the current file of this line reader. 

		 @return		A success/error value.
		 */
		virtual HRESULT Postprocess();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

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