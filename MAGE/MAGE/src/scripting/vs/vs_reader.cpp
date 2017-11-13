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
		const char *token = 
			strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || MAGE_VS_TOKEN_COMMENT == token[0]) {
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
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	void VSReader::ReadVSBool() {
		const string name = ReadString();
		const bool value  = ReadBool();
		
		m_variable_buffer.emplace_back(VariableType::Bool, name, value);
	}

	void VSReader::ReadVSInt() {
		const string name = ReadString();
		const S32 value   = ReadS32();
		
		m_variable_buffer.emplace_back(VariableType::Int, name, value);
	}

	void VSReader::ReadVSInt2() {
		const string name = ReadString();
		const S32 x       = ReadS32();
		const S32 y       = ReadS32();
		const XMINT2 value(x, y);
		
		m_variable_buffer.emplace_back(VariableType::Int2, name, value);
	}

	void VSReader::ReadVSInt3() {
		const string name = ReadString();
		const S32 x       = ReadS32();
		const S32 y       = ReadS32();
		const S32 z  = ReadS32();
		const XMINT3 value(x, y, z);
		
		m_variable_buffer.emplace_back(VariableType::Int3, name, value);
	}

	void VSReader::ReadVSFloat() {
		const string name = ReadString();
		const F32 value = ReadF32();
	
		m_variable_buffer.emplace_back(VariableType::Float, name, value);
	}

	void VSReader::ReadVSFloat2() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const XMFLOAT2 value(x, y);
		
		m_variable_buffer.emplace_back(VariableType::Float2, name, value);
	}
	
	void VSReader::ReadVSFloat3() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const F32 z = ReadF32();
		const XMFLOAT3 value(x, y, z);
		
		m_variable_buffer.emplace_back(VariableType::Float3, name, value);
	}

	void VSReader::ReadVSFloat4() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const F32 z = ReadF32();
		const F32 w = ReadF32();
		const XMFLOAT4 value(x, y, z, w);
		
		m_variable_buffer.emplace_back(VariableType::Float4, name, value);
	}

	void VSReader::ReadVSColor() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const F32 z = ReadF32();
		const F32 w = ReadF32();
		const XMFLOAT4 value(x, y, z, w);
		
		m_variable_buffer.emplace_back(VariableType::Color, name, value);
	}

	void VSReader::ReadVSString() {
		const string name  = ReadString();
		const string value = ReadQuotedString();
		
		m_variable_buffer.emplace_back(VariableType::String, name, value);
	}
}