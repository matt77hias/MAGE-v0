#pragma once

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

#include <optional>
#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
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
		Unused = 0,
		PrintScreen,
		AltPrintScreen,
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowMessageListener
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of window message listeners.
	 */
	class WindowMessageListener {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a window message listener.
		 */
		WindowMessageListener() noexcept;

		/**
		 Constructs a window message listener from the given window message
		 listener.

		 @param[in]		listener
						A reference to the window message listener to copy.
		 */
		WindowMessageListener(const WindowMessageListener& listener) noexcept;

		/**
		 Constructs a window message listener by moving the given window message
		 listener.

		 @param[in]		listener
						A reference to the window message listener to move.
		 */
		WindowMessageListener(WindowMessageListener&& listener) noexcept;

		/**
		 Destructs this window message listener.
		 */
		virtual ~WindowMessageListener();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given window message listener to this window message
		 listener.

		 @param[in]		listener
						A reference to the window message listener to copy.
		 @return		A reference to the copy of the given window message
						listener (i.e. this window message listener).
		 */
		WindowMessageListener& operator=(
			const WindowMessageListener& listener) noexcept;

		/**
		 Moves the given window message listener to this window message
		 listener.

		 @param[in]		listener
						A reference to the window message listener to move.
		 @return		A reference to the moved window message listener (i.e.
						this window message listener).
		 */
		WindowMessageListener& operator=(
			WindowMessageListener&& listener) noexcept;

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
		 */
		virtual void
			ProcessWindowMessage([[maybe_unused]] NotNull< HWND > window,
								 UINT message,
								 [[maybe_unused]] WPARAM wParam,
								 [[maybe_unused]] LPARAM lParam) = 0;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowMessageHandler
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of window message handlers.
	 */
	class WindowMessageHandler {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a window message handler.
		 */
		WindowMessageHandler() noexcept;

		/**
		 Constructs a window message handler from the given window message
		 handler.

		 @param[in]		handler
						A reference to the window message handler to copy.
		 */
		WindowMessageHandler(const WindowMessageHandler& handler) noexcept;

		/**
		 Constructs a window message handler by moving the given window message
		 handler.

		 @param[in]		handler
						A reference to the window message handler to move.
		 */
		WindowMessageHandler(WindowMessageHandler&& handler) noexcept;

		/**
		 Destructs this window message handler.
		 */
		virtual ~WindowMessageHandler();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given window message handler to this window message
		 handler.

		 @param[in]		handler
						A reference to the window message handler to copy.
		 @return		A reference to the copy of the given window message
						handler (i.e. this window message handler).
		 */
		WindowMessageHandler& operator=(
			const WindowMessageHandler& handler) noexcept;

		/**
		 Moves the given window message handler to this window message handler.

		 @param[in]		handler
						A reference to the window message handler to move.
		 @return		A reference to the moved window message handler (i.e.
						this window message handler).
		 */
		WindowMessageHandler& operator=(
			WindowMessageHandler&& handler) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Handles the given message sent to a window.

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
		 @return		The result of the message processing, if the given
						message is handled by this window message handler.
		 */
		[[nodiscard]]
		virtual const std::optional< LRESULT >
			HandleWindowMessage([[maybe_unused]] NotNull< HWND > window,
								UINT message,
								[[maybe_unused]] WPARAM wParam,
								[[maybe_unused]] LPARAM lParam) = 0;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// WindowDescriptor
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of window descriptors.
	 */
	class WindowDescriptor {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a window descriptor.

		 @param[in]		instance
						The application instance handle.
		 @param[in]		window_class_name
						The window class name.
		 @param[in]		window_class_style
						The window class style.
		 @throws		Exception
						Failed to register the window class.
		 */
		explicit WindowDescriptor(NotNull< HINSTANCE > instance,
								  std::wstring window_class_name,
								  U32 window_class_style = CS_CLASSDC);

		/**
		 Constructs a window descriptor from the given window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to copy.
		 */
		WindowDescriptor(const WindowDescriptor& desc) = delete;

		/**
		 Constructs a window descriptor by moving the given window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to move.
		 */
		WindowDescriptor(WindowDescriptor&& desc) noexcept;

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
		WindowDescriptor& operator=(const WindowDescriptor& desc) = delete;

		/**
		 Moves the given window descriptor to this window descriptor.

		 @param[in]		desc
						A reference to the window descriptor to move.
		 @return		A reference to the moved window descriptor (i.e. this
						window descriptor).
		 */
		WindowDescriptor& operator=(WindowDescriptor&& desc) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the application instance handle of this window descriptor.

		 @return		The application instance handle of this window
						descriptor.
		 */
		[[nodiscard]]
		NotNull< HINSTANCE > GetInstance() const noexcept {
			return m_instance;
		}

		/**
		 Returns the window class name of this window descriptor.

		 @return		The window class name of this window descriptor.
		 */
		[[nodiscard]]
		const std::wstring_view GetWindowClassName() const noexcept {
			return m_window_class_name;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The application instance handle of this window descriptor.
		 */
		NotNull< HINSTANCE > m_instance;

		/**
		 The window class name of this window descriptor.
		 */
		std::wstring m_window_class_name;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Window
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of windows.
	 */
	class Window {

	public:

		//---------------------------------------------------------------------
		// Types
		//---------------------------------------------------------------------

		using WindowDescriptorPtr = SharedPtr< const WindowDescriptor >;

		using WindowMessageListenerPtr = NotNull< WindowMessageListener* >;

		using WindowMessageHandlerPtr = NotNull< WindowMessageHandler* >;

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
		[[nodiscard]]
		static LRESULT CALLBACK HandleWindowMessage(HWND window,
													UINT message,
													WPARAM wParam,
													LPARAM lParam);

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The default window style of windows.
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
						The title text.
		 @param[in]		resolution
						The resolution of the window.
		 @param[in]		style
						The style of the window.
		 @throws		Exception
						Failed to create the window.
		 */
		explicit Window(WindowDescriptorPtr window_desc,
						std::wstring_view title_text,
						const U32x2& resolution,
						DWORD style = s_default_window_style);

		/**
		 Constructs a window from the given window.

		 @param[in]		window
						A reference to the window to copy.
		 */
		Window(const Window& window) = delete;

		/**
		 Constructs a window by moving the given window.

		 @param[in]		window
						A reference to the window to move.
		 */
		Window(Window&& window) noexcept;

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
		Window& operator=(const Window& window) = delete;

		/**
		 Moves the given window to this window.

		 @param[in]		window
						A reference to the window to move.
		 @return		A reference to the moved window (i.e. this window).
		 */
		Window& operator=(Window&& window) = delete;

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
		[[nodiscard]]
		WindowDescriptorPtr GetWindowDescriptor() const noexcept {
			return m_window_desc;
		}

		/**
		 Returns the application instance handle of this window.

		 @return		The application instance handle of this window.
		 */
		[[nodiscard]]
		NotNull< HINSTANCE > GetInstance() const noexcept {
			return m_window_desc->GetInstance();
		}

		/**
		 Returns the window handle of this window.

		 @return		The window handle of this window.
		 */
		[[nodiscard]]
		HWND GetWindow() const noexcept {
			return m_window;
		}

		/**
		 Returns the title text of this window.

		 @return		The title text of this window.
		 */
		[[nodiscard]]
		const std::wstring GetTitleText() const noexcept;

		/**
		 Sets the title text of this window to the given title text.

		 @param[in]		title_text
						A pointer to the title text.
		 @throws		Exception
						Failed to set the title text of this window.
		 */
		void SetTitleText(NotNull< const_wzstring > title_text);

		/**
		 Adds the given window message listener to this window.

		 @param[in]		listener
						A pointer to the window message listener to add.
		 */
		void AddListener(WindowMessageListenerPtr listener);

		/**
		 Removes the given window message listener from this window.

		 @param[in]		listener
						A pointer to the window message listener to remove.
		 */
		void RemoveListener(WindowMessageListenerPtr listener);

		/**
		 Removes all the window message listeners from this window.
		 */
		void RemoveAllListeners() noexcept;

		/**
		 Adds the given window message handler to this window.

		 @param[in]		handler
						A pointer to the window message handler to add.
		 */
		void AddHandler(WindowMessageHandlerPtr handler);

		/**
		 Removes the given window message handler from this window.

		 @param[in]		handler
						A pointer to the window message handler to remove.
		 */
		void RemoveHandler(WindowMessageHandlerPtr handler);

		/**
		 Removes all the window message handlers from this window.
		 */
		void RemoveAllHandlers() noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the window of this window.

		 @param[in]		title_text
						The title text.
		 @param[in]		resolution
						The resolution of the client rectangle of the window.
		 @param[in]		style
						The style of the window.
		 @throws		Exception
						Failed to create the window.
		 */
		void InitializeWindow(std::wstring_view title_text,
							  const U32x2& resolution,
							  DWORD style);

		/**
		 Initializes the window of this window.

		 @param[in]		title_text
						The title text.
		 @param[in]		rectangle
						A reference to the client rectangle of the window.
		 @param[in]		style
						The style of the window.
		 @throws		Exception
						Failed to create the window.
		 */
		void InitializeWindow(std::wstring_view title_text,
							  const RECT& rectangle,
							  DWORD style);

		/**
		 Handles the given message sent to this window.

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
		 @return		The result of the message processing, if the given
						message is handled by this window.
		 */
		[[nodiscard]]
		const std::optional< LRESULT >
			HandleWindowMessage(NotNull< HWND > window, UINT message,
								WPARAM wParam, LPARAM lParam) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the window descriptor of this window.
		 */
		WindowDescriptorPtr m_window_desc;

		/**
		 The window handle of this window.
		 */
		HWND m_window;

		/**
		 A vector containing the message listeners of this window.
		 */
		std::vector< WindowMessageListenerPtr > m_listeners;

		/**
		 A vector containing the message handler of this window.
		 */
		std::vector< WindowMessageHandlerPtr > m_handlers;
	};

	#pragma endregion
}