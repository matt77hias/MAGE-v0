//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\var\var_reader.hpp"
#include "loaders\var\var_tokens.hpp"
#include "logging\logging.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	VARReader::VARReader(std::map< std::string, Value >& variable_buffer)
		: LineReader(), 
		m_variable_buffer(variable_buffer) {}

	VARReader::VARReader(VARReader&& reader) noexcept = default;

	VARReader::~VARReader() = default;

	void VARReader::ReadLine() {
		const auto token = Read< std::string_view >();

		if (g_var_token_comment == token[0]) {
			return;
		} 
		else if (g_var_token< bool >  == token) {
			ReadVARVariable< bool >();
		}
		else if (g_var_token< F32 >   == token) {
			ReadVARVariable< F32 >();
		}
		else if (g_var_token< F32x2 > == token) {
			ReadVARVariable< F32, 2 >();
		}
		else if (g_var_token< F32x3 > == token) {
			ReadVARVariable< F32, 3 >();
		}
		else if (g_var_token< F32x4 > == token) {
			ReadVARVariable< F32, 4 >();
		}
		else if (g_var_token< S32 >   == token) {
			ReadVARVariable< S32 >();
		}
		else if (g_var_token< S32x2 > == token) {
			ReadVARVariable< S32, 2 >();
		}
		else if (g_var_token< S32x3 > == token) {
			ReadVARVariable< S32, 3 >();
		}
		else if (g_var_token< S32x4 > == token) {
			ReadVARVariable< S32, 4 >();
		}
		else if (g_var_token< U32 >   == token) {
			ReadVARVariable< U32 >();
		}
		else if (g_var_token< U32x2 > == token) {
			ReadVARVariable< U32, 2 >();
		}
		else if (g_var_token< U32x3 > == token) {
			ReadVARVariable< U32, 3 >();
		}
		else if (g_var_token< U32x4 > == token) {
			ReadVARVariable< U32, 4 >();
		}
		else if (g_var_token< std::string > == token) {
			ReadVARVariable< std::string >();
		}
		else {
			Warning("{}: line {}: unsupported keyword token: {}.",
					GetPath(), GetCurrentLineNumber(), token);
			return;
		}

		ReadRemainingTokens();
	}
}