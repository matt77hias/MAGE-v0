//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"
#include "logging\logging.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	namespace {

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
		 Finds the start of the next word.

		 @param[in]		str
						A pointer to the null-terminated string.
		 @return		A pointer to the null-terminating character if the end of 
						the given string is reached.
		 @return		A pointer to the start of the next word.
		 */
		[[nodiscard]]
		inline NotNull< const_zstring > 
			FindWordStart(NotNull< const_zstring > str) noexcept {

			const char* buffer = str;
			while ('\0' != *buffer && isspace(*buffer)) {
				++buffer;
			}

			return NotNull< const_zstring >(buffer);
		}

		/**
		 Finds the end of the current word.

		 @param[in]		str
						A pointer to the null-terminated string.
		 @return		A pointer to the null-terminating character if the end of 
						the given string is reached.
		 @return		A pointer to the end of the current word (i.e. space).
		 */
		[[nodiscard]]
		inline NotNull< const_zstring > 
			FindWordEnd(NotNull< const_zstring > str) noexcept {
		
			const char* buffer = str;
			while ('\0' != *buffer && !isspace(*buffer)) {
				++buffer;
			}

			return NotNull< const_zstring >(buffer);
		}

		/**
		 Process the given error.

		 @param[in]		format
						The format of the error string.
		 @param[in]		args
						The arguments of the format string.
		 @param[in]		error_type
						The type of the error.
		 @param[in]		disposition
						The disposition of the error.
		 */
		void ProcessError(const_zstring format, 
						  va_list args, 
						  const std::string& error_type,
						  ErrorDisposition disposition) {

			if (ErrorDisposition::Ignore == disposition) {
				return;
			}

			// Print formatted error message
			const auto width 
				= static_cast< size_t >(std::max(20, ConsoleWidth() - 2));
			std::string error_string = error_type + ": ";
			auto error_pos           = error_string.size();

			char error_buffer[2048];
			vsnprintf_s(error_buffer, std::size(error_buffer), 
						_TRUNCATE, format, args);

			const auto* msg_pos = error_buffer;
			while (true) {
				msg_pos = FindWordStart(NotNull< const_zstring >(msg_pos));

				if ('\0' == *msg_pos) {
					break;
				}

				// false == isspace(*msg_pos)

				const auto word_end = FindWordEnd(NotNull< const_zstring >(msg_pos));
				if (const auto word_length 
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
	}

	void Debug([[maybe_unused]] const_zstring format, ...) {
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

	void Info(const_zstring format, ...) {
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

	void Warning(const_zstring format, ...) {
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

	void Error(const_zstring format, ...) {
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);
		
		ProcessError(format, args, "Error", ErrorDisposition::Continue);
		
		// End using variable argument list.
		va_end(args);
	}

	void Fatal(const_zstring format, ...) {
		va_list args;
		
		// Retrieve the additional arguments after format.
		va_start(args, format);

		ProcessError(format, args, "Fatal Error", ErrorDisposition::Abort);
		
		// End using variable argument list.
		va_end(args);
	}
}