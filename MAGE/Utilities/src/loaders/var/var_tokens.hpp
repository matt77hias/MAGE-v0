#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	constexpr const char g_var_token_comment = '#';

	template< typename T >
	const_zstring g_var_token;

	template<>
	constexpr const_zstring g_var_token< bool > = "bool";

	template<>
	constexpr const_zstring g_var_token< F32 > = "F32";

	template<>
	constexpr const_zstring g_var_token< F32x2 > = "F32x2";

	template<>
	constexpr const_zstring g_var_token< F32x3 > = "F32x3";

	template<>
	constexpr const_zstring g_var_token< F32x4 > = "F32x4";

	template<>
	constexpr const_zstring g_var_token< S32 > = "S32";

	template<>
	constexpr const_zstring g_var_token< S32x2 > = "S32x2";

	template<>
	constexpr const_zstring g_var_token< S32x3 > = "S32x3";

	template<>
	constexpr const_zstring g_var_token< S32x4 > = "S32x4";

	template<>
	constexpr const_zstring g_var_token< U32 > = "U32";

	template<>
	constexpr const_zstring g_var_token< U32x2 > = "U32x2";

	template<>
	constexpr const_zstring g_var_token< U32x3 > = "U32x3";

	template<>
	constexpr const_zstring g_var_token< U32x4 > = "U32x4";

	template<>
	constexpr const_zstring g_var_token< std::string > = "string";
}