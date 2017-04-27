//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	FormattedException::FormattedException()
		: exception(), m_text{} {}

	FormattedException::FormattedException(const char *format, ...)
		: FormattedException() {

		Assert(bytes);

		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		vsnprintf_s(m_text, _countof(m_text), _TRUNCATE, format, args);
		
		// End using variable argument list.
		va_end(args);
	}
}