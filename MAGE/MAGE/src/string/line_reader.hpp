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

	class LineReader {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		virtual ~LineReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		LineReader &operator=(const LineReader &reader) = delete;
		LineReader &operator=(LineReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT ReadFromFile(const wstring &fname, const string &delimiters = mage_default_delimiters);
		HRESULT ReadFromMemory(const char *input, const string &delimiters = mage_default_delimiters);

		const wstring &GetFilename() const {
			return m_fname;
		}
		const string &GetDelimiters() const {
			return m_delimiters;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		LineReader()
			: m_context(nullptr), m_fname(), 
			m_delimiters(mage_default_delimiters), m_line_number(0) {}
		LineReader(const LineReader &reader) = delete;
		LineReader(LineReader &&reader) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const uint32_t GetCurrentLineNumber() const {
			return m_line_number;
		}

		virtual HRESULT Preprocess();
		virtual HRESULT ReadLine(char *line) = 0;
		virtual HRESULT Postprocess();
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

		char *m_context;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		wstring m_fname;
		string m_delimiters;
		uint32_t m_line_number;
	};
}