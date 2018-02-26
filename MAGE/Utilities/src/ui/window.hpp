//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// HotKey
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different hot keys registered by windows.

	 This contains: 
	 @c Unused, 
	 @c PrintScreen, and 
	 @c AltPrintScreen.
	 */
	enum class HotKey : U8 {
		Unused         = 0,
		PrintScreen    = 1,
		AltPrintScreen = 2,
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowListener
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of window listeners.
	 */
	class WindowListener {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a window listener.
		 */
		WindowListener() noexcept;

		/**
		 Constructs a window listener from the given window listener.

		 @param[in]		listener
						A reference to the window listener to copy.
		 */
		WindowListener(const WindowListener &listener) noexcept;

		/**
		 Constructs a window listener by moving the given window listener.

		 @param[in]		listener
						A reference to the window listener to move.
		 */
		WindowListener(WindowListener &&listener) noexcept;

		/**
		 Destructs this window listener.
		 */
		virtual ~WindowListener();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given window listener to this window listener.

		 @param[in]		listener
						A reference to the window listener to copy.
		 @return		A reference to the copy of the given window listener 
						(i.e. this window listener).
		 */
		WindowListener &operator=(const WindowListener &listener) noexcept;

		/**
		 Moves the given window listener to this window listener.

		 @param[in]		listener
						A reference to the window listener to move.
		 @return		A reference to the moved window listener (i.e. this 
						window listener).
		 */
		WindowListener &operator=(WindowListener &&listener) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Processes the given message sent to a window.

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
		 @return		The return value is the result of the message 
						processing and depends on the message sent.
		 */
		virtual void HandleMessage(HWND window, 
								   UINT message, 
								   WPARAM wParam, 
								   LPARAM lParam) const = 0;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowDescriptor
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of window descriptors.
	 */
	class WindowDescriptor final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a window descriptor.

		 @pre			@a instance is not equal to @c nullptr.
		 @param[in]		instance
						The application instance handle.
		 @param[in]		window_class_name
						The window class name.
		 @param[in]		style
						The window class style.
		 @throws		Exception
						Failed to register the window class.
		 */
		explicit WindowDescriptor(HINSTANCE instance,
								  wstring window_class_name,
								  U32 window_class_style = CS_CLASSDC);

		/**
		 Constructs a window descriptor from the given window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to copy.
		 */
		WindowDescriptor(const WindowDescriptor &desc) = delete;

		/**
		 Constructs a window descriptor by moving the given window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to move.
		 */
		WindowDescriptor(WindowDescriptor &&desc) noexcept;

		/**
		 Destructs this window descriptor.
		 */
		~WindowDescriptor();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given window descriptor to this window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to copy.
		 @return		A reference to the copy of the given window descriptor 
						(i.e. this window descriptor).
		 */
		WindowDescriptor &operator=(const WindowDescriptor &desc) = delete;

		/**
		 Moves the given window descriptor to this window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to move.
		 @return		A reference to the moved window descriptor (i.e. this 
						window descriptor).
		 */
		WindowDescriptor &operator=(WindowDescriptor &&desc) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the application instance handle of this window descriptor.
		 
		 @return		The application instance handle of this window 
						descriptor.
		 */
		[[nodiscard]] HINSTANCE GetInstance() const noexcept {
			return m_instance;
		}

		/**
		 Returns the window class name of this window descriptor.
		 
		 @return		A reference to the window class name of this window 
						descriptor.
		 */
		[[nodiscard]] const wstring &GetWindowClassName() const noexcept {
			return m_window_class_name;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The application instance handle of this window descriptor.
		 */
		const HINSTANCE m_instance;

		/**
		 The window class name of this window descriptor.
		 */
		const wstring m_window_class_name;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Window
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of windows.
	 */
	class Window final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Processes the given message sent to a window.

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
		 @return		The return value is the result of the message
						processing and depends on the message sent.
		 */
		[[nodiscard]] static LRESULT CALLBACK HandleWindowMessage(HWND window, 
																  UINT message, 
																  WPARAM wParam,
																  LPARAM lParam);

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The default window style.
		 */
		static constexpr DWORD s_default_window_style = WS_OVERLAPPED 
			                                          | WS_CAPTION 
			                                          | WS_SYSMENU 
			                                          | WS_MINIMIZEBOX;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a window.

		 @pre			@a window_desc is not equal to @c nullptr.
		 @param[in]		window_desc
						A pointer to the window descriptor.
		 @param[in]		title_text
						A reference to the title text.
		 @param[in]		width
						The width of the window.
		 @param[in]		height
						The height of the window.
		 @param[in]		style
						The style of the window.
		 @throws		Exception
						Failed to create the window.
		 */
		explicit Window(SharedPtr< const WindowDescriptor > window_desc, 
						const wstring &title_text, 
						U32 width, 
						U32 height,
						DWORD style = s_default_window_style);

		/**
		 Constructs a window from the given window.

		 @param[in]		window
						A reference to the window to copy.
		 */
		Window(const Window &window) = delete;

		/**
		 Constructs a window by moving the given window.

		 @param[in]		window
						A reference to the window to move.
		 */
		Window(Window &&window) noexcept;

		/**
		 Destructs this window.
		 */
		~Window();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given window to this window.

		 @param[in]		window
						A reference to the window to copy.
		 @return		A reference to the copy of the given window (i.e. this 
						window).
		 */
		Window &operator=(const Window &window) = delete;

		/**
		 Moves the given window to this window.

		 @param[in]		window
						A reference to the window to move.
		 @return		A reference to the moved window (i.e. this window).
		 */
		Window &operator=(Window &&window) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets the show state of this window.

		 @param[in]		nCmdShow
						Controls how this window is to be shown.
		 @throws		Exception
						Failed to update the window.
		 */
		void Show(int nCmdShow);

		/**
		 Returns the window descriptor of this window.
		 
		 @return		A pointer to the window descriptor of this window.
		 */
		[[nodiscard]] SharedPtr< const WindowDescriptor >
			GetWindowDescriptor() const noexcept {

			return m_window_desc;
		}

		/**
		 Returns the application instance handle of this window.
		 
		 @return		The application instance handle of this window.
		 */
		[[nodiscard]] HINSTANCE GetInstance() const noexcept {
			return m_window_desc->GetInstance();
		}

		/**
		 Returns the window handle of this window.

		 @return		The window handle of this window.
		 */
		[[nodiscard]] HWND GetWindow() const noexcept {
			return m_window;
		}

		/**
		 Returns the title text of this window.

		 @return		The title text of this window.
		 */
		[[nodiscard]] const wstring GetTitleText() const noexcept;

		/**
		 Sets the title text of this window to the given title text.

		 @param[in]		title_text
						A reference to the title text.
		 @throws		Exception
						Failed to set the title text of this window.
		 */
		void SetTitleText(const wstring &title_text);

		/**
		 Sets the title text of this window to the given title text.

		 @pre			@a title_text is not equal to @c nullptr.
		 @param[in]		title_text
						A pointer to the title text.
		 @throws		Exception
						Failed to set the title text of this window.
		 */
		void SetTitleText(const wchar_t *title_text);

		/**
		 Adds the given listener to this window.

		 @param[in]		listener
						A pointer to the listener to add.
		 */
		void AddListener(const WindowListener *listener);

		/**
		 Removes the given listener from this window.

		 @param[in]		listener
						A pointer to the listener to remove.
		 */
		void RemoveListener(const WindowListener *listener);

	private:

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

		friend LRESULT CALLBACK HandleWindowMessage(HWND window,
													UINT message,
													WPARAM wParam,
													LPARAM lParam);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the window of this window.

		 @param[in]		title_text
						A reference to the title text.
		 @param[in]		width
						The width of the client rectangle of the window.
		 @param[in]		height
						The height of the client rectangle of the window.
		 @param[in]		style
						The style of the window.
		 @throws		Exception
						Failed to create the window.
		 */
		void InitializeWindow(const wstring &title_text, 
							  U32 width, U32 height, DWORD style);

		/**
		 Initializes the window of this window.

		 @param[in]		title_text
						A reference to the title text.
		 @param[in]		rectangle
						A reference to the client rectangle of the window.
		 @param[in]		style
						The style of the window.
		 @throws		Exception
						Failed to create the window.
		 */
		void InitializeWindow(const wstring &title_text, 
							  const RECT &rectangle, DWORD style);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the window descriptor of this window.
		 */
		const SharedPtr< const WindowDescriptor > m_window_desc;

		/**
		 The window handle of this window.
		 */
		HWND m_window;

		/**
		 A vector containing the listeners of this window.
		 */
		std::vector< const WindowListener * > m_listeners;
	};

	#pragma endregion
}