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
	 A class of keyboards.
	 */
	class Keyboard : public Loadable {

	public:

		/**
		 Constructs a keyboard.

		 @param[in]		hwindow
						The handle of the parent window.
		 @param[in]		di
						A pointer to a direct input object.
		 */
		explicit Keyboard(HWND hwindow, IDirectInput8 *di);

		/**
		 Constructs a keyboard from the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard.
		 */
		Keyboard(const Keyboard &keyboard) = delete;

		/**
		 Constructs a keyboard from the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard.
		 */
		Keyboard(Keyboard &&keyboard) = default;

		/**
		 Destructs this keyboard.
		 */
		virtual ~Keyboard() = default;

		/**
		 Copies the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy from.
		 @return		A reference to the copy of the given keyboard
						(i.e. this keyboard).
		 */
		Keyboard &operator=(const Keyboard &keyboard) = delete;

		/**
		 Copies the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy from.
		 @return		A reference to the copy of the given keyboard
						(i.e. this keyboard).
		 */
		Keyboard &operator=(Keyboard &&keyboard) = delete;

		/**
		 Updates the state of this keyboard.
		 */
		void Update();

		/**
		 Returns the window handle of this keyboard.

		 @return		The window handle of this keyboard.
		 */
		HWND GetHandle() const {
			return m_hwindow;
		}

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
		bool GetKeyPress(unsigned char key, bool ignore_press_stamp = false) const;

	private:

		/**
		 Initializes the keyboard device of this keyboard.

		 @return		A success/error value.
		 */
		HRESULT InitializeKeyboard();

		/**
		 The handle of the parent window of this keyboard..
		 */
		HWND m_hwindow;

		/**
		 The DirectInput object of this keyboard.
		 */
		IDirectInput8 * const m_di;

		/**
		 The DirectInput keyboard device of this keyboard.

		 The methods of the IDirectInputDevice8 interface are used to gain and release access
		 to Microsoft DirectInput devices, manage device properties and information, set behavior,
		 perform initialization, create and play force-feedback effects, and invoke a device's control panel.
		 */
		IDirectInputDevice8 *m_keyboard;

		/**
		 The current press stamp (incremented every frame).
		 */
		uint64_t m_press_stamp;

		/**
		 State of the keys of this keyboard.
		 */
		unsigned char m_key_state[256];

		/**
		 Stamps the keys pressed in the last frame of this keyboard.
		 */
		mutable uint64_t m_key_press_stamp[256];
	};
}