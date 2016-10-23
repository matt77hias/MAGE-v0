#pragma once

#include "targetver.h"

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
using std::string;
using std::wstring;
#include <iostream>
using std::cin;
using std::cout;

#include <windows.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#ifndef MAGE_POINTER_SIZE
#if defined(__amd64__) || defined(_M_X64)
#define MAGE_POINTER_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
#define MAGE_POINTER_SIZE 4
#endif
#endif

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------

/**
 The namespace for all the MAGE functionality.
 */
namespace mage {

	/**
	 A struct of general configurations (of the logging) of the engine processing.
	 */
	struct GeneralConfiguration {

		/**
		 Constructs a new general configuration.
		 */
		GeneralConfiguration() : m_quiet(false), m_verbose(false) {}

		/**
		 Checks whether the logging of the engine processing is quiet.

		 @return		@c true if the logging of the engine processing is quiet.
						@c false otherwise.
		 */
		bool IsQuiet() const {
			return m_quiet;
		}

		/**
		 Checks wheter the logging of the engine processing is verbose.

		 @return		@c true if the logging of the engine processing is verbose.
						@c false otherwise.
		 */
		bool IsVerbose() const {
			return m_verbose;
		}

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
	 The general configuration defined by the user and used by the engine.
	 */
	extern GeneralConfiguration general_configuration;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "version.hpp"
#include "collection\collection.hpp"
#include "math\math.hpp"
#include "parallel\parallel.hpp"
#include "log\log.hpp"
#include "memory\memory.hpp"
#include "resource\resource.hpp"
#include "state\state.hpp"

#include "io\io.hpp"

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
		EngineSetup(const wstring &name = L"Application") : m_hinstance(NULL), m_name(name), StateSetup(NULL) {}
		
		/**
		 Constructs an engine setup from the given engine setup.

		 @pre			setup does not point to @c NULL.
		 @param[in]		setup
						A pointer to the engine setup.
		*/
		EngineSetup(const EngineSetup *setup) : m_hinstance(setup->m_hinstance), m_name(setup->m_name), StateSetup(setup->StateSetup) {}

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
	};

	/**
	 A class of engines.
	 */
	class Engine {

	public:

		/**
		 Constructs an engine from the given engine setup.

		 @param[in]		setup
						A pointer to an engine setup.
		 */
		Engine(const EngineSetup *setup = NULL);

		/**
		 Destructs this engine.
		 */
		virtual ~Engine();

		/**
		 Runs the engine setup.
		 */
		void Run();

		// WINDOW SYSTEM

		/**
		 Returns a handle to the window of this engine.
		 */
		HWND GetWindow() const {
			return m_hwindow;
		}
		
		/**
		 Sets the deactive flag of this engine to the given value.

		 @param[in]		deactive
						The new value for the deactive flag.	
		 */
		void SetDeactiveFlag(bool deactive) {
			m_deactive = deactive;
		}

		// STATE SYSTEM

		/**
		 Returns the state manager of this engine.

		 @return		A pointer to the state manager of this engine
		*/
		StateManager *GetStateManager() const {
			return m_state_manager;
		}
		
		// INPUT SYSTEM

		/**
		 Returns the input object of this engine.

		 @return		A pointer to the input object of this engine
		 */
		Input *GetInput() const {
			return m_input;
		}

	private:

		/**
		 Pointer to a copy of the engine setup structure.
		 */
		EngineSetup *m_setup;

		/**
		 Flag indicating whether this engine is loaded.
		 */
		bool m_loaded;
		
		// WINDOW SYSTEM

		/**
		 Main window handle of this engine.
		 */
		HWND m_hwindow;
		
		/** 
		 Flag indicating whether the application is active or not.
		*/
		bool m_deactive;

		// STATE SYSTEM

		/**
		 A pointer to the state manager of this engine.
		 */
		StateManager *m_state_manager;

		// INPUT SYSTEM

		/**
		 A pointer to the input object of this engine.
		 */
		Input *m_input;
	};

	/**
	 The engine used by the user.
	 */
	extern Engine *g_engine;
}