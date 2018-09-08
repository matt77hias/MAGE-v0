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

	/**
	 A class of engine setups.
	 */
	class EngineSetup {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an engine setup.

		 @param[in]		instance
						The application instance handle.
		 @param[in]		name
						The name of the application.
		 */
		explicit EngineSetup(NotNull< HINSTANCE > instance, 
							 std::wstring name = L"MAGE")
			: m_instance(instance),
			m_name(std::move(name)) {}

		/**
		 Constructs an engine setup from the given engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy.
		 */
		EngineSetup(const EngineSetup& setup) = default;

		/**
		 Constructs an engine setup by moving the given engine setup.

		 @param[in]		setup
						A reference to the engine setup to move.
		 */
		EngineSetup(EngineSetup&& setup) noexcept = default;

		/**
		 Destructs this engine setup.
		 */
		~EngineSetup() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given engine setup to this engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy from.
		 @return		A reference to the copy of the given engine setup (i.e. 
						this engine setup).
		 */
		EngineSetup& operator=(const EngineSetup& setup) = default;

		/**
		 Moves the given engine setup to this engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy from.
		 @return		A reference to the moved engine setup (i.e. this engine 
						setup).
		 */
		EngineSetup& operator=(EngineSetup&& setup) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the application instance handle.

		 @return		The application instance handle.
		 */
		[[nodiscard]]
		NotNull< HINSTANCE > GetApplicationInstance() const noexcept {
			return m_instance;
		}

		/**
		 Returns the name of the application.

		 @return		A reference to the name of the application.
		 */
		[[nodiscard]]
		const std::wstring& GetApplicationName() const noexcept {
			return m_name;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The application instance handle.
		 */
		NotNull< HINSTANCE > m_instance;

		/**
		 The name of the application.
		 */
		std::wstring m_name;
	};
}