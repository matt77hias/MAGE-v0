#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of application main windows.
	 */
	class MainWindow final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the main window associated with the current engine.

		 @pre			The current engine must exist.
		 @return		A pointer to the main window associated with the 
						current engine.
		 */
		static MainWindow *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a main window.

		 @pre			@a hinstance is not equal to @c nullptr.
		 @param[in]		hinstance
						The application instance handle.
		 @param[in]		title_text
						A reference to the title text.
		 @param[in]		width
						The width of the window.
		 @param[in]		height
						The height of the window.
		 @throws		FormattedException
						Failed to register the main window's class.
		 @throws		FormattedException
						Failed to create the main window.
		 */
		explicit MainWindow(HINSTANCE hinstance, const wstring &title_text, 
			U32 width, U32 height);

		/**
		 Constructs a main window from the given main window.

		 @param[in]		main_window
						A reference to the main window to copy.
		 */
		MainWindow(const MainWindow &main_window) = delete;

		/**
		 Constructs a main window by moving the given main window.

		 @param[in]		main_window
						A reference to the main window to move.
		 */
		MainWindow(MainWindow &&main_window);

		/**
		 Destructs this main window.
		 */
		~MainWindow();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given main window to this main window.

		 @param[in]		main_window
						A reference to the main window to copy.
		 @return		A reference to the copy of the given main window (i.e. 
						this main window).
		 */
		MainWindow &operator=(const MainWindow &main_window) = delete;

		/**
		 Moves the given main window to this main window.

		 @param[in]		main_window
						A reference to the main window to move.
		 @return		A reference to the moved main window (i.e. this main 
						window).
		 */
		MainWindow &operator=(MainWindow &&main_window) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets the specified window's show state of this main window.

		 @param[in]		nCmdShow
						Controls how this window is to be shown.
		 */
		void Show(int nCmdShow) noexcept;

		/**
		 Returns the application instance handle of this main window.
		 
		 @return		The application instance handle of this main window.
		 */
		HINSTANCE GetHinstance() noexcept {
			return m_hinstance;
		}

		/**
		 Returns the window handle of this main window.

		 @return		The window handle of this main window.
		 */
		HWND GetHandle() noexcept {
			return m_hwindow;
		}

		/**
		 Returns the title text of this main window.

		 @return		The title text of this main window.
		 */
		const wstring GetTitleText() const noexcept;

		/**
		 Sets the title text of this main window to the given title text.

		 @param[in]		title_text
						A reference to the title text.
		 */
		void SetTitleText(const wstring &title_text) noexcept;

		/**
		 Sets the title text of this main window to the given title text.

		 @pre			@a title_text is not equal to @c nullptr.
		 @param[in]		title_text
						A pointer to the title text.
		 */
		void SetTitleText(const wchar_t *title_text) noexcept;

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 The engine-defined function that processes messages sent to the engine 
		 window. The WindowProc type defines a pointer to this callback 
		 function.

		 @param[in]		hWnd
						A handle to the window.
		 @param[in]		msg
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
		static LRESULT CALLBACK MainWindowProc(
			HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

		/**
		 An enumeration of the different hot keys.

		 This contains:
		 @c Unused,
		 @c PrintScreen, and
		 @c AltPrintScreen.
		 */
		enum struct HotKey {
			Unused         = 0,
			PrintScreen    = 1,
			AltPrintScreen = 2,
		};

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the engine window of this main window.

		 @param[in]		title_text
						A reference to the title text.
		 @param[in]		width
						The width of the client rectangle of the window.
		 @param[in]		height
						The height of the client rectangle of the window.
		 @throws		FormattedException
						Failed to register the main window's class.
		 @throws		FormattedException
						Failed to create the main window.
		 */
		void InitializeWindow(const wstring &title_text, U32 width, U32 height);

		/**
		 Initializes the engine window of this main window.

		 @param[in]		title_text
						A reference to the title text.
		 @param[in]		rectangle
						A reference to the client rectangle of the window.
		 @throws		FormattedException
						Failed to register the main window's class.
		 @throws		FormattedException
						Failed to create the main window.
		 */
		void InitializeWindow(const wstring &title_text, const RECT &rectangle);

		/**
		 Uninitializes the engine window of this main window.
		 */
		void UninitializeWindow() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The application instance handle of this main window.
		 */
		const HINSTANCE m_hinstance;

		/**
		 The handle of the parent window of this main window.
		 */
		HWND m_hwindow;
	};
}