#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define DIRECTINPUT_VERSION 0x0800

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <dinput.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of input objects.
	 */
	class Input {

	friend class Engine;

	public:

		/**
		 Checks whether the given key is pressed.

		 @param[in]		key
						The key.
		 @param[in]		ignore_press_stamp
						Flag indicating whether press stamps should be ignored.
						Consistent presses will return false when using the press stamp.
		 @return		@c true if the given key is pressed.
						@c false otherwise.
		 */
		bool GetKeyPress(char key, bool ignore_press_stamp = false) const {
			if ((m_key_state[key] & 0x80) == false) {
				return false;
			}

			const bool pressed = (!ignore_press_stamp && (m_key_press_stamp[key] == m_press_stamp - 1 || m_key_press_stamp[key] == m_press_stamp)) ? false : true;

			m_key_press_stamp[key] = m_press_stamp;

			return pressed;
		}

		/**
		 Checks whether the given mouse button is pressed.

		 @param[in]		mouse_button
						The mouse button.
		 @param[in]		ignore_press_stamp
						Flag indicating whether press stamps should be ignored.
						Consistent presses will return false when using the press stamp.
		 @return		@c true if the given mouse button is pressed.
						@c false otherwise.
		 */
		bool GetMouseButtonPress(char mouse_button, bool ignore_press_stamp = false) const {
			if ((m_mouse_state.rgbButtons[mouse_button] & 0x80) == false) {
				return false;
			}

			const bool pressed = (!ignore_press_stamp && (m_mouse_button_press_stamp[mouse_button] == m_press_stamp - 1 || m_mouse_button_press_stamp[mouse_button] == m_press_stamp)) ? false : true;

			m_mouse_button_press_stamp[mouse_button] = m_press_stamp;

			return pressed;
		}

		/**
		 Returns the horizontal position of the mouse.

		 @return		The horizontal position of the mouse.
		 */
		long GetPosX() const {
			return m_mouse_position.x;
		}

		/**
		 Returns the vertical position of the mouse.

		 @return		The vertical position of the mouse.
		 */
		long GetPosY() const {
			return m_mouse_position.y;
		}

		/**
		 Returns the change in the mouse's horizontal coordinate.

		 @return		The change in the mouse's horizontal coordinate.
		 */
		long GetDeltaX() const {
			return m_mouse_state.lX;
		}

		/**
		 Returns the change in the mouse's vertical coordinate.

		 @return		The change in the mouse's vertical coordinate.
		 */
		long GetDeltaY() const {
			return m_mouse_state.lY;
		}

		/**
		 Returns the change in the mouse's scroll wheel.

		 @return		The change in the mouse's mouse's scroll wheel.
		*/
		long GetDeltaWheel() const {
			return m_mouse_state.lZ;
		}

	protected:

		/**
		 Constructs an input for the given window handle.

		 @param[in]		hwindow
						The handle of the parent window.
		 */
		Input(HWND hwindow);

		/**
		 Destructs this input object.
		 */
		virtual ~Input() {
			SAFE_RELEASE(m_keyboard);
			SAFE_RELEASE(m_mouse);
			SAFE_RELEASE(m_di);
		}

		/**
		 Updates the state of both the keyboard and mouse device of this input object.
		 */
		void Update();

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 The DirectInput object.

		 The methods of the IDirectInput8 interface are used to enumerate,
		 create, and retrieve the status of Microsoft DirectInput device.
		 */
		IDirectInput8 *m_di;

		/**
		 The current press stamp (incremented every frame).
		 */
		uint64_t m_press_stamp;

		// KEYBOARD

		/**
		 The DirectInput keyboard device.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_keyboard;

		/**
		 State of the keys.
		 */
		char m_key_state[256];

		/**
		 Stamps the keys pressed in the last frame.
		 */
		mutable uint64_t m_key_press_stamp[256];

		// MOUSE

		/**
		 DirectInput mouse device.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_mouse;

		/**
		 State of the mouse buttons.

		 Describes the state of a mouse device that has up to four buttons,
		 or another device that is being accessed as if it were a mouse device.
		 */
		DIMOUSESTATE m_mouse_state;

		/**
		 Stamps the mouse buttons pressed in the last frame.
		 */
		mutable uint64_t m_mouse_button_press_stamp[3];

		/**
		 The position of the mouse cursor on the screen.
		 */
		POINT m_mouse_position;
	};
}