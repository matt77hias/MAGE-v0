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
	GeneralConfiguration general_configuration;
	Engine *g_engine = NULL;

	//-------------------------------------------------------------------------
	// WindowProc for handling Windows messages.
	//-------------------------------------------------------------------------
	
	/**
	 The application-defined function that processes messages sent to the engine window. 
	 The WindowProc type defines a pointer to this callback function.

	 @param[in]		hwnd
					A handle to the window.
	 @param[in]		msg
					The message.
	 @param[in]		wparam
					Additional message information.
					The contents of this parameter depend on the value of @a msg.
	 @param[in]		lparam
					Additional message information.
					The contents of this parameter depend on the value of @a msg.
	 @return		The return value is the result of the message processing 
					and depends on the message sent.
	 */
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		switch (msg) {
		case WM_ACTIVATEAPP:
			// Sent when a window belonging to a different application 
			// than the active window is about to be activated. 
			// The message is sent to the application whose window is being activated 
			// and to the application whose window is being deactivated.

			g_engine->SetDeactiveFlag(!wparam);
			return 0;
		case WM_DESTROY:
			// Sent when a window is being destroyed. 
			// It is sent to the window procedure of the window 
			// being destroyed after the window is removed from the screen.

			// Indicate to the system that the window thread requests
			// to terminate (quit) with exit code 0.
			PostQuitMessage(0);
			return 0;
		default:
			// Calls the default window procedure to provide default processing 
			// for any window messages that an application does not process.
			// This function ensures that every message is processed.
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

	//-------------------------------------------------------------------------
	// Engine
	//-------------------------------------------------------------------------
	
	/**
	 Allocates a console to the engine for basic io and 
	 redirects stdin, stdout and stderr to the allocated console.

	 @return		@c true if a console is successfully attached.
					@c false otherwise.
	 */
	static bool AttachConsole() {
		// Allocate a console for basic io
		if (!AllocConsole()) {
			return false;
		}
		
		FILE *stream_in, *stream_out, *stream_err;
		// Redirect stdin, stdout and stderr to the allocated console
		// Reuse stdin to open the file "CONIN$"
		freopen_s(&stream_in, "CONIN$", "r", stdin);
		// Reuse stdout to open the file "CONOUT$"
		freopen_s(&stream_out, "CONOUT$", "w", stdout);
		// Reuse stderr to open the file "CONIN$
		freopen_s(&stream_err, "CONOUT$", "w", stderr);

		return true;
	}

	/**
	 Prints the header of the engine to the console.
	 */
	static void PrintConsoleHeader() {
		printf("MAGE version %s of %s at %s [Detected %d core(s)]\n",
			MAGE_VERSION_STRING, __DATE__, __TIME__, NumberOfSystemCores());
		printf("Copyright (c) 2016 Matthias Moulin.\n");
		fflush(stdout);
	}
	
	Engine::Engine(const EngineSetup *setup) {
		// Indicate that the engine is not yet loaded.
		m_loaded = false;

		// If no setup structure was passed in, create a default one.
		// Otehrwise, make a copy of the passed in structure.
		m_setup = (setup) ? new EngineSetup(setup) : new EngineSetup();

		// Store a pointer to the engine in a global variable for easy access.
		g_engine = this;

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
		wcex.hbrBackground = NULL;
		// Pointer to a null-terminated character string that specifies the resource name 
		// of the class menu, as the name appears in the resource file. 
		// If this member is NULL, windows belonging to this class have no default menu.
		wcex.lpszMenuName = NULL;
		// A pointer to a null-terminated string or is an atom.
		// If lpszClassName is a string, it specifies the window class name.
		wcex.lpszClassName = L"WindowClass";
		// A handle to a small icon that is associated with the window class.
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		// Registers a window class
		RegisterClassEx(&wcex);
		//-----------------------------------------------------------------------------

		// Initializes the COM library for use by the calling thread 
		// and sets the thread's concurrency model to multithreaded concurrency.
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		// Creates the window and retrieve a handle to it.
		// Note: Later the window will be created using a windowed/fullscreen flag.
		m_hwindow = CreateWindow(L"WindowClass", m_setup->m_name.c_str(), WS_OVERLAPPED, 0, 0, 800, 600, NULL, NULL, m_setup->m_hinstance, NULL);

		// Attach a console
		AttachConsole();
		PrintConsoleHeader();

		// Create different engine systems
		m_state_manager = new StateManager();
		m_script_manager = new ResourceManager< Script >();
		m_input = new Input(m_hwindow);

		if (m_setup->StateSetup) {
			// Sets up the states
			m_setup->StateSetup();
		}

		// Seed the random number generator with the current time.
		//srand(timeGetTime());

		// The engine is fully loaded and ready to go.
		m_loaded = true;
	}

	Engine::~Engine() {
		// Ensure the engine is loaded.
		if (m_loaded) {
			delete m_state_manager;
			delete m_script_manager;
			delete m_input;
		}

		// Uninitialise the COM.
		CoUninitialize();

		// Unregister the window class.
		UnregisterClass(L"WindowClass", m_setup->m_hinstance);

		// Clean up the tasks support.
		TasksCleanup();

		delete m_setup;
	}

	void Engine::Run() {
		// Ensure the engine is loaded.
		if (m_loaded) {
			// Activates the window and displays it in its current size and position.
			ShowWindow(m_hwindow, SW_NORMAL);

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
						m_state_manager->GetCurrentState()->RequestViewer(&viewer);
					}
					if (m_state_manager->Update(elapsed_time)) {
						continue;
					}
				}
			}
		}

		// Destroy the engine.
		delete g_engine;
	}
}