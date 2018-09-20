//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LoggingConfiguration
	//-------------------------------------------------------------------------
	#pragma region

	LoggingConfiguration LoggingConfiguration::s_logging_configuration;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Console
	//-------------------------------------------------------------------------
	#pragma region

	namespace {

		/**
		 Handler callback for handling the user closing the console (either by
		 clicking the "Close" button on the console window's window menu, or by
		 clicking the "End Task" button command from the Task Manager).

		 @param[in]		control_type
						The type of control signal received by the handler.
		 @return		@c TRUE if the function handles the control signal
						(i.e. @c CTRL_CLOSE_EVENT). @c FALSE otherwise.
		 */
		[[nodiscard]]
		constexpr BOOL WINAPI ConsoleCloseHandler(DWORD control_type) noexcept {
			return (CTRL_CLOSE_EVENT == control_type) ? TRUE : FALSE;
		}
	}

	[[nodiscard]]
	FU16 ConsoleWidth() {
		// Retrieve a handle to the standard output device.
		const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		ThrowIfFailed((nullptr != handle),
					  "Obtained no handle to the standard output device.");
		ThrowIfFailed((INVALID_HANDLE_VALUE != handle),
					  "Obtained invalid handle to the standard output device.");

		// Retrieve the screen buffer information of the console.
		CONSOLE_SCREEN_BUFFER_INFO buffer_info = {};
		{
			const BOOL result = GetConsoleScreenBufferInfo(handle,
														   &buffer_info);
			ThrowIfFailed(result,
						  "Retrieving console screen buffer info failed.");
		}

		return static_cast< FU16 >(buffer_info.dwSize.X);
	}

	void InitializeConsole() {
		// Allocate a console for basic IO.
		{
			const BOOL result = AllocConsole();
			ThrowIfFailed(result, "Console allocation failed.");
		}

		// Set console handler for handling the user closing the console.
		{
			// This allows proper memory cleanup from the application itself
			// in case the console is closed by the user.
			const BOOL result = SetConsoleCtrlHandler(ConsoleCloseHandler,
													  TRUE);
			ThrowIfFailed(result, "Setting console handler failed.");
		}

		// Redirect stdin to the allocated console.
		{
			std::FILE* stream;
			// Reuse stdin to open the file "CONIN$".
			const errno_t result
				= freopen_s(&stream, "CONIN$", "r", stdin);
			ThrowIfFailed(0 == result,
						  "stdin redirection failed: {}.", result);
		}

		// Redirect stdout to the allocated console.
		{
			std::FILE* stream;
			// Reuse stdout to open the file "CONOUT$".
			const errno_t result
				= freopen_s(&stream, "CONOUT$", "w", stdout);
			ThrowIfFailed(0 == result,
						  "stdout redirection failed: {}.", result);
		}

		// Redirect stderr to the allocated console.
		{
			std::FILE* stream;
			// Reuse stderr to open the file "CONOUT$".
			const errno_t result
				= freopen_s(&stream, "CONOUT$", "w", stderr);
			ThrowIfFailed(0 == result,
						  "stderr redirection failed: {}.", result);
		}
	}

	#pragma endregion
}