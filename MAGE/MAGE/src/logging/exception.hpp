#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <new>
namespace mage {
	using std::exception;
	using std::bad_alloc;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	struct FormattedException : exception {

	public:

		FormattedException();
		explicit FormattedException(const char *format, ...);
		FormattedException(const FormattedException &formatted_exception) = default;
		FormattedException(FormattedException &&formatted_exception) = default;
		virtual ~FormattedException() = default;
		
		FormattedException &operator=(const FormattedException &formatted_exception) = default;
		FormattedException &operator=(FormattedException &&formatted_exception) = default;

		const char *what() const throw() {
			return m_text;
		}

	private:

		char m_text[2048];
	};
}