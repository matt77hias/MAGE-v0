//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "core\version.hpp"
#include "rendering\display_configurator.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"
#include "logging\logging.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	
	Engine *Engine::s_engine = nullptr;

	Engine::Engine(const EngineSetup &setup)
		: Loadable(), 
		m_resource_manager(),
		m_main_window(), m_deactive(false),
		m_rendering_manager(), m_mode_switch(false),
		m_input_manager(), 
		m_scene_manager(),
		m_timer(MakeUnique< Timer >()), m_fixed_delta_time(0.0f),
		m_engine_stats(MakeUnique< EngineStatistics >()) {

		s_engine = this;

		// Initialize the systems of this engine.
		InitializeSystems(setup);
	}

	Engine::Engine(Engine &&engine) = default;

	Engine::~Engine() {

		// Uninitialize the systems of this engine.
		UninitializeSystems();

		s_engine = nullptr;
	}

	void Engine::InitializeSystems(const EngineSetup &setup) {

		// Initialize a console.
		InitializeConsole();
		PrintConsoleHeader();

		// Enumerate the devices.
		UniquePtr< DisplayConfigurator > display_configurator(
			MakeUnique< DisplayConfigurator >());
		const HRESULT result_configure = display_configurator->Configure();
		if (FAILED(result_configure)) {
			Error("Display configuration failed: %ld", result_configure);
			return;
		}

		const DisplayConfiguration *display_configuration 
			= display_configurator->GetDisplayConfiguration();
		
		// Initialize the resource system.
		m_resource_manager    = MakeUnique< ResourceManager >();
		// Initialize the window system.
		const U32 width  = display_configuration->GetDisplayWidth();
		const U32 height = display_configuration->GetDisplayHeight();
		m_main_window         = MakeUnique< MainWindow >(
									setup.GetApplicationHinstance(), 
									setup.GetApplicationName(), 
									width, height);
		// Initialize the rendering system.
		m_rendering_manager   = MakeUnique< RenderingManager >(
									m_main_window->GetHandle(), 
									display_configuration);
		m_rendering_manager->BindPersistentState();
		// Initialize the input system.
		m_input_manager       = MakeUnique< InputManager >(
									m_main_window->GetHandle());
		// Initialize the scene system.
		m_scene_manager       = MakeUnique< SceneManager >();

		// Initializes the COM library for use by the calling thread 
		// and sets the thread's concurrency model to multithreaded concurrency.
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);

		SetLoaded();
	}

	void Engine::UninitializeSystems() noexcept {
		SetLoaded(false);
		
		// Uninitialize the COM.
		CoUninitialize();

		// Uninitialize the scene system.
		m_scene_manager.reset();
		// Uninitialize the input system.
		m_input_manager.reset();
		// Uninitialize the rendering system.
		m_rendering_manager.reset();
		// Uninitialize the window system.
		m_main_window.reset();
		// Uninitialize the resource system.
		m_resource_manager.reset();
	}

	void Engine::OnActiveChange(bool deactive) noexcept {
		m_deactive = deactive;
		
		if (m_deactive) {
			m_timer->Stop();
		}
		else {
			m_timer->Resume();
		}
	}

	void Engine::OnSceneChange() noexcept {
		m_timer->Restart();
	}
	
	int Engine::Run(UniquePtr< Scene > &&scene, int nCmdShow) {
		
		// Check if this engine is loaded.
		if (!IsLoaded()) {
			Error("Game loop can not start because the engine is not loaded.");
			return 0;
		}
		
		// Pass the given scene to the scene manager.
		m_scene_manager->SetScene(std::move(scene));
		// Check if the scene manager is finished.
		if (m_scene_manager->IsFinished()) {
			return 0;
		}

		// Show the main window.
		m_main_window->Show(nCmdShow);
		
		// Handle startup in fullscreen mode.
		SwapChain * const swap_chain = m_rendering_manager->GetSwapChain();
		swap_chain->SetInitialMode();

		// Restart the timer.
		m_timer->Restart();
		F64 fixed_time_budget = 0.0f;

		// Enter the message loop.
		MSG msg;
		SecureZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {
			
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

			// Update the input manager.
			m_input_manager->Update();
			// Handle forced exit.
			if (m_input_manager->GetKeyboard()->GetKeyPress(DIK_F1)) {
				PostQuitMessage(0);
				continue;
			}

			// Handle switch between full screen and windowed mode.
			const bool lost_mode = swap_chain->LostMode();
			if (m_mode_switch || lost_mode) {
				swap_chain->SwitchMode(!lost_mode);
				m_mode_switch = false;
				continue;
			}

			// Calculate the elapsed time.
			const F64 delta_time = m_timer->GetDeltaTime();

			// Perform the fixed delta time updates of the current scene.
			if (m_fixed_delta_time) {
				fixed_time_budget += delta_time;
				while (fixed_time_budget >= m_fixed_delta_time) {
					m_scene_manager->FixedUpdate();
					fixed_time_budget -= m_fixed_delta_time;
				}
			}
			else {
				m_scene_manager->FixedUpdate();
			}

			// Perform the non-fixed delta time updates of the current scene.
			m_scene_manager->Update(delta_time);
			if (m_scene_manager->IsFinished()) {
				PostQuitMessage(0);
				continue;
			}
				
			// Render the current scene.
			m_engine_stats->PrepareRendering();
			m_rendering_manager->BeginFrame();
			m_scene_manager->Render();
			m_rendering_manager->EndFrame();
		}

		return static_cast< int >(msg.wParam);
	}
}
