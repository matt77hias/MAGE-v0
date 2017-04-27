//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "ui\main_window_settings.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_MAIN_WINDOW_CLASS_NAME L"MainWindowClass"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage{
	
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
	LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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
		case WM_MENUCHAR: {
			// Sent when a menu is active and the user presses a key 
			// that does not correspond to any mnemonic or accelerator key. 

			// Prevent the window to beep on ALT + ENTER for switching from fullscreen to windowed mode.
			return MNC_CLOSE << 16; // high-order word of return value.
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
		case WM_SYSKEYDOWN: {
			// Sent to the window with the keyboard focus when the user presses the F10 key 
			// (which activates the menu bar) or holds down the ALT key and then presses another key.

			// Check whether the user wants to switch between windowed and full screen mode.
			if (wParam == VK_RETURN) {
				g_engine->SetModeSwitchFlag(true);
				break;
			}

			// Calls the default window procedure to provide default processing 
			// for any window messages that an application does not process.
			// This function ensures that every message is processed.
			return DefWindowProc(hWnd, msg, wParam, lParam);
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
	// MainWindow
	//-------------------------------------------------------------------------

	MainWindow::MainWindow(HINSTANCE hinstance, const wstring &name, LONG width, LONG height) 
		: m_hinstance(hinstance), m_hwindow(nullptr), m_name(name) {

		Assert(hinstance);

		//Initialize a window.
		InitializeWindow(width, height);
	}

	MainWindow::~MainWindow() {
		// Uninitialize the window.
		UninitializeWindow();
	}

	void MainWindow::InitializeWindow(LONG width, LONG height) {
		const RECT rectangle = { 0, 0, width, height };
		return InitializeWindow(rectangle);
	}

	void MainWindow::InitializeWindow(RECT rectangle) {

		// Prepare and register the window class.
		//-----------------------------------------------------------------------------
		// Structure ontaining window class information. 
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(wcex));
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
		wcex.lpfnWndProc = MainWindowProc;
		// The number of extra bytes to allocate following the window-class structure.
		wcex.cbClsExtra = 0;
		// The number of extra bytes to allocate following the window instance.
		wcex.cbWndExtra = 0;
		// A handle to the instance that contains the window procedure for the class.
		wcex.hInstance = m_hinstance;
		// A handle to the class icon. This member must be a handle to an icon resource.
		wcex.hIcon   = (HICON)LoadImage(m_hinstance, MAKEINTRESOURCE(IDI_APPLICATION_ICON), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
		// A handle to a small icon that is associated with the window class.
		wcex.hIconSm = (HICON)LoadImage(m_hinstance, MAKEINTRESOURCE(IDI_APPLICATION_ICON), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
		// A handle to the class cursor. This member must be a handle to a cursor resource.
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		// A handle to the class background brush. This member can be a handle to
		// the brush to be used for painting the background, or it can be a color value.
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		// Pointer to a null-terminated character string that specifies the resource name 
		// of the class menu, as the name appears in the resource file. 
		// If this member is nullptr, windows belonging to this class have no default menu.
		wcex.lpszMenuName = nullptr;
		// A pointer to a null-terminated string or is an atom.
		// If lpszClassName is a string, it specifies the window class name.
		wcex.lpszClassName = MAGE_MAIN_WINDOW_CLASS_NAME;

		// Register a window class
		if (!RegisterClassEx(&wcex)) {
			throw FormattedException("Registering main window's class failed.");
		}
		//-----------------------------------------------------------------------------

		// Calculate the required size of the window rectangle, based on the desired client rectangle size.
		// A client rectangle is the smallest rectangle that completely encloses a client area. 
		// A window rectangle is the smallest rectangle that completely encloses the window, which includes the client area and the nonclient area.
		// 1. A pointer to a RECT structure.
		// 2. The window style of the window.
		// 3. Flag indicating whether the window has a menu.
		const DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		AdjustWindowRect(&rectangle, style, FALSE);

		// Creates the window and retrieve a handle to it.
		m_hwindow = CreateWindow(MAGE_MAIN_WINDOW_CLASS_NAME, m_name.c_str(), style, CW_USEDEFAULT, CW_USEDEFAULT,
			rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, nullptr, nullptr, m_hinstance, nullptr);

		if (!m_hwindow) {
			throw FormattedException("Main window creation failed.");
		}
	}

	void MainWindow::UninitializeWindow() {
		// Unregister the window class.
		UnregisterClass(MAGE_MAIN_WINDOW_CLASS_NAME, m_hinstance);
	}

	bool MainWindow::Show(int nCmdShow) {
		return ShowWindow(GetHandle(), nCmdShow) != 0;
	}
}