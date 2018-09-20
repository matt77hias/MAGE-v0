#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Exception
	//-------------------------------------------------------------------------
	#pragma region

	template< typename... ArgsT >
	Exception::Exception(std::string_view format_str, const ArgsT&... args)
		: std::exception() {

		WriteTo(m_text, format_str, args...);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Exception: Utilities
	//-------------------------------------------------------------------------
	#pragma region

	inline void ThrowIfFailed(bool result) {
		if (false == result) {
			const Exception exception;
			Error(exception.what());
			throw exception;
		}
	}

	template< typename... ArgsT >
	inline void ThrowIfFailed(bool result,
							  std::string_view format_str,
							  const ArgsT&... args) {

		if (false == result) {
			const Exception exception(format_str, args...);
			Error(exception.what());
			throw exception;
		}
	}

	inline void ThrowIfFailed(BOOL result) {
		if (FALSE == result) {
			const Exception exception;
			Error(exception.what());
			throw exception;
		}
	}

	template< typename... ArgsT >
	inline void ThrowIfFailed(BOOL result,
							  std::string_view format_str,
							  const ArgsT&... args) {

		if (FALSE == result) {
			const Exception exception(format_str, args...);
			Error(exception.what());
			throw exception;
		}
	}

	inline void ThrowIfFailed(HRESULT result) {
		if (FAILED(result)) {
			const Exception exception;
			Error(exception.what());
			throw exception;
		}
	}

	template< typename... ArgsT >
	inline void ThrowIfFailed(HRESULT result,
							  std::string_view format_str,
							  const ArgsT&... args) {

		if (FAILED(result)) {
			const Exception exception(format_str, args...);
			Error(exception.what());
			throw exception;
		}
	}

	#pragma endregion
}