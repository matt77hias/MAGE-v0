//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_reader.hpp"
#include "loaders\var\var_tokens.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	VARReader::VARReader(std::map< string, Value >& variable_buffer)
		: LineReader(), 
		m_variable_buffer(variable_buffer) {}

	VARReader::VARReader(VARReader&& reader) noexcept = default;

	VARReader::~VARReader() = default;

	void VARReader::ReadLine(NotNull< zstring > line) {
		m_context = nullptr;
		const auto* const token = strtok_s(line, GetDelimiters().c_str(), 
										   &m_context);

		if (!token || g_var_token_comment == token[0]) {
			return;
		}

		const auto not_null_token = NotNull< const_zstring >(token);

		if (     str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_bool))) {
			
			ReadVARVariable< bool >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_F32))) {
			
			ReadVARVariable< F32 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_F32x2))) {
			
			ReadVARVariable< F32, 2 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_F32x3))) {
			
			ReadVARVariable< F32, 3 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_F32x4))) {
			
			ReadVARVariable< F32, 4 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_S32))) {
			
			ReadVARVariable< S32 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_S32x2))) {
			
			ReadVARVariable< S32, 2 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_S32x3))) {
			
			ReadVARVariable< S32, 3 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_S32x4))) {
			
			ReadVARVariable< S32, 4 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_U32))) {
			
			ReadVARVariable< U32 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_U32x2))) {
			
			ReadVARVariable< U32, 2 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_U32x3))) {
			
			ReadVARVariable< U32, 3 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_U32x4))) {
			
			ReadVARVariable< U32, 4 >();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_var_token_string))) {
			
			ReadVARVariable< string >();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				    GetPath().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}
}