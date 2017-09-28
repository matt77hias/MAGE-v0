//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LoggingConfiguration LoggingConfiguration::s_logging_configuration;

	U16 ConsoleWidth() {
		
		// Retrieve a handle to the standard output device.
		const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (handle == INVALID_HANDLE_VALUE || handle == nullptr) {
			throw FormattedException("GetStdHandle() failed.");
		}
		
		// Structure containing information about a console screen buffer.
		CONSOLE_SCREEN_BUFFER_INFO buffer_info = {};
		GetConsoleScreenBufferInfo(handle, &buffer_info);
		
		// dwSize:	a COORD structure that contains the size of the console
		//			screen buffer in character columns and rows.
		return static_cast< U16 >(buffer_info.dwSize.X);
	}

	/**
	 Handler callback for handling the user closing the console (either by 
	 clicking Close on the console window's window menu, or by clicking the 
	 End Task button command from Task Manager).

	 @param[in]		dwCtrlType
					The type of control signal received by the handler.
	 @return		@c TRUE if the function handles the control signal. 
					@c CTRL_CLOSE_EVENT. @c FALSE otherwise.
	 */
	inline BOOL WINAPI ConsoleCloseHandler(DWORD dwCtrlType) {
		return (CTRL_CLOSE_EVENT == dwCtrlType) ? TRUE : FALSE;
	}

	void InitializeConsole() {
		// Allocate a console for basic IO.
		if (!AllocConsole()) {
			throw FormattedException(
				"Console allocation failed.");
		}

		// This allows proper memory cleanup from the application itself
		// in case the console is closed by the user.
		const BOOL result = 
			SetConsoleCtrlHandler(ConsoleCloseHandler, TRUE);
		Assert(result);

		// Redirect stdin, stdout and stderr to the allocated console.
		
		// Reuse stdin to open the file "CONIN$".
		FILE *stream_in;
		const errno_t result_in = 
			freopen_s(&stream_in, "CONIN$", "r", stdin);
		if (result_in) {
			throw FormattedException(
				"stdin redirection failed: %d.", result_in);
		}
		
		// Reuse stdout to open the file "CONOUT$".
		FILE *stream_out;
		const errno_t result_out = 
			freopen_s(&stream_out, "CONOUT$", "w", stdout);
		if (result_out) {
			throw FormattedException(
				"stdout redirection failed: %d.", result_out);
		}

		// Reuse stderr to open the file "CONIN$.
		FILE *stream_err;
		const errno_t result_err = 
			freopen_s(&stream_err, "CONOUT$", "w", stderr);
		if (result_err) {
			throw FormattedException(
				"stderr redirection failed: %d.", result_err);
		}
	}
}