#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the fixed terminal width.

	 @return		The fixed terminal width.
	 */
	inline int TerminalWidth() {
		// Retrieve a handle to the standard output device.
		const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE || h == NULL) {
			// Print error message if the handle is invalid.
			fprintf(stderr, "GetStdHandle() call failed");
			return 80;
		}
		// Structure containing information about a console screen buffer.
		CONSOLE_SCREEN_BUFFER_INFO buffer_info = { 0 };
		GetConsoleScreenBufferInfo(h, &buffer_info);
		// dwSize:	a COORD structure that contains the size of the console
		//			screen buffer in character columns and rows.
		return buffer_info.dwSize.X;
	}
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\timer.hpp"
#include "logging\progressreporter.hpp"
#include "logging\error.hpp"
#include "logging\debug.hpp"

#pragma endregion