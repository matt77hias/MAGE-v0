#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of logging configurations of the engine processing.
	 */
	class LoggingConfiguration final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the global logging configuration.

		 @return		A pointer to the global logging configuration.
		 */
		static LoggingConfiguration *Get() noexcept {
			return &s_logging_configuration;
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
		explicit LoggingConfiguration(bool quiet = false, bool verbose = false)
			: m_quiet(quiet), m_verbose(verbose) {}

		/**
		 Constructs a logging configuration from the given logging 
		 configuration.
		 
		 @param[in]		logging_configuration
						A reference to the logging configuration to copy.
		 */
		LoggingConfiguration(
			const LoggingConfiguration &logging_configuration) = default;

		/**
		 Constructs a logging configuration by moving the given logging 
		 configuration.

		 @param[in]		logging_configuration
						A reference to the logging configuration to move.
		 */
		LoggingConfiguration(
			LoggingConfiguration &&logging_configuration) = default;

		/**
		 Destructs this logging configuration.
		 */
		~LoggingConfiguration() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given logging configuration to this logging configuration.

		 @param[in]		logging_configuration
						A reference to the logging configuration to copy.
		 @return		A reference to the copy of the given logging 
						configuration (i.e. this logging configuration).
		 */
		LoggingConfiguration &operator=(
			const LoggingConfiguration &logging_configuration) = default;

		/**
		 Moves the given logging configuration to this logging configuration.

		 @param[in]		logging_configuration
						A reference to the logging configuration to move.
		 @return		A reference to the moved logging configuration (i.e. 
						this logging configuration).
		 */
		LoggingConfiguration &operator=(
			LoggingConfiguration &&logging_configuration) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether the logging of the engine processing is quiet.

		 @return		@c true if the logging of the engine processing is 
						quiet. @c false otherwise.
		 */
		bool IsQuiet() const noexcept {
			return m_quiet;
		}

		/**
		 Checks wheter the logging of the engine processing is verbose.

		 @return		@c true if the logging of the engine processing is 
						verbose. @c false otherwise.
		 */
		bool IsVerbose() const noexcept {
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

	/**
	 Returns the fixed console width.

	 @return		The fixed console width.
	 @throws		FormattedException
					Failed to retrieve a handle to the standard output device.
	 */
	U16 ConsoleWidth();

	/**
	 Allocates a console to this engine for basic io and redirects @c stdin, 
	 @c stdout and @c stderr to the allocated console.

	 @throws		FormattedException
					Failed to initialize the console.
	 */
	void InitializeConsole();
}