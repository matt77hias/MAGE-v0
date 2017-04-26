//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "logging\logging.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	uint16_t ConsoleWidth() {
		// Retrieve a handle to the standard output device.
		const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (handle == INVALID_HANDLE_VALUE || handle == nullptr) {
			throw FormattedException("GetStdHandle() failed.");
		}
		// Structure containing information about a console screen buffer.
		CONSOLE_SCREEN_BUFFER_INFO buffer_info;
		ZeroMemory(&buffer_info, sizeof(buffer_info));
		GetConsoleScreenBufferInfo(handle, &buffer_info);
		// dwSize:	a COORD structure that contains the size of the console
		//			screen buffer in character columns and rows.
		return static_cast< uint16_t >(buffer_info.dwSize.X);
	}

	void InitializeConsole() {
		// Allocate a console for basic io
		if (!AllocConsole()) {
			throw FormattedException("Console allocation failed.");
		}

		FILE *stream_in, *stream_out, *stream_err;
		// Redirect stdin, stdout and stderr to the allocated console
		// Reuse stdin to open the file "CONIN$"
		const errno_t result_in = freopen_s(&stream_in, "CONIN$", "r", stdin);
		if (result_in) {
			throw FormattedException("stdin redirection failed: %d.", result_in);
		}
		// Reuse stdout to open the file "CONOUT$"
		const errno_t result_out = freopen_s(&stream_out, "CONOUT$", "w", stdout);
		if (result_out) {
			throw FormattedException("stdout redirection failed: %d.", result_out);
		}
		// Reuse stderr to open the file "CONIN$
		const errno_t result_err = freopen_s(&stream_err, "CONOUT$", "w", stderr);
		if (result_err) {
			throw FormattedException("stderr redirection failed: %d.", result_err);
		}
	}
}