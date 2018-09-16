//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"
#include "logging\logging.hpp"

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

	Exception::Exception(const_zstring format, ...)
		: Exception() {

		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);

		vsnprintf_s(m_text, std::size(m_text), _TRUNCATE, format, args);
		
		// End using variable argument list.
		va_end(args);

		Error(m_text);
	}

	Exception::Exception(const_zstring format, va_list args)
		: Exception() {

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

	void ThrowIfFailed(bool result, const_zstring format, ...) {
		if (false == result) {
			va_list args;

			// Retrieve the additional arguments after format.
			va_start(args, format);

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

	void ThrowIfFailed(BOOL result, const_zstring format, ...) {
		if (FALSE == result) {
			va_list args;

			// Retrieve the additional arguments after format.
			va_start(args, format);

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

	void ThrowIfFailed(HRESULT result, const_zstring format, ...) {
		if (FAILED(result)) {
			va_list args;

			// Retrieve the additional arguments after format.
			va_start(args, format);

			const Exception exception(format, args);

			// End using variable argument list.
			va_end(args);

			throw exception;
		}
	}

	#pragma endregion
}