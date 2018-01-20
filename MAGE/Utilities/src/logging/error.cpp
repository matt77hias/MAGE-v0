//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "logging\logging.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>
#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of error dispositions.
	
	This contains: 
	 @c Ignore, 
	 @c Continue and 
	 @c Abort.
	 */
	enum class [[nodiscard]] ErrorDisposition : U8 {
		Ignore,	  // Ignore and continue execution.
		Continue, // Report and continue execution.
		Abort     // Report and abort exceution.
	};

	/**
	 Finds the start of a word.

	 @pre			@a buffer is not equal to @c nullptr.
	 @param[in]		buffer
					A pointer to the first character.
	 @return		A pointer to the start of the word.
					(i.e. pointer to a space or null-terminating character)
	 */
	[[nodiscard]] static const char *FindWordStart(const char *buffer) {
		while ('\0' != *buffer && isspace(*buffer)) {
			++buffer;
		}

		return buffer;
	}

	/**
	 Finds the end of a word.

	 @pre			@a buffer is not equal to @c nullptr.
	 @param[in]		buffer
					A pointer to the first character.
	 @return		A pointer to the end of the word.
					(i.e. pointer to a space or null-terminating character)
	 */
	[[nodiscard]] static const char *FindWordEnd(const char *buffer) {
		while ('\0' != *buffer && !isspace(*buffer)) {
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
	static void ProcessError(const char *format, 
		                     const va_list args,
		                     const string &error_type, 
		                     ErrorDisposition disposition) {

		if (ErrorDisposition::Ignore == disposition) {
			return;
		}

		// Print formatted error message
		const size_t width  = std::max(20, ConsoleWidth() - 2);
		string error_string = error_type + ": ";
		size_t error_pos    = error_string.size();

		char error_buffer[2048];
		vsnprintf_s(error_buffer, std::size(error_buffer), 
			        _TRUNCATE, format, args);

		const char *msg_pos = error_buffer;
		while (true) {
			msg_pos = FindWordStart(msg_pos);

			if ('\0' == *msg_pos) {
				break;
			}

			// false == isspace(*msg_pos)

			const char * const word_end  = FindWordEnd(msg_pos);
			if (const size_t word_length 
				= static_cast< size_t >(word_end - msg_pos);
				width < error_pos + word_length) {

				error_string += "\n    ";
				error_pos     = 4;
			}

			while (word_end != msg_pos) {
				error_string += *msg_pos;
				++msg_pos;
				++error_pos;
			}

			error_string += ' ';
			++error_pos;
		}

		fprintf(stderr, "%s\n", error_string.c_str());

		if (ErrorDisposition::Abort == disposition) {
			__debugbreak();
		}
	}

	void Debug([[maybe_unused]] const char *format, ...) {
		#ifdef _DEBUG
		if (!LoggingConfiguration::Get().IsVerbose() 
			|| LoggingConfiguration::Get().IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}
		
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Debug Info", ErrorDisposition::Continue);
		
		// End using variable argument list.
		va_end(args);	
		#endif
	}

	void Info(const char *format, ...) {
		if (!LoggingConfiguration::Get().IsVerbose() 
			|| LoggingConfiguration::Get().IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}

		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Info", ErrorDisposition::Continue);
		
		// End using variable argument list.
		va_end(args);
	}

	void Warning(const char *format, ...) {
		if (LoggingConfiguration::Get().IsQuiet()) {
			// Do not process warning in quiet mode.
			return;
		}
		
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Warning", ErrorDisposition::Continue);
		
		// End using variable argument list.
		va_end(args);
	}

	void Error(const char *format, ...) {
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Error", ErrorDisposition::Continue);
		
		// End using variable argument list.
		va_end(args);
	}

	void Fatal(const char *format, ...) {
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Fatal Error", ErrorDisposition::Abort);
		
		// End using variable argument list.
		va_end(args);
	}
}