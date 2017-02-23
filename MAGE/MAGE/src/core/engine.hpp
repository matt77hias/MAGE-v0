#pragma once

#include "targetver.hpp"

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\device_enumeration.hpp"
#include "rendering\renderer.hpp"
#include "input\input_manager.hpp"
#include "ui\main_window.hpp"

#include "engine_setup.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of engines.
	 */
	class Engine : public Loadable {

	public:

		/**
		 Constructs an engine from the given engine setup.

		 @param[in]		setup
						A reference to an engine setup.
		 */
		Engine(const EngineSetup &setup);

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
		 
		 @return		A reference to the main window of this engine.
		 */
		const MainWindow &GetMainWindow() const {
			return *m_main_window;
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

		 @return		A reference to the renderer of this engine.
		 */
		Renderer &GetRenderer() const {
			return *m_renderer;
		}

		/**
		 Sets the mode switch flag of this engine to the given value.

		 @param[in]		mode_switch
						The new value for the mode switch flag.
		 */
		void SetModeSwitchFlag(bool mode_switch) {
			m_mode_switch = mode_switch;
		}

		// INPUT SYSTEM

		/**
		 Returns the input manager of this engine.

		 @return		A reference to the input manager of this engine.
		 */
		const InputManager &GetInputManager() const {
			return *m_input_manager;
		}

		// SCENE

		/**
		 Sets the scene of this engine to the given scene.

		 @return		A pointer to the scene to set.
		 */
		void SetScene(SharedPtr< Scene > scene);

	private:

		/**
		 Constructs an engine from the given engine.

		 @param[in]		engine
						A reference to the engine.
		 */
		Engine(const Engine &engine) = delete;

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to copy from.
		 @return		A reference to the copy of the given engine
						(i.e. this engine).
		 */
		Engine &operator=(const Engine &engine) = delete;

		/**
		 Initializes the different systems of this engine.

		 @param[in]		setup
						A reference to an engine setup.
		 @return		A success/error value.
		*/
		HRESULT InitializeSystems(const EngineSetup &setup);

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

		// WINDOW SYSTEM

		/**
		 A pointer to the main window of this engine. 
		 */
		UniquePtr< MainWindow > m_main_window;
		
		/** 
		 Flag indicating whether the application is active or not.
		 */
		bool m_deactive;

		// RENDERER SYSTEM

		/**
		 A pointer to the renderer of this engine.
		 */
		UniquePtr< Renderer > m_renderer;

		/**
		 Flag indicating whether the application should switch between
		 full screen and windowed mode.
		 */
		bool m_mode_switch;

		// INPUT SYSTEM

		/**
		 A pointer to the input manager of this engine.
		 */
		UniquePtr< InputManager > m_input_manager;

		// SCENE

		/**
		 The current scene of this engine.
		 */
		SharedPtr< Scene > m_scene;
	};

	/**
	 The engine used by the user.
	 */
	extern Engine *g_engine;
}
