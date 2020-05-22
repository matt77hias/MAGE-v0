#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\format.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <cassert>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

// Assert definition
// The macro NDEBUG controls whether assert statements are active or not.
#ifdef NDEBUG
	#define Assert(expr) (__noop)
#else
	#define Assert(expr) ((expr) ? (void)0 \
                                 : mage::Fatal("Assertion \"{}\" failed in {}, line {}", \
									           #expr, __FILE__, __LINE__))
#endif

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LoggingConfiguration
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of logging configurations of the engine processing.
	 */
	class LoggingConfiguration {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the global logging configuration.

		 @return		A reference to the global logging configuration.
		 */
		[[nodiscard]]
		static LoggingConfiguration& Get() noexcept {
			return s_logging_configuration;
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a logging configuration.

		 @param[in]		quiet
						Flag indicating whether quiet logging is preferred.
		 @param[in]		verbose
						Flag indicating whether verbose logging is preferred.
		 */
		constexpr explicit LoggingConfiguration(bool quiet   = false,
			                                    bool verbose = true) noexcept
			: m_quiet(quiet), m_verbose(verbose) {}

		/**
		 Constructs a logging configuration from the given logging
		 configuration.

		 @param[in]		configuration
						A reference to the logging configuration to copy.
		 */
		constexpr LoggingConfiguration(
			const LoggingConfiguration& configuration) noexcept = default;

		/**
		 Constructs a logging configuration by moving the given logging
		 configuration.

		 @param[in]		configuration
						A reference to the logging configuration to move.
		 */
		constexpr LoggingConfiguration(
			LoggingConfiguration&& configuration) noexcept = default;

		/**
		 Destructs this logging configuration.
		 */
		~LoggingConfiguration() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given logging configuration to this logging configuration.

		 @param[in]		configuration
						A reference to the logging configuration to copy.
		 @return		A reference to the copy of the given logging
						configuration (i.e. this logging configuration).
		 */
		LoggingConfiguration& operator=(
			const LoggingConfiguration& configuration) noexcept = default;

		/**
		 Moves the given logging configuration to this logging configuration.

		 @param[in]		configuration
						A reference to the logging configuration to move.
		 @return		A reference to the moved logging configuration (i.e.
						this logging configuration).
		 */
		LoggingConfiguration& operator=(
			LoggingConfiguration&& configuration) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether the logging of the engine processing is quiet.

		 @return		@c true if the logging of the engine processing is
						quiet. @c false otherwise.
		 */
		[[nodiscard]]
		constexpr bool IsQuiet() const noexcept {
			return m_quiet;
		}

		/**
		 Checks wheter the logging of the engine processing is verbose.

		 @return		@c true if the logging of the engine processing is
						verbose. @c false otherwise.
		 */
		[[nodiscard]]
		constexpr bool IsVerbose() const noexcept {
			return m_verbose;
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The global logging configuration.
		 */
		static LoggingConfiguration s_logging_configuration;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 Flag indicating the logging of the engine processing is quiet.
		 */
		bool m_quiet;

		/**
		 Flag indicating the logging of the engine processing is verbose.
		 */
		bool m_verbose;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Logging
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of message dispositions.

	 This contains:
	 @c Ignore,
	 @c Continue and
	 @c Abort.
	 */
	enum class [[nodiscard]] MessageDisposition : U8 {
		Ignore,	  // Ignore and continue execution.
		Continue, // Report and continue execution.
		Abort     // Report and abort exceution.
	};

	/**
	 Logs a message.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		disposition
					The message disposition.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Log(MessageDisposition disposition,
			 std::string_view format_str, const ArgsT&... args);

	/**
	 Logs a message.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		disposition
					The message disposition.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Log(MessageDisposition disposition,
			 std::wstring_view format_str, const ArgsT&... args);

	/**
	 Logs a debug message.

	 A debug message is associated with generally useful information to log
	 only in debug builds.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Debug([[maybe_unused]] std::string_view format_str,
			   [[maybe_unused]] const ArgsT&... args);

	/**
	 Logs a debug message.

	 A debug message is associated with generally useful information to log
	 only in debug builds.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Debug([[maybe_unused]] std::wstring_view format_str,
			   [[maybe_unused]] const ArgsT&... args);

	/**
	 Logs an info message.

	 An info message is associated with generally useful information to log.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Info(std::string_view format_str, const ArgsT&... args);

	/**
	 Logs an info message.

	 An info message is associated with generally useful information to log.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Info(std::wstring_view format_str, const ArgsT&... args);

	/**
	 Logs a warning message.

	 A warning message is associated with anything that can potentially cause
	 application oddities.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Warning(std::string_view format_str, const ArgsT&... args);

	/**
	 Logs a warning message.

	 A warning message is associated with anything that can potentially cause
	 application oddities.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Warning(std::wstring_view format_str, const ArgsT&... args);

	/**
	 Logs an error message.

	 An error message is associated with any error which is fatal to the
	 operation, but not the service or application.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Error(std::string_view format_str, const ArgsT&... args);

	/**
	 Logs an error message.

	 An error message is associated with any error which is fatal to the
	 operation, but not the service or application.

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Error(std::wstring_view format_str, const ArgsT&... args);

	/**
	 Logs a fatal message.

	 A fatal message is associated with any error that is forcing a shutdown of
	 the service or application to prevent data loss (or further data loss).

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Fatal(std::string_view format_str, const ArgsT&... args);

	/**
	 Logs a fatal message.

	 A fatal message is associated with any error that is forcing a shutdown of
	 the service or application to prevent data loss (or further data loss).

	 @tparam		ArgsT
					The format argument types.
	 @param[in]		format_str
					The format string.
	 @param[in]		args
					A reference to the format arguments.
	 */
	template< typename... ArgsT >
	void Fatal(std::wstring_view format_str, const ArgsT&... args);

	#pragma endregion

	//-------------------------------------------------------------------------
	// Console
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the fixed console width.

	 @return		The fixed console width.
	 @throws		Exception
					Failed to retrieve a valid handle to the standard output
					device.
	 @throws		Exception
					Failed to retrieve the screen buffer info of the console.
	 */
	[[nodiscard]]
	FU16 ConsoleWidth();

	/**
	 Allocates a console for basic IO and redirects @c stdin, @c stdout and
	 @c stderr to this allocated console.

	 @throws		Exception
					Failed to initialize the console.
	 */
	void InitializeConsole();

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.tpp"

#pragma endregion