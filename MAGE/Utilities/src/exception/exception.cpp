//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Exception
	//-------------------------------------------------------------------------
	#pragma region

	Exception::Exception()
		: std::exception(), 
		m_text{} {}

	Exception::Exception(NotNull< const_zstring > format, ...)
		: std::exception(),
		m_text{} {

		va_list args;
		
		// Retrieve the additional arguments after format.
		const char* const c_str = format;
		va_start(args, c_str);

		vsnprintf_s(m_text, std::size(m_text), _TRUNCATE, format, args);
		
		// End using variable argument list.
		va_end(args);

		Error(m_text);
	}

	Exception::Exception(NotNull< const_zstring > format, va_list args)
		: std::exception(), 
		m_text{} {

		vsnprintf_s(m_text, std::size(m_text), _TRUNCATE, format, args);
		
		Error(m_text);
	}

	Exception::Exception(const Exception& exception) = default;

	Exception::Exception(Exception&& exception) = default;

	Exception::~Exception() = default;

	Exception& Exception::operator=(const Exception& exception) = default;

	Exception& Exception::operator=(Exception&& exception) = default;

	const char* Exception::what() const noexcept {
		return m_text;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Exception: Utilities
	//-------------------------------------------------------------------------
	#pragma region

	void ThrowIfFailed(bool result) {
		if (false == result) {
			throw Exception();
		}
	}

	void ThrowIfFailed(bool result, NotNull< const_zstring > format, ...) {
		if (false == result) {
			va_list args;

			// Retrieve the additional arguments after format.
			const char* const c_str = format;
			va_start(args, c_str);

			const Exception exception(format, args);

			// End using variable argument list.
			va_end(args);

			throw exception;
		}
	}

	void ThrowIfFailed(BOOL result) {
		if (FALSE == result) {
			throw Exception();
		}
	}

	void ThrowIfFailed(BOOL result, NotNull< const_zstring > format, ...) {
		if (FALSE == result) {
			va_list args;

			// Retrieve the additional arguments after format.
			const char* const c_str = format;
			va_start(args, c_str);

			const Exception exception(format, args);

			// End using variable argument list.
			va_end(args);

			throw exception;
		}
	}

	void ThrowIfFailed(HRESULT result) {
		if (FAILED(result)) {
			throw Exception();
		}
	}

	void ThrowIfFailed(HRESULT result, NotNull< const_zstring > format, ...) {
		if (FAILED(result)) {
			va_list args;

			// Retrieve the additional arguments after format.
			const char* const c_str = format;
			va_start(args, c_str);

			const Exception exception(format, args);

			// End using variable argument list.
			va_end(args);

			throw exception;
		}
	}

	#pragma endregion
}