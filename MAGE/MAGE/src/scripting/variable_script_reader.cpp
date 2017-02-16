//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script_reader.hpp"
#include "scripting\variable_script_tokens.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT VSReader::ParseLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_VS_TOKEN_COMMENT) {
			return S_OK;
		}

		if (str_equals(token, MAGE_VS_TOKEN_BOOL)) {
			ParseVSBool();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_INT)) {
			ParseVSInt();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_INT2)) {
			ParseVSInt2();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_INT3)) {
			ParseVSInt3();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT)) {
			ParseVSFloat();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT2)) {
			ParseVSFloat2();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT3)) {
			ParseVSFloat3();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT4)) {
			ParseVSFloat4();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_COLOR)) {
			ParseVSColor();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_STRING)) {
			ParseVSString();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_UNKNOWN)) {
			ParseVSUnknown();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		ParseLineRemaining();

		return S_OK;
	}

	void VSReader::ParseVSBool() {
		const string name = ParseString();
		const bool x = ParseBool();
		const bool *value = new bool(x);
		m_variable_buffer.push_back(new Variable(BoolType, name, value));
	}

	void VSReader::ParseVSInt() {
		const string name = ParseString();
		const int x = ParseInt();
		const int *value = new int(x);
		m_variable_buffer.push_back(new Variable(IntType, name, value));
	}

	void VSReader::ParseVSInt2() {
		const string name = ParseString();
		const int x = ParseInt();
		const int y = ParseInt();
		const int2 *value = new int2(x, y);
		m_variable_buffer.push_back(new Variable(Int2Type, name, value));
	}

	void VSReader::ParseVSInt3() {
		const string name = ParseString();
		const int x = ParseInt();
		const int y = ParseInt();
		const int z = ParseInt();
		const int3 *value = new int3(x, y, z);
		m_variable_buffer.push_back(new Variable(Int3Type, name, value));
	}

	void VSReader::ParseVSFloat() {
		const string name = ParseString();
		const float x = ParseFloat();
		const float *value = new float(x);
		m_variable_buffer.push_back(new Variable(FloatType, name, value));
	}

	void VSReader::ParseVSFloat2() {
		const string name = ParseString();
		const float x = ParseFloat();
		const float y = ParseFloat();
		const float2 *value = new float2(x, y);
		m_variable_buffer.push_back(new Variable(Float2Type, name, value));
	}
	
	void VSReader::ParseVSFloat3() {
		const string name = ParseString();
		const float x = ParseFloat();
		const float y = ParseFloat();
		const float z = ParseFloat();
		const float3 *value = new float3(x, y, z);
		m_variable_buffer.push_back(new Variable(Float3Type, name, value));
	}

	void VSReader::ParseVSFloat4() {
		const string name = ParseString();
		const float x = ParseFloat();
		const float y = ParseFloat();
		const float z = ParseFloat();
		const float w = ParseFloat();
		const float4 *value = new float4(x, y, z, w);
		m_variable_buffer.push_back(new Variable(Float4Type, name, value));
	}

	void VSReader::ParseVSColor() {
		const string name = ParseString();
		const float x = ParseFloat();
		const float y = ParseFloat();
		const float z = ParseFloat();
		const float w = ParseFloat();
		const color *value = new color(x, y, z, w);
		m_variable_buffer.push_back(new Variable(ColorType, name, value));
	}

	void VSReader::ParseVSString() {
		const string name = ParseString();
		const string str = ParseQuotedString();
		const string *value = new string(str);
		m_variable_buffer.push_back(new Variable(StringType, name, value));
	}

	void VSReader::ParseVSUnknown() {
		const string name = ParseString();
		const char *str = ParseChars();
		char *value = new char[MAX_PATH + 1];
		strcpy_s(value, MAX_PATH + 1, str);
		m_variable_buffer.push_back(new Variable(UnknownType, name, (void *)value));
	}
}