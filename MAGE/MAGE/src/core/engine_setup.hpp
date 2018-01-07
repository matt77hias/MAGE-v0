#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_APPLICATION_NAME L"Game"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of engine setups.
	 */
	class EngineSetup final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an engine setup.

		 @pre			@a hinstance is not equal to @c nullptr.
		 @param[in]		hinstance
						The application instance handle of the application.
		 @param[in]		name
						The name of the application.
		 */
		explicit EngineSetup(HINSTANCE hinstance, 
			wstring name = MAGE_DEFAULT_APPLICATION_NAME)
			: m_hinstance(hinstance),
			m_name(std::move(name)) {

			Assert(m_hinstance);
		}

		/**
		 Constructs an engine setup from the given engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy.
		 */
		EngineSetup(const EngineSetup &setup) = default;

		/**
		 Constructs an engine setup by moving the given engine setup.

		 @param[in]		setup
						A reference to the engine setup to move.
		 */
		EngineSetup(EngineSetup &&setup) noexcept = default;

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
		EngineSetup &operator=(const EngineSetup &setup) = default;

		/**
		 Moves the given engine setup to this engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy from.
		 @return		A reference to the moved engine setup (i.e. this engine 
						setup).
		 */
		EngineSetup &operator=(EngineSetup &&setup) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the name of the application.

		 @return		A reference to the name of the application.
		 */
		const wstring &GetApplicationName() const noexcept {
			return m_name;
		}

		/**
		 Returns the application instance handle of the application.

		 @return		The application instance handle of the application.
		 */
		HINSTANCE GetApplicationHinstance() const noexcept {
			return m_hinstance;
		}
	
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 Application instance handle.
		 */
		HINSTANCE m_hinstance;

		/**
		 Name of the application.
		 */
		wstring m_name;
	};
}