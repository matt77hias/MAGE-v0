//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "display\display_configurator.hpp"
#include "exception\exception.hpp"
#include "ImGui\imgui_window_message_listener.hpp"
#include "logging\dump.hpp"
#include "meta\targetver.hpp"
#include "meta\version.hpp"
#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// EngineMessageHandler
	//-------------------------------------------------------------------------
	#pragma region

	EngineMessageHandler::EngineMessageHandler() = default;

	EngineMessageHandler::EngineMessageHandler(
		const EngineMessageHandler& handler) = default;

	EngineMessageHandler::EngineMessageHandler(
		EngineMessageHandler&& handler) noexcept
		: WindowMessageHandler(std::move(handler)),
		m_on_active_change(std::move(handler.m_on_active_change)),
		m_on_mode_switch(std::move(handler.m_on_mode_switch)),
		m_on_print_screen(std::move(handler.m_on_print_screen)) {}

	EngineMessageHandler::~EngineMessageHandler() = default;

	EngineMessageHandler& EngineMessageHandler
		::operator=(const EngineMessageHandler& handler) = default;

	EngineMessageHandler& EngineMessageHandler
		::operator=(EngineMessageHandler&& handler) noexcept {

		WindowMessageHandler::operator=(std::move(handler));

		m_on_active_change = std::move(handler.m_on_active_change);
		m_on_mode_switch   = std::move(handler.m_on_mode_switch);
		m_on_print_screen  = std::move(handler.m_on_print_screen);
		return *this;
	}

	[[nodiscard]]
	const std::optional< LRESULT > EngineMessageHandler
		::HandleWindowMessage([[maybe_unused]] NotNull< HWND > window,
							  UINT message,
							  [[maybe_unused]] WPARAM wParam,
							  [[maybe_unused]] LPARAM lParam) {

		switch (message) {

		case WM_ACTIVATEAPP: {
			// Sent when a window belonging to a different application
			// than the active window is about to be activated.
			// The message is sent to the application whose window is being
			// activated and to the application whose window is being
			// deactivated.

			const auto deactive = static_cast< bool >(!wParam);
			m_on_active_change(deactive);
			return 0;
		}

		case WM_HOTKEY: {
			// Posted when the user presses a hot key registered by the
			// RegisterHotKey function.

			switch(wParam) {

			case static_cast< WPARAM >(HotKey::PrintScreen) :
			case static_cast< WPARAM >(HotKey::AltPrintScreen): {
				m_on_print_screen();
				return 0;
			}

			}

			break;
		}

		case WM_SYSKEYDOWN: {
			// Sent to the window with the keyboard focus when the user presses
			// the F10 key (which activates the menu bar) or holds down the ALT
			// key and then presses another key.

			switch (wParam) {

			case VK_RETURN: {
				m_on_mode_switch();
				return 0;
			}

			}

			break;
		}

		}

		return {};
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	#pragma region

	Engine::Engine(const EngineSetup& setup,
				   const rendering::DisplayConfiguration& display_config)
		: m_window(),
		m_message_handler(),
		m_input_manager(),
		m_rendering_manager(),
		m_scene(),
		m_requested_scene(),
		m_timer(),
		m_time(),
		m_fixed_delta_time(TimeIntervalSeconds::zero()),
		m_fixed_time_budget(TimeIntervalSeconds::zero()),
		m_deactive(false),
		m_mode_switch(false),
		m_has_requested_scene(false) {

		// Initialize the systems of this engine.
		InitializeSystems(setup, display_config);
	}

	Engine::Engine(Engine&& engine) noexcept = default;

	Engine::~Engine() {
		// Uninitialize the systems of this engine.
		UninitializeSystems();
	}

	void Engine::InitializeSystems(const EngineSetup& setup,
								   const rendering::DisplayConfiguration& display_config) {

		// Initialize the window.
		{
			auto window_desc
				= MakeShared< WindowDescriptor >(setup.GetApplicationInstance(),
												 L"MAGE");
			m_window = MakeUnique< Window >(std::move(window_desc),
											setup.GetApplicationName(),
											display_config.GetDisplayResolution());

			m_message_handler.m_on_active_change = [this](bool deactive) {
				m_deactive = deactive;

				if (m_deactive) {
					m_timer.Stop();
				}
				else {
					m_timer.Resume();
				}
			};

			m_message_handler.m_on_mode_switch   = [this]() {
				m_mode_switch = true;
			};

			m_message_handler.m_on_print_screen  = [this]() {
				auto& swap_chain = m_rendering_manager->GetSwapChain();
				const auto fname = L"screenshot-" + GetLocalSystemDateAndTimeAsString()
					             + L".png";
				swap_chain.TakeScreenShot(fname);
			};

			m_window->AddListener(
				NotNull< WindowMessageListener* >(&ImGuiWindowMessageListener::s_listener));
			m_window->AddHandler(
				NotNull< WindowMessageHandler* >(&m_message_handler));
		}

		const auto window = NotNull< HWND >(m_window->GetWindow());

		// Initialize the input system.
		m_input_manager = MakeUnique< input::Manager >(window);

		// Initialize the rendering system.
		m_rendering_manager = MakeUnique< rendering::Manager >(window, display_config);
		m_rendering_manager->BindPersistentState();

		// Initializes the COM library for use by the calling thread and sets
		// the thread's concurrency model to multithreaded concurrency.
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	}

	void Engine::UninitializeSystems() noexcept {
		m_window->RemoveAllListeners();
		m_window->RemoveAllHandlers();

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
			m_time = GameTime();
			m_fixed_time_budget = TimeIntervalSeconds::zero();
		}
	}

	[[nodiscard]]
	bool Engine::UpdateInput() {
		// Update the input manager.
		m_input_manager->Update();

		// Handle forced exit.
		if (m_input_manager->GetKeyboard().IsActivated(DIK_F1)) {
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
		// Perform the fixed delta time updates of the current scene.
		if (TimeIntervalSeconds::zero() != m_fixed_delta_time) {
			m_fixed_time_budget += m_time.GetWallClockDeltaTime();
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
		m_scene->ForEach< BehaviorScript >([this](BehaviorScript& script) {
			if (State::Active == script.GetState()
				&& !m_has_requested_scene) {

				script.Update(*this);
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
			if (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) {
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

			// Calculate the time.
			m_time = m_timer.GetTime();

			if (UpdateRendering()) {
				continue;
			}

			if (UpdateScripting()) {
				continue;
			}

			m_rendering_manager->Render(m_time);
		}

		return static_cast< int >(msg.wParam);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory
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
