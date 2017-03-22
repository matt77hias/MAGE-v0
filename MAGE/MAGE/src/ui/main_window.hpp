#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loadable.hpp"
#include "platform\windows.hpp"
#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of main windows.
	 */
	class MainWindow : public Loadable {

	public:

		/**
		 Constructs a main window.

		 @param[in]		hinstance
						The application instance handle.
		 @param[in]		name
						A reference to the name of the application.
		 @param[in]		width
						The width of the window.
		 @param[in]		height
						The height of the window.
		 */
		MainWindow(HINSTANCE hinstance, const wstring &name, LONG width, LONG height);

		/**
		 Destructs this main window.
		 */
		virtual ~MainWindow();

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
		HINSTANCE GetHinstance() const {
			return m_hinstance;
		}

		/**
		 Returns the window handle of this main window.

		 @return		The window handle of this main window.
		 */
		HWND GetHandle() const {
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

		/**
		 Constructs a main window from the given main window.

		 @param[in]		main_window
						A reference to the main window.
		 */
		MainWindow(const MainWindow &main_window) = delete;

		/**
		 Constructs a main window from the given main window.

		 @param[in]		main_window
						A reference to the main window.
		 */
		MainWindow(MainWindow &&main_window) = delete;

		/**
		 Copies the given main window to this main window.

		 @param[in]		main_window
						A reference to the main window to copy from.
		 @return		A reference to the copy of the given main window
						(i.e. this main window).
		 */
		MainWindow &operator=(const MainWindow &main_window) = delete;

		/**
		 Copies the given main window to this main window.

		 @param[in]		main_window
						A reference to the main window to copy from.
		 @return		A reference to the copy of the given main window
						(i.e. this main window).
		 */
		MainWindow &operator=(MainWindow &&main_window) = delete;

		/**
		 Initializes the engine window of this main window.

		 @param[in]		width
						The width of the client rectangle of the window.
		 @param[in]		height
						The height of the client rectangle of the window.
		 @return		A success/error value.
		 */
		HRESULT InitializeWindow(LONG width, LONG height);

		/**
		 Initializes the engine window of this main window.

		 @param[in]		rectangle
						The client rectangle of the window.
		 @return		A success/error value.
		 */
		HRESULT InitializeWindow(RECT rectangle);

		/**
		 Unitializes the engine window of this main window.

		 @return		A success/error value.
		 */
		HRESULT UninitializeWindow();

		/**
		 Application instance handle.
		 */
		HINSTANCE m_hinstance;

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 The name of this main window.
		 */
		const wstring m_name;
	};
}