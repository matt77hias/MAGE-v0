#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"
#include "string\string.hpp"

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
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a main window.

		 @pre			@a hinstance is not equal to @c nullptr.
		 @param[in]		hinstance
						The application instance handle.
		 @param[in]		name
						A reference to the name of the application.
		 @param[in]		width
						The width of the window.
		 @param[in]		height
						The height of the window.
		 @throws		FormattedException
						Failed to register the main window's class.
		 @throws		FormattedException
						Failed to create the main window.
		 */
		explicit MainWindow(HINSTANCE hinstance, const wstring &name, LONG width, LONG height);

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
		MainWindow(MainWindow &&main_window) = default;

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
		 @return		A reference to the copy of the given main window
						(i.e. this main window).
		 */
		MainWindow &operator=(const MainWindow &main_window) = delete;

		/**
		 Moves the given main window to this main window.

		 @param[in]		main_window
						A reference to the main window to move.
		 @return		A reference to the moved main window
						(i.e. this main window).
		 */
		MainWindow &operator=(MainWindow &&main_window) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets the specified window's show state of this main window.

		 @param[in]		nCmdShow
						Controls how this window is to be shown.
		 @return		@c true if the window was previously visible.
						@c false otherwise.
		 */
		bool Show(int nCmdShow);

		/**
		 Returns the application instance handle of this main window.
		 
		 @return		The application instance handle of this main window.
		 */
		HINSTANCE GetHinstance() {
			return m_hinstance;
		}

		/**
		 Returns the window handle of this main window.

		 @return		The window handle of this main window.
		 */
		HWND GetHandle() {
			return m_hwindow;
		}

		/**
		 Returns the name of this main window.

		 @return		The name of this main window.
		 */
		const wstring &GetName() const {
			return m_name;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the engine window of this main window.

		 @param[in]		width
						The width of the client rectangle of the window.
		 @param[in]		height
						The height of the client rectangle of the window.
		 @throws		FormattedException
						Failed to register the main window's class.
		 @throws		FormattedException
						Failed to create the main window.
		 */
		void InitializeWindow(LONG width, LONG height);

		/**
		 Initializes the engine window of this main window.

		 @param[in]		rectangle
						The client rectangle of the window.
		 @throws		FormattedException
						Failed to register the main window's class.
		 @throws		FormattedException
						Failed to create the main window.
		 */
		void InitializeWindow(RECT rectangle);

		/**
		 Uninitializes the engine window of this main window.
		 */
		void UninitializeWindow();

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

		/**
		 The name of this main window.
		 */
		const wstring m_name;
	};
}