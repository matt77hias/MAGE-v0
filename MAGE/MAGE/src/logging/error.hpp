#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_ERROR_IGNORE 0
#define MAGE_ERROR_CONTINUE 1
#define MAGE_ERROR_ABORT 2

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Notifies an info message.
	 
	 @param[in]		format
					Pointer to the message format.	
	 */
	void Info(const char *format, ...);
	
	/**
	 Notifies a warning message.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Warning(const char *format, ...);
	
	/**
	 Notifies an error message.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Error(const char *format, ...);
	
	/**
	 Notifies a severe message.

	 @param[in]		format
					Pointer to the message format.
	 */
	void Severe(const char *format, ...);
}