//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_reader.hpp"
#include "loaders\var\var_tokens.hpp"
#include "utils\string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VARReader::VARReader(map< string, Value > &variable_buffer)
		: LineReader(), 
		m_variable_buffer(variable_buffer) {}

	VARReader::VARReader(VARReader &&reader) = default;

	VARReader::~VARReader() = default;

	void VARReader::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = 
			strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || MAGE_VAR_TOKEN_COMMENT == token[0]) {
			return;
		}

		if (str_equals(token, MAGE_VAR_TOKEN_BOOL)) {
			ReadVARBool();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_INT)) {
			ReadVARInt();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_INT2)) {
			ReadVARInt2();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_INT3)) {
			ReadVARInt3();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_FLOAT)) {
			ReadVARFloat();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_FLOAT2)) {
			ReadVARFloat2();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_FLOAT3)) {
			ReadVARFloat3();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_FLOAT4)) {
			ReadVARFloat4();
		}
		else if (str_equals(token, MAGE_VAR_TOKEN_STRING)) {
			ReadVARString();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	void VARReader::ReadVARBool() {
		const string name = ReadString();
		const bool value  = ReadBool();
		
		m_variable_buffer.insert_or_assign(std::move(name), 
			                               Value(value));
	}

	void VARReader::ReadVARInt() {
		const string name = ReadString();
		const S32 value   = ReadS32();
		
		m_variable_buffer.insert_or_assign(std::move(name), 
			                               Value(value));
	}

	void VARReader::ReadVARInt2() {
		const string name = ReadString();
		const S32 x       = ReadS32();
		const S32 y       = ReadS32();
		const S32x2 value(x, y);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARInt3() {
		const string name = ReadString();
		const S32 x       = ReadS32();
		const S32 y       = ReadS32();
		const S32 z  = ReadS32();
		const S32x3 value(x, y, z);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARFloat() {
		const string name = ReadString();
		const F32 value = ReadF32();
	
		m_variable_buffer.insert_or_assign(std::move(name), 
			                               Value(value));
	}

	void VARReader::ReadVARFloat2() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const F32x2 value(x, y);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}
	
	void VARReader::ReadVARFloat3() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const F32 z = ReadF32();
		const F32x3 value(x, y, z);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARFloat4() {
		const string name = ReadString();
		const F32 x = ReadF32();
		const F32 y = ReadF32();
		const F32 z = ReadF32();
		const F32 w = ReadF32();
		const F32x4 value(x, y, z, w);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARString() {
		const string name  = ReadString();
		const string value = ReadQuotedString();
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}
}