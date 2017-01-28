#pragma once

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
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of engine setups.
	 */
	struct EngineSetup {

	public:

		/**
		 Constructs an engine setup with the given application name.

		 @param[in]		name
						A reference to the name of the application.
		 */
		EngineSetup(const wstring &name = L"Application")
			: m_hinstance(nullptr), m_name(name), StateSetup(nullptr) {}

		/**
		 Constructs an engine setup from the given engine setup.

		 @param[in]		setup
						A reference to the engine setup.
		 */
		EngineSetup(const EngineSetup &setup)
			: m_hinstance(setup.m_hinstance), m_name(setup.m_name), StateSetup(setup.StateSetup) {}

		/**
		 Destructs this engine setup.
		 */
		virtual ~EngineSetup() {}

		/**
		 Application instance handle.
		 */
		HINSTANCE m_hinstance;

		/**
		 Name of the application.
		 */
		 wstring m_name;

		/**
		 The state setup function.
		 */
		void(*StateSetup)();

	private:

		/**
		 Copies the given engine setup to this engine setup.

		 @param[in]		setup
						A reference to the engine setup to copy from.
		 @return		A reference to the copy of the given engine setup
						(i.e. this engine setup).
		 */
		EngineSetup &operator=(const EngineSetup &setup) = delete;
	};
}