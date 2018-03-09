#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine_setup.hpp"
#include "input_manager.hpp"
#include "rendering_manager.hpp"
#include "system\timer.hpp"
#include "ui\window.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	#pragma region

	// Forward dclaration.
	class Scene;

	/**
	 A class of engines.
	 */
	class Engine final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an engine from the given engine setup.

		 @param[in]		setup
						A reference to an engine setup.
		 @param[in]		display_config
						The display configuration.
		 @throws		Exception
						Failed to initialize the engine.
		 */
		explicit Engine(const EngineSetup& setup, 
						rendering::DisplayConfiguration display_config);

		/**
		 Constructs an engine from the given engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 */
		Engine(const Engine& engine) = delete;

		/**
		 Constructs an engine by moving the given engine.

		 @param[in]		engine
						A reference to the engine to move.
		 */
		Engine(Engine&& engine) noexcept;

		/**
		 Destructs this engine.
		 */
		~Engine();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 @return		A reference to the copy of the given engine (i.e. this 
						engine).
		 */
		Engine& operator=(const Engine& engine) = delete;

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to move.
		 @return		A reference to the moved engine (i.e. this engine).
		 */
		Engine& operator=(Engine&& engine) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Runs this engine.

		 @param[in]		scene
						A reference to the start scene.
		 @param[in]		nCmdShow
						Controls how the engine window is to be shown.
		 @return		@c 0, if the function terminates before entering the 
						message loop.
		 @return		The @c wParam parameter contained in the @c WM_QUIT 
						message.
		 */
		[[nodiscard]]
		int Run(UniquePtr< Scene >&& scene, int nCmdShow = SW_NORMAL);

		/**
		 Returns the input manager of this engine.

		 @return		A reference to the input manager of this engine.
		 */
		[[nodiscard]]
		input::Manager& GetInputManager() noexcept {
			return *m_input_manager;
		}

		/**
		 Returns the input manager of this engine.

		 @return		A reference to the input manager of this engine.
		 */
		[[nodiscard]]
		const input::Manager& GetInputManager() const noexcept {
			return *m_input_manager;
		}

		/**
		 Returns the rendering manager of this engine.

		 @return		A reference to the rendering manager of this engine.
		 */
		[[nodiscard]]
		rendering::Manager& GetRenderingManager() noexcept {
			return *m_rendering_manager;
		}

		/**
		 Returns the rendering manager of this engine.

		 @return		A reference to the rendering manager of this engine.
		 */
		[[nodiscard]]
		const rendering::Manager& GetRenderingManager() const noexcept {
			return *m_rendering_manager;
		}

		/**
		 Sets the scene of this engine to the given scene.

		 @param[in]		scene
						A reference to the start scene.
		 */
		void RequestScene(UniquePtr< Scene >&& scene) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the different systems of this engine.

		 @param[in]		setup
						A reference to an engine setup.
		 @param[in]		display_config
						The display configuration.
		 @throws		Exception
						Failed to initialize at least one of the different 
						systems of this engine.
		 */
		void InitializeSystems(const EngineSetup& setup,
							   rendering::DisplayConfiguration display_config);

		/**
		 Uninitializes the different systems of this engine.
		 */
		void UninitializeSystems() noexcept;

		/**
		 Notifies this engine of a change in activeness.

		 Call this method when the engine becomes active or deactive.

		 @param[in]		deactive
						@c true if this engine becomes deactive. @c false
						otherwise.
		 */
		void OnActiveChange(bool deactive) noexcept;

		/**
		 Notifies this engine of a change in display mode.

		 Call this method when the engine needs to switch its current
		 (windowed|fullscreen) display mode.
		 */
		void OnModeSwitch() noexcept;

		void ApplyRequestedScene();

		[[nodiscard]]
		bool UpdateInput();
		
		[[nodiscard]]
		bool UpdateRendering();
		
		[[nodiscard]]
		bool UpdateScripting();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the window of this engine.
		 */
		UniquePtr< Window > m_window;

		/**
		 A pointer to the input manager of this engine.
		 */
		UniquePtr< input::Manager > m_input_manager;

		/**
		 A pointer to the rendering manager of this engine.
		 */
		UniquePtr< rendering::Manager > m_rendering_manager;

		/**
		 A pointer to the current scene of this engine.
		 */
		UniquePtr< Scene > m_scene;

		/**
		 A pointer to the requested scene of this engine.
		 */
		UniquePtr< Scene > m_requested_scene;

		/**
		 The timer of this engine.
		 */
		WallClockTimer m_timer;

		/**
		 The fixed delta time of this engine.

		 If the fixed delta time is equal to zero, fixed delta time updates
		 will be treated as non-fixed delta time updates by this engine.
		 */
		F64 m_fixed_delta_time;

		/**
		 The fixed time budget of this engine.
		 */
		F64 m_fixed_time_budget;

		/**
		 Flag indicating whether the application is active or not.
		 */
		bool m_deactive;

		/**
		 Flag indicating whether the application should switch between full
		 screen and windowed mode.
		 */
		bool m_mode_switch;

		/**
		 A flag indicating whether this engine has a requested scene.
		 
		 A separate flag is needed, because the requested scene maybe 
		 @c nullptr.
		 */
		bool m_has_requested_scene;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory
	//-------------------------------------------------------------------------
	#pragma region

	UniquePtr< Engine > CreateEngine(const EngineSetup& setup);

	#pragma endregion
}
