#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"
#include "loadable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of main windows.
	 */
	class MainWindow : public Loadable {

	friend class Engine;

	public:

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

	protected:

		/**
		 Constructs a main window.

		 @param[in]		hinstance
						The application instance handle.
		 @param[in]		name
						The application name.
		 @param[in]		width
						The width of the window.
		 @param[in]		height
						The height of the window.
		 */
		MainWindow(HINSTANCE hinstance, wstring name, LONG width, LONG height);

		/**
		 Destructs this main window.
		 */
		virtual ~MainWindow();

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
		 Sets the specified window's show state of this main window.

		 @param[in]		nCmdShow
						Controls how this window is to be shown.
		 @return		If the window was previously visible, the return value is nonzero.
						If the window was previously hidden, the return value is zero.
		 */
		BOOL Show(int nCmdShow);

		/**
		 Application instance handle.
		 */
		HINSTANCE m_hinstance;

		/**
		 Window handle of this main window.
		 */
		HWND m_hwindow;

		/**
		 The name of this main window.
		 */
		wstring m_name;
	};
}