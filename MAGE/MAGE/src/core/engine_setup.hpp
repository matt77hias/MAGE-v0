#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <string>
namespace mage {
	using std::wstring;
}

#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_APPLICATION_NAME L"Application"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of engine setups.
	 */
	struct EngineSetup final {

	public:

		/**
		 Constructs an engine setup.

		 @param[in]		hinstance
						The application instance handle of the application. 
		 @param[in]		name
						A reference to the name of the application.
		 @param[in]		StateSetupFunction
						A pointer to a function to set up the states of the application.
		 */
		EngineSetup(HINSTANCE hinstance = nullptr, const wstring &name = MAGE_DEFAULT_APPLICATION_NAME, void(*StateSetupFunction)() = nullptr)
			: m_hinstance(hinstance), m_name(name), StateSetup(StateSetupFunction) {}

		/**
		 Constructs an engine setup from the given engine setup.

		 @param[in]		setup
						A reference to the engine setup.
		 */
		EngineSetup(const EngineSetup &setup) = default;

		/**
		 Destructs this engine setup.
		 */
		~EngineSetup() = default;

		/**
		 Returns the name of the application.

		 @return		A reference to the name of the application.
		 */
		const wstring &GetApplicationName() const {
			return m_name;
		}

		/**
		 Returns the application instance handle of the application.

		 @return		The application instance handle of the application.
		 */
		HINSTANCE GetApplicationHinstance() const {
			return m_hinstance;
		}
	
		/**
		 Sets up the states of the application.
		 */
		void SetupApplicationStates() const {
			if (StateSetup) {
				StateSetup();
			}
		}

	private:

		/**
		 Copies the given engine setup to this engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy from.
		 @return		A reference to the copy of the given engine setup
						(i.e. this engine setup).
		 */
		EngineSetup &operator=(const EngineSetup &setup) = delete;

		/**
		 Application instance handle.
		 */
		HINSTANCE m_hinstance;

		/**
		 Name of the application.
		 */
		const wstring m_name;

		/**
		 The state setup function.
		 */
		void(*StateSetup)();
	};
}