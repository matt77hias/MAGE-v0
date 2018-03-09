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
	// EngineMessageHandler
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of engine message handlers.
	 */
	class EngineMessageHandler final : public WindowMessageHandler {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a engine message handler.
		 */
		EngineMessageHandler();

		/**
		 Constructs a engine message handler from the given engine message 
		 handler.

		 @param[in]		handler
						A reference to the engine message handler to copy.
		 */
		EngineMessageHandler(const EngineMessageHandler& handler);

		/**
		 Constructs a engine message handler by moving the given engine message 
		 handler.

		 @param[in]		handler
						A reference to the engine message handler to move.
		 */
		EngineMessageHandler(EngineMessageHandler&& handler) noexcept;

		/**
		 Destructs this engine message handler.
		 */
		virtual ~EngineMessageHandler();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given engine message handler to this engine message 
		 handler.

		 @param[in]		handler
						A reference to the engine message handler to copy.
		 @return		A reference to the copy of the given engine message 
						handler (i.e. this engine message handler).
		 */
		EngineMessageHandler& operator=(const EngineMessageHandler& handler);

		/**
		 Moves the given engine message handler to this engine message handler.

		 @param[in]		handler
						A reference to the engine message handler to move.
		 @return		A reference to the moved engine message handler (i.e. 
						this engine message handler).
		 */
		EngineMessageHandler& operator=(EngineMessageHandler&& handler) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Handles the given message sent to a window.

		 @param[in]		window
						A handle to the window.
		 @param[in]		message
						The message.
		 @param[in]		wParam
						Additional message information. The contents of this 
						parameter depend on the value of @a msg.
		 @param[in]		lParam
						Additional message information. The contents of this 
						parameter depend on the value of @a msg.
		 @param[out]	result
						The result of the message processing in case the 
						message is handled by this engine message handler.
		 @return		@c true if the given message is handled by this engine 
						message handler. @c false otherwise.
		 */
		[[nodiscard]]
		virtual bool HandleWindowMessage([[maybe_unused]] NotNull< HWND > window,
										 UINT message, 
										 [[maybe_unused]] WPARAM wParam,
										 [[maybe_unused]] LPARAM lParam,
										 LRESULT& result) override;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		std::function< void(bool) > m_on_active_change;

		std::function< void() > m_on_mode_switch;

		std::function< void() > m_on_print_screen;
	};

	#pragma endregion

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
		const input::Manager& GetInputManager() const noexcept {
			return *m_input_manager;
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
		 The window message handler of this engine.
		 */
		EngineMessageHandler m_message_handler;

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
