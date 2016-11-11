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

#include <d3d11_2.h>
#include <directxmath.h>
using namespace DirectX;

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

// Memory management macros
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p) = NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = NULL; } }

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

// Forward declaration
namespace mage {
	class Engine;
}

#include "version.hpp"
#include "collection\collection.hpp"
#include "math\math.hpp"
#include "parallel\parallel.hpp"
#include "logging\logging.hpp"
#include "memory\memory.hpp"

#include "resource\resource.hpp"
#include "state\state.hpp"
#include "scripting\scripting.hpp"
#include "input\input.hpp"
#include "rendering\rendering.hpp"

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
		 Runs this engine.

		 @param[in]		nCmdShow
						Controls how the engine window is to be shown.
		 */
		void Run(int nCmdShow = SW_NORMAL);

		// WINDOW SYSTEM

		/**
		 Returns a handle to the window of this engine.
		 
		 @return		A handle to the window of this engine.
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

		// RENDERER SYSTEM

		/**
		 Returns the renderer of this engine.

		 @return		A pointer to the renderer of this engine.
		 */
		Renderer *GetRenderer() const {
			return m_renderer;
		}

		// STATE SYSTEM

		/**
		 Returns the state manager of this engine.

		 @return		A pointer to the state manager of this engine.
		 */
		StateManager *GetStateManager() const {
			return m_state_manager;
		}
		
		// SCRIPTING SYSTEM

		/**
		 Returns the script manager of this engine.

		 @return		A pointer to the script manager of this engine.
		*/
		ResourceManager< VariableScript > *GetScriptManager() const {
			return m_script_manager;
		}

		// INPUT SYSTEM

		/**
		 Returns the input object of this engine.

		 @return		A pointer to the input object of this engine.
		 */
		const Input *GetInput() const {
			return m_input;
		}

	protected:

		/**
		 Initializes the engine window of this engine.

		 @return		A success/error value.
		 */
		HRESULT InitializeWindow();

		/**
		 Unitializes the engine window of this engine.

		 @return		A success/error value.
		 */
		HRESULT UninitializeWindow();

		/**
		 Allocates a console to this engine for basic io and
		 redirects stdin, stdout and stderr to the allocated console.

		 @return		A success/error value.
		 */
		HRESULT AttachConsole();

		/**
		 Initializes the different systems of this engine.

		 @return		A success/error value.
		 */
		HRESULT InitializeSystems();

		/**
		 Unitialize the different systems of this engine.

		 @return		A success/error value.
		 */
		HRESULT UninitializeSystems();

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

		// RENDERER SYSTEM

		/**
		 A pointer to the renderer of this engine.
		 */
		Renderer *m_renderer;

		// STATE SYSTEM

		/**
		 A pointer to the state manager of this engine.
		 */
		StateManager *m_state_manager;

		// SCRIPTING SYSTEM

		/**
		 A pointer the script manager of this engine
		 */
		ResourceManager< VariableScript > *m_script_manager;

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
