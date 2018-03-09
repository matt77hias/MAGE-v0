//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "display\display_configurator.hpp"
#include "exception\exception.hpp"
#include "logging\dump.hpp"
#include "logging\error.hpp"
#include "logging\logging.hpp"
#include "meta\targetver.hpp"
#include "meta\version.hpp"
#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Engine::Engine(const EngineSetup& setup, 
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

	Engine::Engine(Engine&& engine) noexcept = default;
	
	Engine::~Engine() {
		// Uninitialize the systems of this engine.
		UninitializeSystems();
	}

	void Engine::InitializeSystems(const EngineSetup& setup, 
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

	void Engine::UninitializeSystems() noexcept {
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

	void Engine::OnActiveChange(bool deactive) noexcept {
		m_deactive = deactive;
		
		if (m_deactive) {
			m_timer.Stop();
		}
		else {
			m_timer.Resume();
		}
	}

	void Engine::OnModeSwitch() noexcept {
		m_mode_switch = true;
	}

	void Engine::RequestScene(UniquePtr< Scene >&& scene) noexcept {
		m_requested_scene     = std::move(scene);
		m_has_requested_scene = true;
	}

	void Engine::ApplyRequestedScene() {
		if (m_scene) {
			m_scene->Uninitialize(*this);
		}

		m_scene               = std::move(m_requested_scene);
		m_requested_scene     = nullptr;
		m_has_requested_scene = false;

		if (m_scene) {
			m_scene->Initialize(*this);

			m_timer.Restart();
			m_fixed_time_budget = 0.0;
		}
	}

	[[nodiscard]]
	bool Engine::UpdateInput() {
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
	bool Engine::UpdateRendering() {
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
	bool Engine::UpdateScripting() {
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
	int Engine::Run(UniquePtr< Scene >&& scene, int nCmdShow) {
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
			return nullptr;
		}

		// Obtain the selected display configuration.
		const auto config = configurator->GetDisplayConfiguration();
		Assert(config);

		// Construct an engine.
		return MakeUnique< Engine >(setup, *config);
	}

	#pragma endregion
}
