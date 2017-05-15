//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\vs\vs_reader.hpp"
#include "scripting\vs\vs_tokens.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VSReader::VSReader(vector< Variable > &variable_buffer)
		: LineReader(), m_variable_buffer(variable_buffer) {}

	VSReader::VSReader(VSReader &&reader) = default;

	VSReader::~VSReader() = default;

	void VSReader::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_VS_TOKEN_COMMENT) {
			return;
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
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	void VSReader::ReadVSBool() {
		const string name = ReadString();
		const bool value = ReadBool();
		m_variable_buffer.push_back(Variable(VariableType::Bool, name, value));
	}

	void VSReader::ReadVSInt() {
		const string name = ReadString();
		const int value = ReadInt32();
		m_variable_buffer.push_back(Variable(VariableType::Int, name, value));
	}

	void VSReader::ReadVSInt2() {
		const string name = ReadString();
		const int x = ReadInt32();
		const int y = ReadInt32();
		const int2 value(x, y);
		m_variable_buffer.push_back(Variable(VariableType::Int2, name, value));
	}

	void VSReader::ReadVSInt3() {
		const string name = ReadString();
		const int x = ReadInt32();
		const int y = ReadInt32();
		const int z = ReadInt32();
		const int3 value(x, y, z);
		m_variable_buffer.push_back(Variable(VariableType::Int3, name, value));
	}

	void VSReader::ReadVSFloat() {
		const string name = ReadString();
		const float value = ReadFloat();
		m_variable_buffer.push_back(Variable(VariableType::Float, name, value));
	}

	void VSReader::ReadVSFloat2() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float2 value(x, y);
		m_variable_buffer.push_back(Variable(VariableType::Float2, name, value));
	}
	
	void VSReader::ReadVSFloat3() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float z = ReadFloat();
		const float3 value(x, y, z);
		m_variable_buffer.push_back(Variable(VariableType::Float3, name, value));
	}

	void VSReader::ReadVSFloat4() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float z = ReadFloat();
		const float w = ReadFloat();
		const float4 value(x, y, z, w);
		m_variable_buffer.push_back(Variable(VariableType::Float4, name, value));
	}

	void VSReader::ReadVSColor() {
		const string name = ReadString();
		const float x = ReadFloat();
		const float y = ReadFloat();
		const float z = ReadFloat();
		const float w = ReadFloat();
		const color value(x, y, z, w);
		m_variable_buffer.push_back(Variable(VariableType::Color, name, value));
	}

	void VSReader::ReadVSString() {
		const string name = ReadString();
		const string value = ReadQuotedString();
		m_variable_buffer.push_back(Variable(VariableType::String, name, value));
	}
}