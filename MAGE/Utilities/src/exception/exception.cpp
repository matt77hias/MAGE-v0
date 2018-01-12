//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

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
		: exception(), m_text{} {}

	Exception::Exception(const char *format, ...)
		: Exception() {

		Assert(format);

		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);

		vsnprintf_s(m_text, std::size(m_text), _TRUNCATE, format, args);
		
		// End using variable argument list.
		va_end(args);

		Error(m_text);
	}

	Exception::Exception(const char *format, va_list args) 
		: exception(), m_text{} {

		Assert(format);

		vsnprintf_s(m_text, std::size(m_text), _TRUNCATE, format, args);
		
		Error(m_text);
	}

	Exception::Exception(const Exception &exception) = default;

	Exception::Exception(Exception &&exception) = default;

	Exception::~Exception() = default;

	Exception &Exception::operator=(const Exception &exception) = default;

	Exception &Exception::operator=(Exception &&exception) = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Exception: Utilities
	//-------------------------------------------------------------------------
	#pragma region

	void ThrowIfFailed(bool result) {
		if (!result) {
			throw Exception();
		}
	}

	void ThrowIfFailed(bool result, const char *format, ...) {
		if (!result) {
			va_list args;

			// Retrieve the additional arguments after format.
			va_start(args, format);

			const Exception exception = Exception(format);

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

	void ThrowIfFailed(BOOL result, const char *format, ...) {
		if (FALSE == result) {
			va_list args;

			// Retrieve the additional arguments after format.
			va_start(args, format);

			const Exception exception = Exception(format);

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

	void ThrowIfFailed(HRESULT result, const char *format, ...) {
		if (FAILED(result)) {
			va_list args;

			// Retrieve the additional arguments after format.
			va_start(args, format);

			const Exception exception = Exception(format);

			// End using variable argument list.
			va_end(args);

			throw exception;
		}
	}

	#pragma endregion
}