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
namespace mage::loader {

	VARReader::VARReader(std::map< string, Value > &variable_buffer)
		: LineReader(), 
		m_variable_buffer(variable_buffer) {}

	VARReader::VARReader(VARReader &&reader) noexcept = default;

	VARReader::~VARReader() = default;

	void VARReader::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = 
			strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || g_var_token_comment == token[0]) {
			return;
		}

		if (str_equals(token, g_var_token_bool)) {
			ReadVARBool();
		}
		else if (str_equals(token, g_var_token_int)) {
			ReadVARInt();
		}
		else if (str_equals(token, g_var_token_int2)) {
			ReadVARInt2();
		}
		else if (str_equals(token, g_var_token_int3)) {
			ReadVARInt3();
		}
		else if (str_equals(token, g_var_token_float)) {
			ReadVARFloat();
		}
		else if (str_equals(token, g_var_token_float2)) {
			ReadVARFloat2();
		}
		else if (str_equals(token, g_var_token_float3)) {
			ReadVARFloat3();
		}
		else if (str_equals(token, g_var_token_float4)) {
			ReadVARFloat4();
		}
		else if (str_equals(token, g_var_token_string)) {
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
		const string name = Read< string >();
		const bool value  = Read< bool >();
		
		m_variable_buffer.insert_or_assign(std::move(name), 
			                               Value(value));
	}

	void VARReader::ReadVARInt() {
		const string name = Read< string >();
		const S32 value   = Read< S32 >();
		
		m_variable_buffer.insert_or_assign(std::move(name), 
			                               Value(value));
	}

	void VARReader::ReadVARInt2() {
		const string name = Read< string >();
		const S32 x       = Read< S32 >();
		const S32 y       = Read< S32 >();
		const S32x2 value(x, y);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARInt3() {
		const string name = Read< string >();
		const S32 x       = Read< S32 >();
		const S32 y       = Read< S32 >();
		const S32 z       = Read< S32 >();
		const S32x3 value(x, y, z);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARFloat() {
		const string name = Read< string >();
		const F32 value   = Read< F32 >();
	
		m_variable_buffer.insert_or_assign(std::move(name), 
			                               Value(value));
	}

	void VARReader::ReadVARFloat2() {
		const string name = Read< string >();
		const F32 x       = Read< F32 >();
		const F32 y       = Read< F32 >();
		const F32x2 value(x, y);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}
	
	void VARReader::ReadVARFloat3() {
		const string name = Read< string >();
		const F32 x       = Read< F32 >();
		const F32 y       = Read< F32 >();
		const F32 z       = Read< F32 >();
		const F32x3 value(x, y, z);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARFloat4() {
		const string name = Read< string >();
		const F32 x       = Read< F32 >();
		const F32 y       = Read< F32 >();
		const F32 z       = Read< F32 >();
		const F32 w       = Read< F32 >();
		const F32x4 value(x, y, z, w);
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}

	void VARReader::ReadVARString() {
		const string name  = Read< string >();
		const string value = ReadQuotedString();
		
		m_variable_buffer.insert_or_assign(std::move(name),
			                               Value(std::move(value)));
	}
}