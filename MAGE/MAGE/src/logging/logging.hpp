#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of logging configurations of the engine processing.
	 */
	struct LoggingConfiguration final {

	public:

		/**
		 Constructs a new logging configuration.
		 */
		LoggingConfiguration() : m_quiet(false), m_verbose(false) {}

		/**
		 Destructs this logging configuration.
		 */
		~LoggingConfiguration() {}

		/**
		 Checks whether the logging of the engine processing is quiet.

		 @return		@c true if the logging of the engine processing is quiet.
						@c false otherwise.
		 */
		bool IsQuiet() const {
			return m_quiet;
		}

		/**
		 Checks wheter the logging of the engine processing is verbose.

		 @return		@c true if the logging of the engine processing is verbose.
						@c false otherwise.
		 */
		bool IsVerbose() const {
			return m_verbose;
		}

	private:

		/**
		 Flag indicating the logging of the engine processing is quiet.
		 */
		bool m_quiet;

		/**
		 Flag indicating the logging of the engine processing is verbose.
		 */
		bool m_verbose;
	};

	/**
	 The logging configuration defined by the user and used by the engine.
	 */
	extern LoggingConfiguration g_logging_configuration;

	/**
	 Returns the fixed terminal width.

	 @return		The fixed terminal width.
	 */
	inline int TerminalWidth() {
		// Retrieve a handle to the standard output device.
		const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE || h == nullptr) {
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

	/**
	 Allocates a console to this engine for basic io and
	 redirects stdin, stdout and stderr to the allocated console.

	 @return		A success/error value.
	 */
	HRESULT InitializeConsole();
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