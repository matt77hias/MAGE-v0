//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "ui\main_window_settings.hpp"
#include "imgui\imgui_impl_dx11.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

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
namespace mage {

	MainWindow *MainWindow::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetMainWindow();
	}

	[[nodiscard]] LRESULT CALLBACK MainWindow
		::MainWindowProc(HWND window, 
			             UINT message, 
			             WPARAM wParam, 
			             LPARAM lParam) noexcept {
		
		ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);

		switch (message) {
		
		case WM_ACTIVATEAPP: {
			// Sent when a window belonging to a different application 
			// than the active window is about to be activated. 
			// The message is sent to the application whose window is being 
			// activated and to the application whose window is being 
			// deactivated.

			const bool deactive = static_cast< bool >(!wParam);
			Engine::Get()->OnActiveChange(deactive);
			
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
		
		case WM_HOTKEY: {
			// Posted when the user presses a hot key registered by the 
			// RegisterHotKey function.

			switch(wParam) {

			case static_cast< int >(HotKey::PrintScreen) :
			case static_cast< int >(HotKey::AltPrintScreen): {
				SwapChain::Get()->TakeScreenShot();
				[[fallthrough]];
			}

			default: {
				return DefWindowProc(window, message, wParam, lParam);
			}

			}
		}

		case WM_MENUCHAR: {
			// Sent when a menu is active and the user presses a key 
			// that does not correspond to any mnemonic or accelerator key. 

			// Prevent the window to beep on ALT + ENTER for switching from 
			// fullscreen to windowed mode.
			return MAKELRESULT(0, MNC_CLOSE); // MNC_CLOSE << 16
		}

		case WM_PAINT: {
			// Sent when the system or another application makes a request 
			// to paint a portion of an application's window.

			// Prepare the specified window for painting and 
			// fill a PAINTSTRUCT with information about the painting and
			// return a handle to to a display device context for the specified 
			// window.
			PAINTSTRUCT ps;
			BeginPaint(window, &ps);
			// Mark the end of painting in the specified window.
			EndPaint(window, &ps);
			
			break;
		}
		
		case WM_SYSKEYDOWN: {
			// Sent to the window with the keyboard focus when the user presses 
			// the F10 key (which activates the menu bar) or holds down the ALT 
			// key and then presses another key.

			switch (wParam) {

			case VK_RETURN: {
				Engine::Get()->OnModeSwitch();
				break;
			}

			default: {
				return DefWindowProc(window, message, wParam, lParam);
			}

			}
		}

		default: {
			return DefWindowProc(window, message, wParam, lParam);
		}
		}

		return 0;
	}

	MainWindow::MainWindow(HINSTANCE instance, 
		                   const wstring &title_text, 
		                   U32 width, 
		                   U32 height)
		: m_instance(instance), m_window(nullptr) {

		Assert(m_instance);

		//Initialize a window.
		InitializeWindow(title_text, width, height);
	}

	MainWindow::MainWindow(MainWindow &&main_window) noexcept = default;

	MainWindow::~MainWindow() {
		// Uninitialize the window.
		UninitializeWindow();
	}

	const wstring MainWindow::GetTitleText() const noexcept {
		wchar_t text[1024];
		const int result = GetWindowText(m_window, 
			                             text, 
			                             static_cast< int >(std::size(text)));
		
		return result ? text : L"";
	}

	void MainWindow::SetTitleText(const wstring &title_text) {
		SetTitleText(title_text.c_str());
	}

	void MainWindow::SetTitleText(const wchar_t *title_text) {
		Assert(title_text);
		
		const BOOL result = SetWindowText(m_window, title_text);
		ThrowIfFailed(result, "Failed to set the window text.");
	}

	void MainWindow::InitializeWindow(const wstring &title_text, 
		                              U32 width, 
		                              U32 height) {
		
		const RECT rectangle = { 
			0, 
			0, 
			static_cast< LONG >(width), 
			static_cast< LONG >(height) 
		};
		
		return InitializeWindow(title_text, rectangle);
	}

	void MainWindow::InitializeWindow(const wstring &title_text, 
		                              const RECT &rectangle) {

		// Prepare and register the window class.
		//---------------------------------------------------------------------
		// Structure ontaining window class information. 
		WNDCLASSEX wcex    = {};
		wcex.cbSize        = sizeof(WNDCLASSEX);
		// The class style(s)
		// CS_CLASSDC:	Allocates one device context to be shared by all 
		//              windows in the class. Because window classes are process 
		//              specific, it is possible for multiple threads of an 
		//              application to create a window of the same class. It is 
		//              also possible for the threads to attempt to use the 
		//              device context simultaneously. When this happens, the 
		//              system allows only one thread to successfully finish its 
		//              drawing operation.
		wcex.style         = CS_CLASSDC;
		wcex.lpfnWndProc   = MainWindowProc;
		wcex.hInstance     = m_instance;
		wcex.hIcon         = (HICON)LoadImage(m_instance, 
			                                  MAKEINTRESOURCE(IDI_APPLICATION_ICON), 
			                                  IMAGE_ICON, 
			                                  GetSystemMetrics(SM_CXICON), 
			                                  GetSystemMetrics(SM_CYICON), 
			                                  0);
		wcex.hIconSm       = (HICON)LoadImage(m_instance, 
			                                  MAKEINTRESOURCE(IDI_APPLICATION_ICON), 
			                                  IMAGE_ICON, 
			                                  GetSystemMetrics(SM_CXSMICON), 
			                                  GetSystemMetrics(SM_CYSMICON), 
			                                  0);
		wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = nullptr;
		wcex.lpszClassName = MAGE_MAIN_WINDOW_CLASS_NAME;

		// Register a window class.
		{
			const ATOM result = RegisterClassEx(&wcex);
			ThrowIfFailed(0 != result, "Registering main window's class failed.");
		}

		//-----------------------------------------------------------------------------

		// Calculate the required size of the window rectangle, based on the desired 
		// client rectangle size. A client rectangle is the smallest rectangle that 
		// completely encloses a client area. A window rectangle is the smallest 
		// rectangle that completely encloses the window, which includes the client 
		// area and the nonclient area.
		// 1. A pointer to a RECT structure.
		// 2. The window style of the window.
		// 3. Flag indicating whether the window has a menu.
		const DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		RECT adjusted_rectangle = rectangle;
		AdjustWindowRect(&adjusted_rectangle, style, FALSE);

		// Creates the window and retrieve a handle to it.
		m_window = CreateWindow(MAGE_MAIN_WINDOW_CLASS_NAME, 
			                    title_text.c_str(), 
			                    style, 
			                    CW_USEDEFAULT, 
			                    CW_USEDEFAULT, 
			                    adjusted_rectangle.right  - adjusted_rectangle.left, 
			                    adjusted_rectangle.bottom - adjusted_rectangle.top, 
			                    nullptr, 
			                    nullptr, 
			                    m_instance, 
			                    nullptr);
		ThrowIfFailed((nullptr != m_window), "Main window creation failed.");

		// Register a print screen hot key, because pressing down VK_SNAPSHOT 
		// does not result in a WM_KEYDOWN (or WM_SYSKEYDOWN).
		{
			const BOOL result = RegisterHotKey(m_window,
				                               static_cast< int >(HotKey::AltPrintScreen), 
				                               MOD_ALT | MOD_NOREPEAT, 
				                               VK_SNAPSHOT);
			ThrowIfFailed(result, "Registering hot key failed.");
		}
		{
			const BOOL result = RegisterHotKey(m_window,
				                              static_cast< int >(HotKey::PrintScreen),
				                              MOD_NOREPEAT, 
				                              VK_SNAPSHOT);
			ThrowIfFailed(result, "Registering hot key failed.");
		}
	}

	void MainWindow::UninitializeWindow() noexcept {
		// Unregister the window class.
		UnregisterClass(MAGE_MAIN_WINDOW_CLASS_NAME, m_instance);
	}

	void MainWindow::Show(int nCmdShow) {
		ShowWindow(m_window, nCmdShow);
		
		const BOOL result = UpdateWindow(m_window);
		ThrowIfFailed(result, "Failed to update the window.");
	}
}
