//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Globals
	//-------------------------------------------------------------------------
	LoggingConfiguration g_logging_configuration;
	Engine *g_engine = NULL;

	//-------------------------------------------------------------------------
	// WindowProc for handling Windows messages.
	//-------------------------------------------------------------------------
	
	/**
	 The application-defined function that processes messages sent to the engine window. 
	 The WindowProc type defines a pointer to this callback function.

	 @param[in]		hWnd
					A handle to the window.
	 @param[in]		msg
					The message.
	 @param[in]		wParam
					Additional message information.
					The contents of this parameter depend on the value of @a msg.
	 @param[in]		lParam
					Additional message information.
					The contents of this parameter depend on the value of @a msg.
	 @return		The return value is the result of the message processing
					and depends on the message sent.
	 */
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_ACTIVATEAPP: {
			// Sent when a window belonging to a different application 
			// than the active window is about to be activated. 
			// The message is sent to the application whose window is being activated 
			// and to the application whose window is being deactivated.

			g_engine->SetDeactiveFlag(!wParam);
			break;
		}
		case WM_DESTROY: {
			// Sent when a window is being destroyed. 
			// It is sent to the window procedure of the window 
			// being destroyed after the window is removed from the screen.

			// Indicate to the system that the window thread requests
			// to terminate (quit) with exit code 0.
			PostQuitMessage(0);
			break;
		}
		case WM_PAINT: {
			// Sent when the system or another application makes a request 
			// to paint a portion of an application's window.

			// Prepare the specified window for painting and 
			// fill a PAINTSTRUCT with information about the painting and
			// return a handle to to a display device context for the specified window.
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			// Mark the end of painting in the specified window.
			EndPaint(hWnd, &ps);
			break;
		}
		default: {
			// Calls the default window procedure to provide default processing 
			// for any window messages that an application does not process.
			// This function ensures that every message is processed.
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		}

		return 0;
	}

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	
	Engine::Engine(const EngineSetup *setup) : m_loaded(false), 
		m_renderer(NULL), m_state_manager(NULL), m_script_manager(NULL), m_input(NULL) {

		// Store a pointer to the engine in a global variable for easy access.
		if (g_engine) {
			delete g_engine;
		}
		g_engine = this;

		// If no setup structure was passed in, create a default one.
		// Otehrwise, make a copy of the passed in structure.
		m_setup = (setup) ? new EngineSetup(setup) : new EngineSetup();

		//Initialize a window.
		const HRESULT result_window = InitializeWindow();
		if (FAILED(result_window)) {
			return;
		}

		// Attach a console.
		const HRESULT result_console = AttachConsole();
		if (FAILED(result_console)) {
			return;
		}
		PrintConsoleHeader();

		// Initializes the COM library for use by the calling thread 
		// and sets the thread's concurrency model to multithreaded concurrency.
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		// Initialize the different engine systems.
		const HRESULT result_system = InitializeSystems();
		if (FAILED(result_system)) {
			Severe("Failed to initialize systems.");
		}

		// The engine is fully loaded and ready to go.
		m_loaded = true;
	}

	Engine::~Engine() {

		if (m_loaded) {
			// Unitialize the different systems.
			UninitializeSystems();
			// Uninitialise the COM.
			CoUninitialize();
		}
		// Unintialize the window.
		UninitializeWindow();

		// Clean up the tasks support.
		TasksCleanup();

		SAFE_DELETE(m_setup);
	}

	HRESULT Engine::AttachConsole() {
		// Allocate a console for basic io
		if (!AllocConsole()) {
			return E_FAIL;
		}

		FILE *stream_in, *stream_out, *stream_err;
		// Redirect stdin, stdout and stderr to the allocated console
		// Reuse stdin to open the file "CONIN$"
		freopen_s(&stream_in, "CONIN$", "r", stdin);
		// Reuse stdout to open the file "CONOUT$"
		freopen_s(&stream_out, "CONOUT$", "w", stdout);
		// Reuse stderr to open the file "CONIN$
		freopen_s(&stream_err, "CONOUT$", "w", stderr);

		return S_OK;
	}

	HRESULT Engine::InitializeWindow() {

		// Prepare and register the window class.
		//-----------------------------------------------------------------------------
		// Structure ontaining window class information. 
		WNDCLASSEX wcex;
		// The size, in bytes, of this structure.
		wcex.cbSize = sizeof(WNDCLASSEX);
		// The class style(s)
		// CS_CLASSDC:	Allocates one device context to be shared by all windows in the class. 
		//				Because window classes are process specific, it is possible for multiple 
		//				threads of an application to create a window of the same class. 
		//				It is also possible for the threads to attempt to use the device context simultaneously. 
		//				When this happens, the system allows only one thread to successfully finish its drawing operation.
		wcex.style = CS_CLASSDC;
		// A pointer to the window procedure.
		wcex.lpfnWndProc = WindowProc;
		// The number of extra bytes to allocate following the window-class structure.
		wcex.cbClsExtra = 0;
		// The number of extra bytes to allocate following the window instance.
		wcex.cbWndExtra = 0;
		//A handle to the instance that contains the window procedure for the class.
		wcex.hInstance = m_setup->m_hinstance;
		// A handle to the class icon. This member must be a handle to an icon resource.
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		// A handle to the class cursor. This member must be a handle to a cursor resource.
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		// A handle to the class background brush. This member can be a handle to
		// the brush to be used for painting the background, or it can be a color value.
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		// Pointer to a null-terminated character string that specifies the resource name 
		// of the class menu, as the name appears in the resource file. 
		// If this member is NULL, windows belonging to this class have no default menu.
		wcex.lpszMenuName = NULL;
		// A pointer to a null-terminated string or is an atom.
		// If lpszClassName is a string, it specifies the window class name.
		wcex.lpszClassName = L"WindowClass";
		// A handle to a small icon that is associated with the window class.
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		// Register a window class
		if (!RegisterClassEx(&wcex)) {
			return E_FAIL;
		}
		//-----------------------------------------------------------------------------

		RECT rectangle = { 0, 0, 800, 600 };
		// Calculate the required size of the window rectangle, based on the desired client-rectangle size.
		// A client rectangle is the smallest rectangle that completely encloses a client area. 
		// A window rectangle is the smallest rectangle that completely encloses the window, which includes the client area and the nonclient area.
		// 1. A pointer to a RECT structure.
		// 2. The window style of the window.
		// 3. Flag indicating whether the window has a menu.
		AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, FALSE);

		if (g_device_enumeration) {
			delete g_device_enumeration;
		}
		g_device_enumeration = new DeviceEnumeration();
		if (g_device_enumeration->Enumerate() != IDOK) {
			return E_FAIL;
		}

		// Creates the window and retrieve a handle to it.
		// WS_OVERLAPPED:	The window is an overlapped window. An overlapped window has a title bar and a border.
		// WS_CAPTION:		The window has a title bar(includes the WS_BORDER style).
		// WS_BORDER:		The window has a thin-line border.
		// WS_SYSMENU:		The window has a window menu on its title bar.
		// WS_MINIMIZEBOX:	The window has a minimize button.
		m_hwindow = CreateWindow(L"WindowClass", m_setup->m_name.c_str(), g_device_enumeration->IsWindowed() ? WS_OVERLAPPED : WS_POPUP,
			CW_USEDEFAULT, CW_USEDEFAULT, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, NULL, NULL, m_setup->m_hinstance, NULL);

		if (!m_hwindow) {
			return E_FAIL;
		}

		return S_OK;
	}

	HRESULT Engine::UninitializeWindow() {
		// Unregister the window class.
		UnregisterClass(L"WindowClass", m_setup->m_hinstance);
		return S_OK;
	}

	HRESULT Engine::InitializeSystems() {
		// Create different engine systems
		m_renderer			= new Renderer();
		m_state_manager		= new StateManager();
		m_script_manager	= new ResourceManager< VariableScript >();
		m_input				= new Input(m_hwindow);

		if (m_setup->StateSetup) {
			// Sets up the states
			m_setup->StateSetup();
		}

		return S_OK;
	}

	HRESULT Engine::UninitializeSystems() {
		SAFE_DELETE(m_renderer);
		SAFE_DELETE(m_state_manager);
		SAFE_DELETE(m_script_manager);
		SAFE_DELETE(m_input);
		return S_OK;
	}

	void Engine::Run(int nCmdShow) {
		// Ensure the engine is loaded.
		if (!m_loaded) {
			return;
		}

		// Set the specified window's show state.
		ShowWindow(m_hwindow, nCmdShow);

		// Used to retrieve details about the viewer from the application.
		ViewerSetup viewer;

		Timer timer;
		timer.Start();

		// Enter the message loop.
		MSG msg;
		SecureZeroMemory(&msg, sizeof(MSG));
		while (msg.message != WM_QUIT) {
			// Retrieves messages for any window that belongs to the current thread
			// without performing range filtering. Furthermore messages are removed
			// after processing.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				// Translates virtual-key messages into character messages.
				TranslateMessage(&msg);
				// Dispatches a message to a window procedure.
				DispatchMessage(&msg);
			}
			else if (!m_deactive) {
				// Calculate the elapsed time.
				const double elapsed_time = timer.Time();
				timer.Restart();

				// Update the input object, reading the keyboard and mouse.
				m_input->Update();
				// Check whether the user wants to make a forced exit.
				if (m_input->GetKeyPress(DIK_F1)) {
					PostQuitMessage(0);
				}

				// Request the viewer from the current state (if there is one).
				if (m_state_manager->GetCurrentState()) {
					m_state_manager->GetCurrentState()->RequestViewSetup(&viewer);
				}
				if (m_state_manager->Update(elapsed_time)) {
					continue;
				}
			}
		}
	}
}