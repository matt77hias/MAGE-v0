#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <cassert>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Notifies a debug message.

	 A debug message is associated with generally useful information to log 
	 only in debug builds.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Debug([[maybe_unused]] const_zstring format, ...);

	/**
	 Notifies an info message.

	 An info message is associated with generally useful information to log.
	 
	 @param[in]		format
					Pointer to the message format.	
	 */
	void Info(const_zstring format, ...);
	
	/**
	 Notifies a warning message.

	 A warning message is associated with anything that can potentially cause 
	 application oddities.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Warning(const_zstring format, ...);
	
	/**
	 Notifies an error message.

	 An error message is associated with any error which is fatal to the 
	 operation, but not the service or application.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Error(const_zstring format, ...);
	
	/**
	 Notifies a fatal message.

	 A fatal message is associated with any error that is forcing a shutdown of 
	 the service or application to prevent data loss (or further data loss).

	 @param[in]		format
					Pointer to the message format.
	 */
	void Fatal(const_zstring format, ...);
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
	#define Assert(expr) ((expr) ? (void)0 \
                                 : mage::Fatal("Assertion \"%s\" failed in %s, line %d", \
									           #expr, __FILE__, __LINE__))
#endif

#pragma endregion