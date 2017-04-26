//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "logging\error.hpp"
#include "logging\logging.hpp"
#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of error dispositions.
	
	This contains: 
	 @c ERROR_DISPOSITION_IGNORE, 
	 @c ERROR_DISPOSITION_CONTINUE and 
	 @c ERROR_DISPOSITION_ABORT.
	 */
	enum ErrorDisposition {
		ERROR_DISPOSITION_IGNORE,	// Ignore and continue execution.
		ERROR_DISPOSITION_CONTINUE, // Report and continue execution.
		ERROR_DISPOSITION_ABORT     // Report and abort exceution.
	};

	/**
	 Finds the end of a word.

	 @pre			@a buffer is not equal to @c nullptr.
	 @param[in]		buffer
					A pointer to the first character.
	 @return		A pointer to the end of the word.
					(i.e. pointer to a space or null-terminating character)
	 */
	static const char *FindWordEnd(const char *buffer) {
		while (*buffer != '\0' && !isspace(*buffer)) {
			++buffer;
		}
		return buffer;
	}

	/**
	 Process the given error.

	 @pre			@a format is not equal to @c nullptr.
	 @param[in]		format
					The format of the error string.
	 @param[in]		args
					The arguments of the format string.
	 @param[in]		error_type
					The type of the error.
	 @param[in]		disposition
					The disposition of the error.
	 */
	static void ProcessError(const char *format, const va_list args,
		const string &error_type, ErrorDisposition disposition) {

		if (disposition == ERROR_DISPOSITION_IGNORE) {
			return;
		}

		// MAGE_ERROR_CONTINUE and MAGE_ERROR_ABORT
		// Print formatted error message
		const int width = std::max(20, ConsoleWidth() - 2);
		string error_string = error_type + ": ";
		size_t error_pos = error_string.size();

		char error_buffer[2048];
		// Write formatted output using a pointer to a list of arguments.
		vsnprintf_s(error_buffer, _countof(error_buffer), _TRUNCATE, format, args);

		const char *msg_pos = error_buffer;
		while (true) {
			while (*msg_pos != '\0' && isspace(*msg_pos)) {
				++msg_pos;
			}
			if (*msg_pos == '\0') {
				break;
			}

			// isspace(*msg_pos) == true

			const char *word_end = FindWordEnd(msg_pos);
			if (error_pos + word_end - msg_pos > width) {
				error_string += "\n    ";
				error_pos = 4;
			}
			while (msg_pos != word_end) {
				error_string += *msg_pos;
				++msg_pos;
				++error_pos;
			}
			error_string += ' ';
			++error_pos;
		}

		// Writes the error_string pointed by format to stderr.
		fprintf(stderr, "%s\n", error_string.c_str());

		if (disposition == ERROR_DISPOSITION_ABORT) {
			__debugbreak();
		}
	}

	void Debug(const char *format, ...) {
#ifdef _DEBUG
		if (!g_logging_configuration.IsVerbose() || g_logging_configuration.IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}
		
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Debug Info", ERROR_DISPOSITION_CONTINUE);
		
		// End using variable argument list.
		va_end(args);	
#endif
		UNUSED(format);
	}

	void Info(const char *format, ...) {
		if (!g_logging_configuration.IsVerbose() || g_logging_configuration.IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}

		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Info", ERROR_DISPOSITION_CONTINUE);
		
		// End using variable argument list.
		va_end(args);
	}

	void Warning(const char *format, ...) {
		if (g_logging_configuration.IsQuiet()) {
			// Do not process warning in quiet mode.
			return;
		}
		
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Warning", ERROR_DISPOSITION_CONTINUE);
		
		// End using variable argument list.
		va_end(args);
	}

	void Error(const char *format, ...) {
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Error", ERROR_DISPOSITION_CONTINUE);
		
		// End using variable argument list.
		va_end(args);
	}

	void Fatal(const char *format, ...) {
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Fatal Error", ERROR_DISPOSITION_ABORT);
		
		// End using variable argument list.
		va_end(args);
	}
}