#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ArgsT >
	inline void Log(MessageDisposition disposition,
					std::string_view format_str, const ArgsT&... args) {

		if (MessageDisposition::Ignore == disposition) {
			return;
		}

		Print(format_str, args...);
		Print("\n");

		if (MessageDisposition::Abort == disposition) {
			__debugbreak();
		}
	}

	template< typename... ArgsT >
	inline void Log(MessageDisposition disposition,
					std::wstring_view format_str, const ArgsT&... args) {

		if (MessageDisposition::Ignore == disposition) {
			return;
		}

		Print(format_str, args...);
		Print("\n");

		if (MessageDisposition::Abort == disposition) {
			__debugbreak();
		}
	}

	template< typename... ArgsT >
	inline void Debug([[maybe_unused]] std::string_view format_str,
					  [[maybe_unused]] const ArgsT&... args) {

		#ifdef _DEBUG
		if (  !LoggingConfiguration::Get().IsVerbose()
			|| LoggingConfiguration::Get().IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}

		Print("Debug:   ");
		Log(MessageDisposition::Continue, format_str, args...);
		#endif
	}

	template< typename... ArgsT >
	inline void Debug([[maybe_unused]] std::wstring_view format_str,
					  [[maybe_unused]] const ArgsT&... args) {

		#ifdef _DEBUG
		if (  !LoggingConfiguration::Get().IsVerbose()
			|| LoggingConfiguration::Get().IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}

		Print("Debug:   ");
		Log(MessageDisposition::Continue, format_str, args...);
		#endif
	}

	template< typename... ArgsT >
	inline void Info(std::string_view format_str, const ArgsT&... args) {
		if (  !LoggingConfiguration::Get().IsVerbose()
			|| LoggingConfiguration::Get().IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}

		Print("Info:    ");
		Log(MessageDisposition::Continue, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Info(std::wstring_view format_str, const ArgsT&... args) {
		if (  !LoggingConfiguration::Get().IsVerbose()
			|| LoggingConfiguration::Get().IsQuiet()) {
			// Do not process info in non-verbose mode.
			// Do not process info in quiet mode.
			return;
		}

		Print("Info:    ");
		Log(MessageDisposition::Continue, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Warning(std::string_view format_str, const ArgsT&... args) {
		if (LoggingConfiguration::Get().IsQuiet()) {
			// Do not process warning in quiet mode.
			return;
		}

		Print("Warning: ");
		Log(MessageDisposition::Continue, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Warning(std::wstring_view format_str, const ArgsT&... args) {
		if (LoggingConfiguration::Get().IsQuiet()) {
			// Do not process warning in quiet mode.
			return;
		}

		Print("Warning: ");
		Log(MessageDisposition::Continue, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Error(std::string_view format_str, const ArgsT&... args) {
		Print("Error:   ");
		Log(MessageDisposition::Continue, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Error(std::wstring_view format_str, const ArgsT&... args) {
		Print("Error:   ");
		Log(MessageDisposition::Continue, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Fatal(std::string_view format_str, const ArgsT&... args) {
		Print("Fatal:   ");
		Log(MessageDisposition::Abort, format_str, args...);
	}

	template< typename... ArgsT >
	inline void Fatal(std::wstring_view format_str, const ArgsT&... args) {
		Print("Fatal:   ");
		Log(MessageDisposition::Abort, format_str, args...);
	}
}