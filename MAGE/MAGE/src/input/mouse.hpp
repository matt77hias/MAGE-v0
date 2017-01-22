#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of mouses.
	 */
	class Mouse : public Loadable {

	friend class InputManager;

	public:

		/**
		 Checks whether the given mouse button of this mouse is pressed.

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
		 Returns the horizontal position of this mouse.

		 @return		The horizontal position of this mouse.
		 */
		long GetPosX() const {
			return m_mouse_position.x;
		}

		/**
		 Returns the vertical position of this mouse.

		 @return		The vertical position of this mouse.
		 */
		long GetPosY() const {
			return m_mouse_position.y;
		}

		/**
		 Returns the change in this mouse's horizontal coordinate.

		 @return		The change in this mouse's horizontal coordinate.
		 */
		long GetDeltaX() const {
			return m_mouse_state.lX;
		}

		/**
		 Returns the change in this mouse's vertical coordinate.

		 @return		The change in this mouse's vertical coordinate.
		 */
		long GetDeltaY() const {
			return m_mouse_state.lY;
		}

		/**
		 Returns the change in this mouse's scroll wheel.

		 @return		The change in this mouse's scroll wheel.
		 */
		long GetDeltaWheel() const {
			return m_mouse_state.lZ;
		}

	protected:

		/**
		 Constructs a mouse.

		 @param[in]		hwindow
						The handle of the parent window.
		 @param[in]		di
						A pointer to a direct input object.
		 */
		Mouse(HWND hwindow, IDirectInput8 *di);

		/**
		 Destructs this mouse.
		 */
		virtual ~Mouse();

		/**
		 Initializes the mouse device of this mouse.

		 @param[in]		di
						A pointer to a direct input object.
		 @return		A success/error value.
		 */
		HRESULT InitializeMouse(IDirectInput8 *di);

		/**
		 Uninitializes the mouse device of this mouse.

		 @return		A success/error value.
		 */
		HRESULT UninitializeMouse();

		/**
		 Updates the state of this mouse.
		 */
		void Update();

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 The current press stamp (incremented every frame).
		 */
		uint64_t m_press_stamp;

		/**
		 DirectInput mouse device of this mouse.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_mouse;

		/**
		 State of the mouse buttons of this mouse.

		 Describes the state of a mouse device that has up to four buttons,
		 or another device that is being accessed as if it were a mouse device.
		 */
		DIMOUSESTATE m_mouse_state;

		/**
		 Stamps the mouse buttons pressed in the last frame of this mouse.
		 */
		mutable uint64_t m_mouse_button_press_stamp[3];

		/**
		 The position of the mouse cursor on the screen of this mouse.
		 */
		POINT m_mouse_position;
	};
}