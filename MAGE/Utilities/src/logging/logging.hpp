#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

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
	class LoggingConfiguration final {

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
			                                    bool verbose = false) noexcept
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
	// Console
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the fixed console width.

	 @return		The fixed console width.
	 @throws		Exception
					Failed to retrieve a handle to the standard output device.
	 */
	[[nodiscard]]
	U16 ConsoleWidth();

	/**
	 Allocates a console to this engine for basic io and redirects @c stdin, 
	 @c stdout and @c stderr to the allocated console.

	 @throws		Exception
					Failed to initialize the console.
	 */
	void InitializeConsole();

	#pragma endregion
}