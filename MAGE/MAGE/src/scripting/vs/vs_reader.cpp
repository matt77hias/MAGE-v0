//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\vs\vs_reader.hpp"
#include "scripting\vs\vs_tokens.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT VSReader::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_VS_TOKEN_COMMENT) {
			return S_OK;
		}

		if (str_equals(token, MAGE_VS_TOKEN_BOOL)) {
			ReadVSBool();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_INT)) {
			ReadVSInt();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_INT2)) {
			ReadVSInt2();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_INT3)) {
			ReadVSInt3();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT)) {
			ReadVSFloat();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT2)) {
			ReadVSFloat2();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT3)) {
			ReadVSFloat3();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_FLOAT4)) {
			ReadVSFloat4();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_COLOR)) {
			ReadVSColor();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_STRING)) {
			ReadVSString();
		}
		else if (str_equals(token, MAGE_VS_TOKEN_UNKNOWN)) {
			ReadVSUnknown();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		ReadLineRemaining();

		return S_OK;
	}

	void VSReader::ReadVSBool() {
		const string name = ReadString();
		const bool x = ReadBool();
		const bool *value = new bool(x);
		m_variable_buffer.push_back(new Variable(BoolType, name, value));
	}

	void VSReader::ReadVSInt() {
		const string name = ReadString();
		const int x = ReadInt32();
		const int *value = new int(x);
		m_variable_buffer.push_back(new Variable(IntType, name, value));
	}

	void VSReader::ReadVSInt2() {
		const string name = ReadString();
		const int x = ReadInt32();
		const int y = ReadInt32();
		const int2 *value = new int2(x, y);
		m_variable_buffer.push_back(new Variable(Int2Type, name, value));
	}

	void VSReader::ReadVSInt3() {
		const string name = ReadString();
		const int x = ReadInt32();
		const int y = ReadInt32();
		const int z = ReadInt32();
		const int3 *value = new int3(x, y, z);
		m_variable_buffer.push_back(new Variable(Int3Type, name, value));
	}

	void VSReader::ReadVSFloat() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float *value = new float(x);
		m_variable_buffer.push_back(new Variable(FloatType, name, value));
	}

	void VSReader::ReadVSFloat2() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float2 *value = new float2(x, y);
		m_variable_buffer.push_back(new Variable(Float2Type, name, value));
	}
	
	void VSReader::ReadVSFloat3() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float z = ReadFloat();
		const float3 *value = new float3(x, y, z);
		m_variable_buffer.push_back(new Variable(Float3Type, name, value));
	}

	void VSReader::ReadVSFloat4() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float z = ReadFloat();
		const float w = ReadFloat();
		const float4 *value = new float4(x, y, z, w);
		m_variable_buffer.push_back(new Variable(Float4Type, name, value));
	}

	void VSReader::ReadVSColor() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float z = ReadFloat();
		const float w = ReadFloat();
		const color *value = new color(x, y, z, w);
		m_variable_buffer.push_back(new Variable(ColorType, name, value));
	}

	void VSReader::ReadVSString() {
		const string name = ReadString();
		const string str = ReadQuotedString();
		const string *value = new string(str);
		m_variable_buffer.push_back(new Variable(StringType, name, value));
	}

	void VSReader::ReadVSUnknown() {
		const string name = ReadString();
		const char *str = ReadChars();
		char *value = new char[MAX_PATH + 1];
		strcpy_s(value, MAX_PATH + 1, str);
		m_variable_buffer.push_back(new Variable(UnknownType, name, (void *)value));
	}
}