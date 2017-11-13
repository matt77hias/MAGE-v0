#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <assert.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Error Logging (+ Aborting)
	//-------------------------------------------------------------------------

	/**
	 Notifies a debug message.

	 A debug message is associated with generally useful information to log 
	 only in debug builds.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		format
					Pointer to the message format.
	 */
	void Debug([[maybe_unused]] const char *format, ...);

	/**
	 Notifies an info message.

	 An info message is associated with generally useful information to log.
	 
	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		format
					Pointer to the message format.	
	 */
	void Info(const char *format, ...);
	
	/**
	 Notifies a warning message.

	 A warning message is associated with anything that can potentially cause 
	 application oddities.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		format
					Pointer to the message format.
	 */
	void Warning(const char *format, ...);
	
	/**
	 Notifies an error message.

	 An error message is associated with any error which is fatal to the 
	 operation, but not the service or application.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		format
					Pointer to the message format.
	 */
	void Error(const char *format, ...);
	
	/**
	 Notifies a fatal message.

	 A fatal message is associated with any error that is forcing a shutdown of 
	 the service or application to prevent data loss (or further data loss).

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		format
					Pointer to the message format.
	 */
	void Fatal(const char *format, ...);
}

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

// Assert definition
// The macro NDEBUG controls whether assert statements are active or not.
#ifdef NDEBUG
#define Assert(expr) (__noop)
#else
#define Assert(expr) ((expr) ? __noop : Fatal("Assertion \"%s\" failed in %s, line %d", \
												#expr, __FILE__, __LINE__))
#endif

#pragma endregion