#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

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

		LineReader() : m_context(nullptr) {}
		virtual ~LineReader() = default;

		HRESULT ReadFromFile(const wstring &fname, const string &delimiters = MAGE_DEFAULT_DELIMITERS);
		HRESULT ReadFromMemory(const char *input, const string &delimiters = MAGE_DEFAULT_DELIMITERS);

		const wstring &GetFilename() const {
			return m_fname;
		}
		const string &GetDelimiters() const {
			return m_delimiters;
		}

	protected:

		const uint32_t GetCurrentLineNumber() const {
			return m_line_number;
		}

		virtual HRESULT Preprocess();
		virtual HRESULT ReadLine(char *line) = 0;
		virtual HRESULT Postprocess();
		void ReadLineRemaining();

		char *ReadChars();
		string ReadString();
		string ReadQuotedString();
		bool ReadBool();
		int ReadInt();
		unsigned int ReadUnsignedInt();
		long ReadLong();
		unsigned long ReadUnsignedLong();
		long long ReadLongLong();
		unsigned long long ReadUnsignedLongLong();
		float ReadFloat();
		double ReadDouble();
		XMFLOAT2 ReadFloat2();
		XMFLOAT3 ReadFloat3();
		XMFLOAT4 ReadFloat4();

		bool HasChars() const;
		bool HasString() const;
		bool HasQuotedString() const;
		bool HasBool() const;
		bool HasInt() const;
		bool HasUnsignedInt() const;
		bool HasLong() const;
		bool HasUnsignedLong() const;
		bool HasLongLong() const;
		bool HasUnsignedLongLong() const;
		bool HasFloat() const;
		bool HasDouble() const;

		char *m_context;

	private:

		LineReader(const LineReader &parser) = delete;
		LineReader &operator=(const LineReader &parser) = delete;

		wstring m_fname;
		string m_delimiters;
		uint32_t m_line_number;
	};
}