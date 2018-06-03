//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_reader.hpp"
#include "loaders\var\var_tokens.hpp"
#include "logging\error.hpp"

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

	void VARReader::ReadLine() {
		const auto token = Read< string >();

		if (g_var_token_comment == token[0]) {
			return;
		} 
		else if (g_var_token_bool   == token) {
			ReadVARVariable< bool >();
		}
		else if (g_var_token_F32    == token) {
			ReadVARVariable< F32 >();
		}
		else if (g_var_token_F32x2  == token) {
			ReadVARVariable< F32, 2 >();
		}
		else if (g_var_token_F32x3  == token) {
			ReadVARVariable< F32, 3 >();
		}
		else if (g_var_token_F32x4  == token) {
			ReadVARVariable< F32, 4 >();
		}
		else if (g_var_token_S32    == token) {
			ReadVARVariable< S32 >();
		}
		else if (g_var_token_S32x2  == token) {
			ReadVARVariable< S32, 2 >();
		}
		else if (g_var_token_S32x3  == token) {
			ReadVARVariable< S32, 3 >();
		}
		else if (g_var_token_S32x4  == token) {
			ReadVARVariable< S32, 4 >();
		}
		else if (g_var_token_U32    == token) {
			ReadVARVariable< U32 >();
		}
		else if (g_var_token_U32x2  == token) {
			ReadVARVariable< U32, 2 >();
		}
		else if (g_var_token_U32x3  == token) {
			ReadVARVariable< U32, 3 >();
		}
		else if (g_var_token_U32x4  == token) {
			ReadVARVariable< U32, 4 >();
		}
		else if (g_var_token_string == token) {
			ReadVARVariable< string >();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				    GetPath().c_str(), GetCurrentLineNumber(), 
					token.c_str());
			return;
		}

		ReadRemainingTokens();
	}
}