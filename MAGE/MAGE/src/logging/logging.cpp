//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "logging\logging.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	uint16_t ConsoleWidth() {
		// Retrieve a handle to the standard output device.
		const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE || h == nullptr) {
			Error("GetStdHandle() failed.");
			return 80;
		}
		// Structure containing information about a console screen buffer.
		CONSOLE_SCREEN_BUFFER_INFO buffer_info;
		ZeroMemory(&buffer_info, sizeof(buffer_info));
		GetConsoleScreenBufferInfo(h, &buffer_info);
		// dwSize:	a COORD structure that contains the size of the console
		//			screen buffer in character columns and rows.
		return (uint16_t)buffer_info.dwSize.X;
	}

	HRESULT InitializeConsole() {
		// Allocate a console for basic io
		if (!AllocConsole()) {
			Error("Console allocation failed.");
			return E_FAIL;
		}

		FILE *stream_in, *stream_out, *stream_err;
		// Redirect stdin, stdout and stderr to the allocated console
		// Reuse stdin to open the file "CONIN$"
		const errno_t result_in = freopen_s(&stream_in, "CONIN$", "r", stdin);
		if (result_in) {
			Error("stdin redirection failed: %d.", result_in);
			return E_FAIL;
		}
		// Reuse stdout to open the file "CONOUT$"
		const errno_t result_out = freopen_s(&stream_out, "CONOUT$", "w", stdout);
		if (result_out) {
			Error("stdout redirection failed: %d.", result_out);
			return E_FAIL;
		}
		// Reuse stderr to open the file "CONIN$
		const errno_t result_err = freopen_s(&stream_err, "CONOUT$", "w", stderr);
		if (result_err) {
			Error("stderr redirection failed: %d.", result_err);
			return E_FAIL;
		}

		return S_OK;
	}
}