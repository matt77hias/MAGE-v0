#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

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
	class Mouse final {

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
		 @throws		FormattedException
						Failed to initialize the mouse.
		 */
		explicit Mouse(HWND hwindow, IDirectInput8 *di);

		/**
		 Constructs a mouse from the given mouse.

		 @param[in]		mouse
						A reference to the mouse to copy.
		 */
		Mouse(const Mouse &mouse) = delete;

		/**
		 Constructs a mouse by moving the given mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 */
		Mouse(Mouse &&mouse) = default;

		/**
		 Destructs this mouse.
		 */
		~Mouse() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to copy.
		 @return		A reference to the copy of the given mouse
						(i.e. this mouse).
		 */
		Mouse &operator=(const Mouse &mouse) = delete;

		/**
		 Moves the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 @return		A reference to the moved mouse
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
		int32_t GetPositionX() const {
			return static_cast< int32_t >(m_mouse_position.x);
		}

		/**
		 Returns the vertical position of this mouse.

		 @return		The vertical position of this mouse.
		 */
		int32_t GetPositionY() const {
			return static_cast< int32_t >(m_mouse_position.y);
		}

		/**
		 Returns the change in this mouse's horizontal coordinate.

		 @return		The change in this mouse's horizontal coordinate.
		 */
		int32_t GetDeltaX() const {
			return static_cast< int32_t >(m_mouse_state.lX);
		}

		/**
		 Returns the change in this mouse's vertical coordinate.

		 @return		The change in this mouse's vertical coordinate.
		 */
		int32_t GetDeltaY() const {
			return static_cast< int32_t >(m_mouse_state.lY);
		}

		/**
		 Returns the change in this mouse's scroll wheel.

		 @return		The change in this mouse's scroll wheel.
		 */
		int32_t GetDeltaWheel() const {
			return static_cast< int32_t >(m_mouse_state.lZ);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the mouse device of this mouse.

		 @throws		FormattedException
						Failed to initialize the mouse.
		 */
		void InitializeMouse();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this mouse.
		 */
		const HWND m_hwindow;

		/**
		 A pointer to the DirectInput object of this mouse.
		 */
		IDirectInput8 * const m_di;

		/**
		 A pointer to the DirectInput mouse device of this mouse.
		 */
		ComPtr< IDirectInputDevice8 > m_mouse;

		/**
		 The current press stamp (incremented every frame) of this mouse.
		 */
		uint64_t m_press_stamp;

		/**
		 The state of the mouse buttons of this mouse.

		 Describes the state of a mouse device that has up to four buttons,
		 or another device that is being accessed as if it were a mouse device.
		 */
		DIMOUSESTATE m_mouse_state;

		/**
		 The mouse button press stamp of this mouse.

		 Stamps the mouse buttons pressed in the last frame of this mouse.
		 */
		mutable uint64_t m_mouse_button_press_stamp[3];

		/**
		 The position of the mouse cursor on the screen of this mouse.
		 */
		POINT m_mouse_position;
	};
}