#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	constexpr const char g_var_token_comment = '#';

	template< typename T >
	const_zstring GetVarToken() noexcept;

	template<>
	constexpr const_zstring GetVarToken< bool >() noexcept {
		return "bool";
	}

	template<>
	constexpr const_zstring GetVarToken< F32 >() noexcept {
		return "F32";
	}

	template<>
	constexpr const_zstring GetVarToken< F32x2 >() noexcept {
		return "F32x2";
	}

	template<>
	constexpr const_zstring GetVarToken< F32x3 >() noexcept {
		return "F32x3";
	}

	template<>
	constexpr const_zstring GetVarToken< F32x4 >() noexcept {
		return "F32x4";
	}

	template<>
	constexpr const_zstring GetVarToken< S32 >() noexcept {
		return "S32";
	}

	template<>
	constexpr const_zstring GetVarToken< S32x2 >() noexcept {
		return "S32x2";
	}

	template<>
	constexpr const_zstring GetVarToken< S32x3 >() noexcept {
		return "S32x3";
	}

	template<>
	constexpr const_zstring GetVarToken< S32x4 >() noexcept {
		return "S32x4";
	}

	template<>
	constexpr const_zstring GetVarToken< U32 >() noexcept {
		return "U32";
	}

	template<>
	constexpr const_zstring GetVarToken< U32x2 >() noexcept {
		return "U32x2";
	}

	template<>
	constexpr const_zstring GetVarToken< U32x3 >() noexcept {
		return "U32x3";
	}

	template<>
	constexpr const_zstring GetVarToken< U32x4 >() noexcept {
		return "U32x4";
	}

	template<>
	constexpr const_zstring GetVarToken< std::string >() noexcept {
		return "string";
	}
}