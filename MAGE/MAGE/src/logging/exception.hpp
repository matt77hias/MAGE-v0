#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <new>
namespace mage {
	using std::exception;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of formatted exceptions.
	 */
	class FormattedException : exception {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

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
		 Constructs a formatted exception.

		 @pre			@a format is not equal to @c nullptr.
		 @param[in]		format
						Pointer to the message format.
		 @param[in]		args
						The variable argument list.
		 */
		explicit FormattedException(const char * format, va_list args);

		/**
		 Constructs a formatted exception from the given formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to copy.
		 */
		FormattedException(const FormattedException &formatted_exception);

		/**
		 Constructs a formatted exception by moving the given formatted 
		 exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to move.
		 */
		FormattedException(FormattedException &&formatted_exception);
		
		/**
		 Destructs this formatted exception.
		 */
		virtual ~FormattedException();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given formatted exception to this formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to copy.
		 @return		A reference to the copy of the given formatted 
						exception (i.e. this formatted exception).
		 */
		FormattedException &operator=(
			const FormattedException &formatted_exception);
		
		/**
		 Moves the given formatted exception to this formatted exception.

		 @param[in]		formatted_exception
						A reference to a formatted exception to move.
		 @return		A reference to the moved formatted exception (i.e. 
						this formatted exception).
		 */
		FormattedException &operator=(
			FormattedException &&formatted_exception);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns a null-terminated byte string that may be used to identify the 
		 exception.

		 @return		A null-terminated byte string that may be used to 
						identify the exception.
		 */
		virtual const char *what() const noexcept override {
			return m_text;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The text buffer of this formatted exception.
		 */
		char m_text[2048];
	};

	static_assert(!std::is_same< bool, BOOL >::value,
		"MAGE/Windows primitive type mismatch");
	static_assert(!std::is_same< BOOL, HRESULT >::value,
		"MAGE/Windows primitive type mismatch");

	/**
	 Throws if the given results corresponds to a failure.

	 @param[in]		result
					The result value.
	 */
	void ThrowIfFailed(bool result);

	/**
	 Throws if the given results corresponds to a failure.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		result
					The result value.
	 @param[in]		format
					Pointer to the message format.
	 */
	void ThrowIfFailed(bool result, const char *format, ...);

	/**
	 Throws if the given results corresponds to a failure.

	 @param[in]		result
					The result value.
	 */
	void ThrowIfFailed(BOOL result);

	/**
	 Throws if the given results corresponds to a failure.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		result
					The result value.
	 @param[in]		format
					Pointer to the message format.
	 */
	void ThrowIfFailed(BOOL result, const char *format, ...);

	/**
	 Throws if the given results corresponds to a failure.

	 @param[in]		result
					The result value.
	 */
	void ThrowIfFailed(HRESULT result);

	/**
	 Throws if the given results corresponds to a failure.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		result
					The result value.
	 @param[in]		format
					Pointer to the message format.
	 */
	void ThrowIfFailed(HRESULT result, const char *format, ...);
}