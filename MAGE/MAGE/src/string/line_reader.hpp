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

		char *ReadOptionalChars(TokenResult *pr = nullptr);
		string ReadOptionalString(const string &default_value = "", TokenResult *pr = nullptr);
		string ReadOptionalQuotedString(const string &default_value = "", TokenResult *pr = nullptr);
		bool ReadOptionalBool(bool default_value = false, TokenResult *pr = nullptr);
		int ReadOptionalInt(int default_value = 0, TokenResult *pr = nullptr);
		unsigned int ReadOptionalUnsignedInt(unsigned int default_value = 0, TokenResult *pr = nullptr);
		long ReadOptionalLong(long default_value = 0, TokenResult *pr = nullptr);
		unsigned long ReadOptionalUnsignedLong(unsigned long default_value = 0, TokenResult *pr = nullptr);
		long long ReadOptionalLongLong(long long default_value = 0, TokenResult *pr = nullptr);
		unsigned long long ReadOptionalUnsignedLongLong(unsigned long long default_value = 0, TokenResult *pr = nullptr);
		float ReadOptionalFloat(float default_value = 0.0f, TokenResult *pr = nullptr);
		double ReadOptionalDouble(double default_value = 0.0, TokenResult *pr = nullptr);
		XMFLOAT2 ReadOptionalFloat2(XMFLOAT2 default_value = XMFLOAT2(), TokenResult *pr = nullptr);
		XMFLOAT3 ReadOptionalFloat3(XMFLOAT3 default_value = XMFLOAT3(), TokenResult *pr = nullptr);
		XMFLOAT4 ReadOptionalFloat4(XMFLOAT4 default_value = XMFLOAT4(), TokenResult *pr = nullptr);

		char *m_context;

	private:

		LineReader(const LineReader &parser) = delete;
		LineReader &operator=(const LineReader &parser) = delete;

		wstring m_fname;
		string m_delimiters;
		uint32_t m_line_number;
	};
}