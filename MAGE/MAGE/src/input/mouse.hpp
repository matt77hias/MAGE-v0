#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\input.hpp"
#include "memory\types.hpp"

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
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the mouse associated with the current engine.

		 @pre			The input manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the mouse associated with the current 
						engine.
		 */
		static const Mouse *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mouse.

		 @pre			@a hwindow is not equal to @c nullptr.
		 @pre			@a di is not equal to @c nullptr.
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
		Mouse(Mouse &&mouse);

		/**
		 Destructs this mouse.
		 */
		~Mouse();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to copy.
		 @return		A reference to the copy of the given mouse (i.e. this 
						mouse).
		 */
		Mouse &operator=(const Mouse &mouse) = delete;

		/**
		 Moves the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 @return		A reference to the moved mouse (i.e. this mouse).
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
						Flag indicating whether press stamps should be 
						ignored. Consistent presses will return false when 
						using the press stamp.
		 @return		@c true if the given mouse button is pressed. @c false 
						otherwise.
		 */
		bool GetMouseButtonPress(char mouse_button, 
			bool ignore_press_stamp = false) const;

		/**
		 Returns the horizontal position of this mouse.

		 @return		The horizontal position of this mouse.
		 */
		i32 GetPositionX() const noexcept {
			return static_cast< i32 >(m_mouse_position.x);
		}

		/**
		 Returns the vertical position of this mouse.

		 @return		The vertical position of this mouse.
		 */
		i32 GetPositionY() const noexcept {
			return static_cast< i32 >(m_mouse_position.y);
		}

		/**
		 Returns the change in this mouse's horizontal coordinate.

		 @return		The change in this mouse's horizontal coordinate.
		 */
		i32 GetDeltaX() const noexcept {
			return static_cast< i32 >(m_mouse_state.lX);
		}

		/**
		 Returns the change in this mouse's vertical coordinate.

		 @return		The change in this mouse's vertical coordinate.
		 */
		i32 GetDeltaY() const noexcept {
			return static_cast< i32 >(m_mouse_state.lY);
		}

		/**
		 Returns the change in this mouse's scroll wheel.

		 @return		The change in this mouse's scroll wheel.
		 */
		i32 GetDeltaWheel() const noexcept {
			return static_cast< i32 >(m_mouse_state.lZ);
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
		u64 m_press_stamp;

		/**
		 The state of the mouse buttons of this mouse.

		 Describes the state of a mouse device that has up to four buttons, or 
		 another device that is being accessed as if it were a mouse device.
		 */
		DIMOUSESTATE m_mouse_state;

		/**
		 The mouse button press stamp of this mouse.

		 Stamps the mouse buttons pressed in the last frame of this mouse.
		 */
		mutable u64 m_mouse_button_press_stamp[3];

		/**
		 The position of the mouse cursor on the screen of this mouse.
		 */
		POINT m_mouse_position;
	};
}