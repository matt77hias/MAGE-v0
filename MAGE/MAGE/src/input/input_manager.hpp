#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\keyboard.hpp"
#include "input\mouse.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of input managers.
	 */
	class InputManager : public Loadable {

	public:

		/**
		 Constructs an input manager for the given window handle.

		 @param[in]		hwindow
						The handle of the parent window.
		 */
		explicit InputManager(HWND hwindow);

		/**
		 Constructs an input manager from the given input manager.

		 @param[in]		input_manager
						A reference to the input manager.
		 */
		InputManager(const InputManager &input_manager) = delete;

		/**
		 Constructs an input manager from the given input manager.

		 @param[in]		input_manager
						A reference to the input manager.
		 */
		InputManager(InputManager &&input_manager) = default;

		/**
		 Destructs this input manager.
		 */
		virtual ~InputManager() = default;

		/**
		 Copies the given input manager to this input manager.

		 @param[in]		input_manager
						A reference to the input manager to copy from.
		 @return		A reference to the copy of the given input manager
						(i.e. this input manager).
		 */
		InputManager &operator=(const InputManager &input_manager) = delete;

		/**
		 Copies the given input manager to this input manager.

		 @param[in]		input_manager
						A reference to the input manager to copy from.
		 @return		A reference to the copy of the given input manager
						(i.e. this input manager).
		 */
		InputManager &operator=(InputManager &&input_manager) = delete;

		/**
		 Updates the state of the input systems of this input manager.
		 */
		void Update();

		/**
		 Returns the window handle of this input manager.

		 @return		The window handle of this input manager.
		 */
		HWND GetHandle() const {
			return m_hwindow;
		}

		/**
		 Returns the keyboard of this input manager.

		 @return		A reference to the keyboard of this input manager.
		 */
		const Keyboard &GetKeyboard() const {
			return *m_keyboard;
		}

		/**
		 Returns the mouse of this input manager.

		 @return		A reference to the mouse of this input manager.
		 */
		const Mouse &GetMouse() const {
			return *m_mouse;
		}

	private:

		/**
		 Initializes the DirectInput object of this input manager.

		 @return		A success/error value.
		 */
		HRESULT InitializeDI();

		/**
		 Initializes the different input systems of this input manager.
		 */
		HRESULT InitializeInputSystems();

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 The DirectInput object of this input manager.

		 The methods of the IDirectInput8 interface are used to enumerate,
		 create, and retrieve the status of Microsoft DirectInput device.
		 */
		ComPtr< IDirectInput8 > m_di;

		/**
		 A pointer to the keyboard of this input manager.
		 */
		UniquePtr< Keyboard > m_keyboard;

		/**
		 A pointer to the mouse of this input manager.
		 */
		UniquePtr< Mouse > m_mouse;
	};
}