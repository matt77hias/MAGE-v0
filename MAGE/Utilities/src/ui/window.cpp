//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"
#include "platform\windows_utils.hpp"
#include "ui\window.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define IDI_APPLICATION_ICON  102

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// WindowMessageListener
	//-------------------------------------------------------------------------
	#pragma region

	WindowMessageListener::WindowMessageListener() noexcept = default;

	WindowMessageListener::WindowMessageListener(
		const WindowMessageListener& listener) noexcept = default;

	WindowMessageListener::WindowMessageListener(
		WindowMessageListener&& listener) noexcept = default;

	WindowMessageListener::~WindowMessageListener() = default;

	WindowMessageListener& WindowMessageListener
		::operator=(const WindowMessageListener& listener) noexcept = default;

	WindowMessageListener& WindowMessageListener
		::operator=(WindowMessageListener&& listener) noexcept = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowMessageHandler
	//-------------------------------------------------------------------------
	#pragma region

	WindowMessageHandler::WindowMessageHandler() noexcept = default;

	WindowMessageHandler::WindowMessageHandler(
		const WindowMessageHandler& handler) noexcept = default;

	WindowMessageHandler::WindowMessageHandler(
		WindowMessageHandler&& handler) noexcept = default;

	WindowMessageHandler::~WindowMessageHandler() = default;

	WindowMessageHandler& WindowMessageHandler
		::operator=(const WindowMessageHandler& handler) noexcept = default;

	WindowMessageHandler& WindowMessageHandler
		::operator=(WindowMessageHandler&& handler) noexcept = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowDescriptor
	//-------------------------------------------------------------------------
	#pragma region

	WindowDescriptor::WindowDescriptor(NotNull< HINSTANCE > instance,
									   std::wstring window_class_name,
									   U32 window_class_style)
		: m_instance(std::move(instance)),
		m_window_class_name(std::move(window_class_name)) {

		// Prepare and register the window class.
		WNDCLASSEX wcex    = {};
		wcex.cbSize        = sizeof(WNDCLASSEX);
		wcex.style         = window_class_style;
		wcex.lpfnWndProc   = Window::HandleWindowMessage;
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
		wcex.lpszClassName = m_window_class_name.c_str();

		// Register the window class.
		const ATOM result = RegisterClassEx(&wcex);
		ThrowIfFailed(0 != result, "Failed to register window class: {}.",
					  m_window_class_name);
	}

	WindowDescriptor::WindowDescriptor(WindowDescriptor&& desc) noexcept = default;

	WindowDescriptor::~WindowDescriptor() {
		// Unregister the window class.
		UnregisterClass(m_window_class_name.c_str(), m_instance);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Window
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	LRESULT CALLBACK Window::HandleWindowMessage(HWND window,
												 UINT message,
												 WPARAM wParam,
												 LPARAM lParam) {
		// Window dependent message handling.
		{
			const auto not_null_window = NotNull< HWND >(window);
			const auto caller = GetWindowCaller< Window >
				                (not_null_window, message, wParam, lParam);
			if (caller) {
				if (const auto result
					= caller->HandleWindowMessage(not_null_window, message,
												  wParam, lParam);
					bool(result)) {

					return *result;
				}

			}
		}

		// Window independent message handling.
		switch (message) {

		case WM_DESTROY: {
			// Sent when a window is being destroyed.
			// It is sent to the window procedure of the window
			// being destroyed after the window is removed from the screen.

			// Indicate to the system that the window thread requests
			// to terminate (quit) with exit code 0.
			PostQuitMessage(0);

			return 0;
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

			return 0;
		}

		default: {
			return DefWindowProc(window, message, wParam, lParam);
		}

		}
	}

	Window::Window(WindowDescriptorPtr window_desc,
				   std::wstring_view title_text,
				   const U32x2& resolution,
				   DWORD style)
		: m_window_desc(std::move(window_desc)),
		m_window(nullptr),
		m_listeners(),
		m_handlers() {

		Assert(m_window_desc);

		//Initialize a window.
		InitializeWindow(title_text, resolution, style);
	}

	Window::Window(Window&& window) noexcept = default;

	Window::~Window() = default;

	void Window::InitializeWindow(std::wstring_view title_text,
								  const U32x2& resolution,
								  DWORD style) {

		const RECT rectangle = {
			0,
			0,
			static_cast< LONG >(resolution[0]),
			static_cast< LONG >(resolution[1])
		};

		return InitializeWindow(title_text, rectangle, style);
	}

	void Window::InitializeWindow(std::wstring_view title_text,
								  const RECT& rectangle,
								  DWORD style) {

		// An explicit formatting string is provided to avoid clashes with the
		// string.
		wchar_t buffer_window_name[MAX_PATH];
		WriteTo(buffer_window_name, L"{}", m_window_desc->GetWindowClassName());
		wchar_t buffer_title_text[MAX_PATH];
		WriteTo(buffer_title_text, L"{}", title_text);

		// Calculate the required size of the window rectangle, based on the desired
		// client rectangle size. A client rectangle is the smallest rectangle that
		// completely encloses a client area. A window rectangle is the smallest
		// rectangle that completely encloses the window, which includes the client
		// area and the nonclient area.
		// 1. A pointer to a RECT structure.
		// 2. The window style of the window.
		// 3. Flag indicating whether the window has a menu.
		auto adjusted_rectangle = rectangle;
		AdjustWindowRect(&adjusted_rectangle, style, FALSE);

		// Creates the window and retrieve a handle to it.
		m_window = CreateWindow(buffer_window_name,
								buffer_title_text,
			                    style,
			                    CW_USEDEFAULT,
			                    CW_USEDEFAULT,
			                    adjusted_rectangle.right  - adjusted_rectangle.left,
			                    adjusted_rectangle.bottom - adjusted_rectangle.top,
			                    nullptr,
			                    nullptr,
								GetInstance(),
			                    this);
		ThrowIfFailed((nullptr != m_window), "Window creation failed.");

		// Register a print screen hot key, because pressing down VK_SNAPSHOT
		// does not result in a WM_KEYDOWN (or WM_SYSKEYDOWN).
		{
			const BOOL result = RegisterHotKey(m_window,
				                               static_cast< int >(HotKey::AltPrintScreen),
				                               MOD_ALT | MOD_NOREPEAT,
											   VK_SNAPSHOT);
			if (FALSE == result) {
				Warning("Registering Alt+PrintScreen hot key failed.");
			}
		}
		{
			const BOOL result = RegisterHotKey(m_window,
											   static_cast< int >(HotKey::PrintScreen),
											   MOD_NOREPEAT,
											   VK_SNAPSHOT);
			if (FALSE == result) {
				Warning("Registering PrintScreen hot key failed.");
			}
		}
	}

	void Window::Show(int nCmdShow) {
		ShowWindow(m_window, nCmdShow);

		const BOOL result = UpdateWindow(m_window);
		ThrowIfFailed(result, "Failed to update the window.");
	}

	[[nodiscard]]
	const std::wstring Window::GetTitleText() const noexcept {
		wchar_t text[1024];
		const int result = GetWindowText(m_window,
										 text,
										 static_cast< int >(std::size(text)));

		return (0 == result) ? L"" : text;
	}

	void Window::SetTitleText(NotNull< const_wzstring > title_text) {
		const BOOL result = SetWindowText(m_window, title_text);
		ThrowIfFailed(result, "Failed to set the title window text.");
	}

	void Window::AddListener(WindowMessageListenerPtr listener) {
		m_listeners.push_back(listener);
	}

	void Window::RemoveListener(WindowMessageListenerPtr listener) {
		using std::begin;
		using std::end;

		m_listeners.erase(std::remove(begin(m_listeners), end(m_listeners),
									  listener),
						  end(m_listeners));
	}

	void Window::RemoveAllListeners() noexcept {
		m_listeners.clear();
	}

	void Window::AddHandler(WindowMessageHandlerPtr handler) {
		m_handlers.push_back(handler);
	}

	void Window::RemoveHandler(WindowMessageHandlerPtr handler) {
		using std::begin;
		using std::end;

		m_handlers.erase(std::remove(begin(m_handlers), end(m_handlers),
									 handler),
						 end(m_handlers));
	}

	void Window::RemoveAllHandlers() noexcept {
		m_handlers.clear();
	}

	[[nodiscard]]
	const std::optional< LRESULT > Window
		::HandleWindowMessage(NotNull< HWND > window, UINT message,
							  WPARAM wParam, LPARAM lParam) const {

		// Notify the window message listeners.
		for (auto listener : m_listeners) {
			listener->ProcessWindowMessage(window, message, wParam, lParam);
		}

		// Notify the window message handlers.
		for (auto handler : m_handlers) {
			if (const auto result
				= handler->HandleWindowMessage(window, message, wParam, lParam);
				bool(result)) {

				return result;
			}
		}

		return {};
	}

	#pragma endregion
}