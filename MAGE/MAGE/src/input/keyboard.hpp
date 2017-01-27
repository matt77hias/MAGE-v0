#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"
#include "loadable.hpp"
#include "input\input.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of keyboards.
	 */
	class Keyboard : public Loadable {

	friend class InputManager;

	public:

		/**
		 Checks whether the given key of this keyboard is pressed.

		 @param[in]		key
						The key.
		 @param[in]		ignore_press_stamp
						Flag indicating whether press stamps should be ignored.
						Consistent presses will return false when using the press stamp.
		 @return		@c true if the given key of this keyboard is pressed.
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

	protected:

		/**
		 Constructs a keyboard.

		 @param[in]		hwindow
						The handle of the parent window.
		 @param[in]		di
						A pointer to a direct input object.
		 */
		Keyboard(HWND hwindow, IDirectInput8 *di);

		/**
		 Destructs this keyboard.
		 */
		virtual ~Keyboard();

		/**
		 Initializes the keyboard device of this keyboard.

		 @param[in]		di
						A pointer to a direct input object.
		 @return		A success/error value.
		 */
		HRESULT InitializeKeyboard(IDirectInput8 *di);

		/**
		 Uninitializes the keyboard device of this keyboard.

		 @return		A success/error value.
		 */
		HRESULT UninitializeKeyboard();

		/**
		 Updates the state of this keyboard.
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
		 The DirectInput keyboard device of this keyboard.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_keyboard;

		/**
		 State of the keys of this keyboard.
		 */
		char m_key_state[256];

		/**
		 Stamps the keys pressed in the last frame of this keyboard.
		 */
		mutable uint64_t m_key_press_stamp[256];

	private:

		/**
		 Constructs a keyboard from the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard.
		 */
		Keyboard(const Keyboard &keyboard);

		/**
		 Copies the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy from.
		 @return		A reference to the copy of the given keyboard (i.e. this keyboard).
		 */
		Keyboard &operator=(const Keyboard &keyboard);
	};
}