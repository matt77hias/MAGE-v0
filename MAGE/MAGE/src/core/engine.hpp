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
namespace mage {
	using namespace DirectX;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Linker Directives
//-----------------------------------------------------------------------------
#pragma region

#pragma comment (lib, "d3d11.lib")

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
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p) = nullptr; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = nullptr; } }

// Supresses C4100: unreferenced formal parameter
#define UNUSED(param) (void)(param)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "version.hpp"
#include "loadable.hpp"
#include "collection\collection.hpp"
#include "parallel\parallel.hpp"
#include "string\string_utils.hpp"
#include "logging\logging.hpp"
#include "memory\memory.hpp"
#include "ui\ui.hpp"

#include "math\math.hpp"
#include "view\view.hpp"
#include "resource\resource.hpp"
#include "scripting\scripting.hpp"
#include "rendering\rendering.hpp"
#include "texture\texture.hpp"
#include "input\input.hpp"
#include "state\state.hpp"
#include "mesh\mesh.hpp"
#include "scene\scene.hpp"

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
		EngineSetup(const wstring &name = L"Application") : m_hinstance(nullptr), m_name(name), StateSetup(nullptr) {}
		
		/**
		 Constructs an engine setup from the given engine setup.

		 @param[in]		setup
						A reference to the engine setup.
		 */
		EngineSetup(const EngineSetup &setup) : m_hinstance(setup.m_hinstance), m_name(setup.m_name), StateSetup(setup.StateSetup) {}

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
						A reference to the engine setup.
		 @return		A reference to the copy of the given engine setup 
						(i.e. this engine setup).
		 */
		EngineSetup &operator=(const EngineSetup &setup);

	};

	/**
	 A class of engines.
	 */
	class Engine : public Loadable {

	public:

		/**
		 Constructs an engine from the given engine setup.

		 @param[in]		setup
						A pointer to an engine setup.
		 */
		Engine(const EngineSetup *setup = nullptr);

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
		 Returns the main window of this engine.
		 
		 @return		The main window of this engine.
		 */
		const MainWindow *GetMainWindow() const {
			return m_main_window;
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

		/**
		 Sets the mode switch flag of this engine to the given value.

		 @param[in]		mode_switch
						The new value for the mode switch flag.
		 */
		void SetModeSwitchFlag(bool mode_switch) {
			m_mode_switch = mode_switch;
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
		 Returns the input manager of this engine.

		 @return		A pointer to the input manager of this engine.
		 */
		const InputManager *GetInputManager() const {
			return m_input_manager;
		}

	protected:

		/**
		 Initializes the different systems of this engine.

		 @param[in]		setup
						A pointer to an engine setup.
		 @return		A success/error value.
		 */
		HRESULT InitializeSystems(const EngineSetup *setup);

		/**
		 Unitialize the different systems of this engine.

		 @return		A success/error value.
		 */
		HRESULT UninitializeSystems();

		/**
		 Checks whether this engine is deactive.

		 @return		@c true if this engine is deactive.
						@c false otherwise.
		 */
		bool IsDeactive() const {
			return m_deactive;
		}

		/**
		 Checks whether this engine should switch modes.

		 @return		@c true if this engine should switch modes.
						@c false otherwise.
		 */
		bool ModeSwitch() const {
			return m_mode_switch;
		}

	private:

		/**
		 Constructs an engine from the given engine.

		 @param[in]		engine
						A reference to the engine.
		 */
		Engine(const Engine &engine);

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine.
		 @return		A reference to the copy of the given engine (i.e. this engine).
		 */
		Engine &operator=(const Engine &engine);


		// WINDOW SYSTEM

		/**
		 A pointer to the main window of this engine. 
		 */
		MainWindow *m_main_window;
		
		/** 
		 Flag indicating whether the application is active or not.
		 */
		bool m_deactive;

		// RENDERER SYSTEM

		/**
		 A pointer to the renderer of this engine.
		 */
		Renderer *m_renderer;

		/**
		 Flag indicating whether the application should switch between
		 full screen and windowed mode.
		 */
		bool m_mode_switch;

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
		 A pointer to the input manager of this engine.
		 */
		InputManager *m_input_manager;
	};

	/**
	 The engine used by the user.
	 */
	extern Engine *g_engine;
}
