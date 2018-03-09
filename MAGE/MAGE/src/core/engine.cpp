//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "meta\version.hpp"
#include "exception\exception.hpp"
#include "logging\dump.hpp"
#include "logging\error.hpp"
#include "logging\logging.hpp"
#include "display\display_configurator.hpp"
#include "system\timer.hpp"
#include "ui\window.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Engine::Impl
	//-------------------------------------------------------------------------

	/**
	 A class of engines.
	 */
	class Engine::Impl final {

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
		explicit Impl(const EngineSetup& setup, 
					  rendering::DisplayConfiguration display_config);

		/**
		 Constructs an engine from the given engine.

		 @param[in]		engine
						A reference to the engine to copy.
		 */
		Impl(const Impl& engine) = delete;

		/**
		 Constructs an engine by moving the given engine.

		 @param[in]		engine
						A reference to the engine to move.
		 */
		Impl(Impl&& engine) noexcept;

		/**
		 Destructs this engine.
		 */
		~Impl();

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
		Impl &operator=(const Impl &engine) = delete;

		/**
		 Copies the given engine to this engine.

		 @param[in]		engine
						A reference to the engine to move.
		 @return		A reference to the moved engine (i.e. this engine).
		 */
		Impl &operator=(Impl &&engine) = delete;

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
		void OnModeSwitch() noexcept {
			m_mode_switch = true;
		}

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

	Engine::Impl::Impl(const EngineSetup& setup, 
					   rendering::DisplayConfiguration display_config)
		: m_window(), 
		m_input_manager(), 
		m_rendering_manager(), 
		m_scene(), 
		m_requested_scene(), 
		m_timer(), 
		m_fixed_delta_time(0.0), 
		m_fixed_time_budget(0.0),
		m_deactive(false), 
		m_mode_switch(false), 
		m_has_requested_scene(false) {

		// Initialize the systems of this engine.
		InitializeSystems(setup, std::move(display_config));
	}

	Engine::Impl::Impl(Impl&& engine) noexcept = default;
	
	Engine::Impl::~Impl() {
		// Uninitialize the systems of this engine.
		UninitializeSystems();
	}

	void Engine::Impl
		::InitializeSystems(const EngineSetup& setup, 
							rendering::DisplayConfiguration display_config) {

		// Initialize the window.
		{
			auto window_desc
				= MakeShared< WindowDescriptor >(setup.GetApplicationInstance(),
													L"MAGE");

			m_window = MakeUnique< Window >(std::move(window_desc),
											setup.GetApplicationName(),
											display_config.GetDisplayWidth(),
											display_config.GetDisplayHeight());
		}
		
		// Initialize the input system.
		m_input_manager = MakeUnique< input::Manager >(m_window->GetWindow());

		// Initialize the rendering system.
		m_rendering_manager = MakeUnique< rendering::Manager >(m_window->GetWindow(), 
															   std::move(display_config));
		m_rendering_manager->BindPersistentState();
		
		// Initializes the COM library for use by the calling thread and sets 
		// the thread's concurrency model to multithreaded concurrency.
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	}

	void Engine::Impl::UninitializeSystems() noexcept {
		// Uninitialize the COM library.
		CoUninitialize();

		// Uninitialize the scene system.
		m_scene.reset();
		// Uninitialize the rendering system.
		m_rendering_manager.reset();
		// Uninitialize the input system.
		m_input_manager.reset();
		// Uninitialize the window system.
		m_window.reset();
	}

	void Engine::Impl::OnActiveChange(bool deactive) noexcept {
		m_deactive = deactive;
		
		if (m_deactive) {
			m_timer.Stop();
		}
		else {
			m_timer.Resume();
		}
	}

	void Engine::Impl::RequestScene(UniquePtr< Scene >&& scene) noexcept {
		m_requested_scene     = std::move(scene);
		m_has_requested_scene = true;
	}

	void Engine::Impl::ApplyRequestedScene() {
		if (m_scene) {
			m_scene->Uninitialize();
		}

		m_scene               = std::move(m_requested_scene);
		m_requested_scene     = nullptr;
		m_has_requested_scene = false;

		if (m_scene) {
			m_scene->Initialize();

			m_timer.Restart();
			m_fixed_time_budget = 0.0;
		}
	}

	[[nodiscard]]
	bool Engine::Impl::UpdateInput() {
		// Update the input manager.
		m_input_manager->Update();
		
		// Handle forced exit.
		if (m_input_manager->GetKeyboard().GetKeyPress(DIK_F1)) {
			PostQuitMessage(0);
			return true;
		}
		
		return false;
	}

	[[nodiscard]]
	bool Engine::Impl::UpdateRendering() {
		// Handle switch between full screen and windowed mode.
		auto& swap_chain     = m_rendering_manager->GetSwapChain();
		const auto lost_mode = swap_chain.LostMode();
		if (m_mode_switch || lost_mode) {
			swap_chain.SwitchMode(!lost_mode);
			m_mode_switch = false;
			return true;
		}

		// Update the rendering manager.
		m_rendering_manager->Update();

		return false;
	}
	
	[[nodiscard]]
	bool Engine::Impl::UpdateScripting() {
		// Calculate the elapsed time.
		const auto delta_time = m_timer.GetDeltaTime();
		
		// Perform the fixed delta time updates of the current scene.
		if (m_fixed_delta_time) {
			m_fixed_time_budget += delta_time;
			while (m_fixed_time_budget >= m_fixed_delta_time) {
				m_scene->ForEach< BehaviorScript >([this](BehaviorScript& script) {
					if (State::Active == script.GetState()) {
						script.FixedUpdate(*this);
					}
				});

				m_fixed_time_budget -= m_fixed_delta_time;
			}
		}
		else {
			m_scene->ForEach< BehaviorScript >([this](BehaviorScript& script) {
				if (State::Active == script.GetState()) {
					script.FixedUpdate(*this);
				}
			});
		}
		
		// Perform the non-fixed delta time updates of the current scene.
		m_scene->ForEach< BehaviorScript >([this, delta_time](BehaviorScript &script) {
			if (State::Active == script.GetState()
				&& !m_has_requested_scene) {

				script.Update(*this, delta_time);
			}
		});

		if (m_has_requested_scene) {
			ApplyRequestedScene();
			
			if (!m_scene) {
				PostQuitMessage(0);
				return true;
			}
		}

		return false;
	}

	[[nodiscard]]
	int Engine::Impl::Run(UniquePtr< Scene >&& scene, int nCmdShow) {
		// Show the main window.
		m_window->Show(nCmdShow);

		// Handle startup in fullscreen mode.
		auto& swap_chain = m_rendering_manager->GetSwapChain();
		swap_chain.SetInitialMode();

		RequestScene(std::move(scene));
		ApplyRequestedScene();
		// Check if the engine is finished.
		if (!m_scene) {
			return 0;
		}

		// Enter the message loop.
		MSG msg;
		SecureZeroMemory(&msg, sizeof(msg));
		while (WM_QUIT != msg.message) {
			
			// Retrieves messages for any window that belongs to the current 
			// thread without performing range filtering. Furthermore messages 
			// are removed after processing.
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				// Translates virtual-key messages into character messages.
				TranslateMessage(&msg);
				// Dispatches a message to a window procedure.
				DispatchMessage(&msg);
				continue;
			}

			// Check if the main window is deactive.
			if (m_deactive) {
				continue;
			}

			if (UpdateInput()) {
				continue;
			}

			if (UpdateRendering()) {
				continue;
			}

			if (UpdateScripting()) {
				continue;
			}

			m_rendering_manager->Render();
		}

		return static_cast< int >(msg.wParam);
	}

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	#pragma region

	Engine::Engine(const EngineSetup& setup,
				   rendering::DisplayConfiguration display_config) 
		: m_impl(MakeUnique< Impl >(setup, std::move(display_config))) {}

	Engine::Engine(Engine&& engine) noexcept = default;

	Engine::~Engine() = default;

	[[nodiscard]]
	int Engine::Run(UniquePtr< Scene >&& scene, int nCmdShow) {
		return m_impl->Run(std::move(scene), nCmdShow);
	}

	[[nodiscard]]
	input::Manager& Engine::GetInputManager() noexcept {
		return m_impl->GetInputManager();
	}

	[[nodiscard]]
	const input::Manager& Engine::GetInputManager() const noexcept {
		return m_impl->GetInputManager();
	}

	[[nodiscard]]
	rendering::Manager& Engine::GetRenderingManager() noexcept {
		return m_impl->GetRenderingManager();
	}

	[[nodiscard]]
	const rendering::Manager& Engine::GetRenderingManager() const noexcept {
		return m_impl->GetRenderingManager();
	}

	void Engine::RequestScene(UniquePtr< Scene >&& scene) noexcept {
		return m_impl->RequestScene(std::move(scene));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Method
	//-------------------------------------------------------------------------
	#pragma region

	UniquePtr< Engine > CreateEngine(const EngineSetup& setup) {
		#ifdef _DEBUG
		const int debug_flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		// Perform automatic leak checking at program exit through a call to 
		// _CrtDumpMemoryLeaks and generate an error report if the application 
		// failed to free all the memory it allocated.
		_CrtSetDbgFlag(debug_flags | _CRTDBG_LEAK_CHECK_DF);
		#endif

		AddUnhandledExceptionFilter();
		
		// Initialize a console.
		InitializeConsole();
		PrintConsoleHeader();

		// Enumerate the display configurations.
		auto configurator = MakeUnique< rendering::DisplayConfigurator >();
		const HRESULT result = configurator->Configure();
		if (FAILED(result)) {
			return;
		}

		// Obtain the selected display configuration.
		const auto config = configurator->GetDisplayConfiguration();
		Assert(config);

		// Construct an engine.
		return MakeUnique< Engine >(setup, *config);
	}

	#pragma endregion
}
