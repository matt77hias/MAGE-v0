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
	// Exceptions
	//-------------------------------------------------------------------------

	using std::exception;
	using std::bad_alloc;

	//-------------------------------------------------------------------------
	// Error Logging (+ Aborting)
	//-------------------------------------------------------------------------

	/**
	 Notifies a debug message.

	 A debug message is associated with generally useful information to log 
	 only in debug builds.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Debug(const char *format, ...);

	/**
	 Notifies an info message.

	 An info message is associated with generally useful information to log.
	 
	 @param[in]		format
					Pointer to the message format.	
	 */
	void Info(const char *format, ...);
	
	/**
	 Notifies a warning message.

	 A warning message is associated with anything that can potentially cause application oddities.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Warning(const char *format, ...);
	
	/**
	 Notifies an error message.

	 An error message is associated with any error which is fatal to the operation,
	 but not the service or application.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Error(const char *format, ...);
	
	/**
	 Notifies a fatal message.

	 A fatal message is associated with any error that is forcing a shutdown 
	 of the service or application to prevent data loss (or further data loss).

	 @param[in]		format
					Pointer to the message format.
	 */
	void Fatal(const char *format, ...);
}

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#ifdef NDEBUG
#define Assert(expr) (__noop)
#else
#define Assert(expr) ((expr) ? __noop : Fatal("Assertion \"%s\" failed in %s, line %d", \
												#expr, __FILE__, __LINE__))
#endif

#pragma endregion