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

	/**
	 A class of formatted exceptions.
	 */
	struct FormattedException : exception {

	public:

		/**
		 Constructs a formatted exception.
		 */
		FormattedException();

		/**
		 Constructs a formatted exception.

		 @pre			@a format is not equal to @c nullptr.
		 @param[in]		format
						Pointer to the message format.
		 */
		explicit FormattedException(const char *format, ...);

		/**
		 Constructs a formatted exception from the given formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to copy.
		 */
		FormattedException(const FormattedException &formatted_exception);

		/**
		 Constructs a formatted exception by moving the given formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to move.
		 */
		FormattedException(FormattedException &&formatted_exception);
		
		/**
		 Destructs this formatted exception.
		 */
		virtual ~FormattedException();
		
		/**
		 Copies the given formatted exception to this formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to copy.
		 @return		A reference to the copy of the given formatted exception
						(i.e. this formatted exception).
		 */
		FormattedException &operator=(const FormattedException &formatted_exception);
		
		/**
		 Moves the given formatted exception to this formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to move.
		 @return		A reference to the moved formatted exception
						(i.e. this formatted exception).
		 */
		FormattedException &operator=(FormattedException &&formatted_exception);

		/**
		 Returns a null-terminated byte string that may be used to identify the exception.

		 @return		A null-terminated byte string that may be used to identify the exception.
		 */
		virtual const char *what() const override {
			return m_text;
		}

	private:

		/**
		 The text buffer of this formatted exception.
		 */
		char m_text[2048];
	};
}