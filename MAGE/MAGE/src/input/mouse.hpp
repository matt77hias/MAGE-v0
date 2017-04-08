#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loadable.hpp"
#include "input\input.hpp"
#include "memory\memory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of mouses.
	 */
	class Mouse final : public Loadable {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mouse.

		 @param[in]		hwindow
						The handle of the parent window.
		 @param[in]		di
						A pointer to a direct input object.
		 */
		explicit Mouse(HWND hwindow, IDirectInput8 *di);

		/**
		 Constructs a mouse from the given mouse.

		 @param[in]		mouse
						A reference to the mouse.
		 */
		Mouse(const Mouse &mouse) = delete;

		/**
		 Constructs a mouse from the given mouse.

		 @param[in]		mouse
						A reference to the mouse.
		 */
		Mouse(Mouse &&mouse) = default;

		/**
		 Destructs this mouse.
		 */
		virtual ~Mouse() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to copy from.
		 @return		A reference to the copy of the given mouse
						(i.e. this mouse).
		 */
		Mouse &operator=(const Mouse &mouse) = delete;

		/**
		 Copies the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to copy from.
		 @return		A reference to the copy of the given mouse
						(i.e. this mouse).
		 */
		Mouse &operator=(Mouse &&mouse) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the state of this mouse.
		 */
		void Update();

		/**
		 Returns the window handle of this mouse.

		 @return		The window handle of this mouse.
		 */
		HWND GetHandle() const {
			return m_hwindow;
		}

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
		bool GetMouseButtonPress(char mouse_button, bool ignore_press_stamp = false) const;

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

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the mouse device of this mouse.

		 @return		A success/error value.
		 */
		HRESULT InitializeMouse();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this mouse.
		 */
		HWND m_hwindow;

		/**
		 The DirectInput object of this keyboard of this mouse.
		 */
		IDirectInput8 * const m_di;

		/**
		 DirectInput mouse device of this mouse.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_mouse;

		/**
		The current press stamp (incremented every frame).
		*/
		uint64_t m_press_stamp;

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