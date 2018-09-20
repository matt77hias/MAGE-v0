#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct_input.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <bitset>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::input {

	/**
	 A class of keyboards.
	 */
	class Keyboard {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a keyboard.

		 @param[in]		window
						The handle of the parent window.
		 @param[in]		di
						A reference to a direct input object.
		 @throws		Exception
						Failed to initialize the keyboard.
		 */
		explicit Keyboard(NotNull< HWND > window, IDirectInput8& di);

		/**
		 Constructs a keyboard from the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy.
		 */
		Keyboard(const Keyboard& keyboard) = delete;

		/**
		 Constructs a keyboard by moving the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to move.
		 */
		Keyboard(Keyboard&& keyboard) noexcept;

		/**
		 Destructs this keyboard.
		 */
		~Keyboard();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy.
		 @return		A reference to the copy of the given keyboard (i.e.
						this keyboard).
		 */
		Keyboard& operator=(const Keyboard& keyboard) = delete;

		/**
		 Moves the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to move.
		 @return		A reference to the moved keyboard (i.e. this keyboard).
		 */
		Keyboard& operator=(Keyboard&& keyboard) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this keyboard.

		 @return		The window handle of this keyboard.
		 */
		[[nodiscard]]
		NotNull< HWND > GetWindow() noexcept {
			return m_window;
		}

		/**
		 Updates the state of this keyboard.
		 */
		void Update() noexcept;

		/**
		 Checks whether the given key is active.

		 @param[in]		key
						The key.
		 @return		@c true if the given key is active. @c false otherwise.
		 */
		[[nodiscard]]
		bool IsActive(U8 key) const noexcept {
			const std::size_t index = 2u * key + 1u;
			return m_key_states[index];
		}

		/**
		 Checks whether the given key is passive.

		 @param[in]		key
						The key.
		 @return		@c true if the given key is passive. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool IsPassive(U8 key) const noexcept {
			return !IsActive(key);
		}

		/**
		 Checks whether the given key is switched from being passive to active
		 or vice versa (i.e. activated or deactivated).

		 @param[in]		key
						The key.
		 @return		@c true if the given key is switched from being passive
						to active or vice versa (i.e. activated or deactivated).
						@c false otherwise.
		 */
		[[nodiscard]]
		bool IsSwitched(U8 key) const noexcept {
			const std::size_t index = 2u * key;
			return m_key_states[index];
		}

		/**
		 Checks whether the given key is activated.

		 @param[in]		key
						The key.
		 @return		@c true if the given key is activated. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool IsActivated(U8 key) const noexcept {
			return IsActive(key) && IsSwitched(key);
		}

		/**
		 Checks whether the given key is deactivated.

		 @param[in]		key
						The key.
		 @return		@c true if the given key is deactivated. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool IsDeactivated(U8 key) const noexcept {
			return IsPassive(key) && IsSwitched(key);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the keyboard device of this keyboard.

		 @throws		Exception
						Failed to initialize the keyboard.
		 */
		void InitializeKeyboard();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this keyboard.
		 */
		NotNull< HWND > m_window;

		/**
		 A reference to the DirectInput object of this keyboard.
		 */
		IDirectInput8& m_di;

		/**
		 A pointer to the DirectInput keyboard device of this keyboard.
		 */
		ComPtr< IDirectInputDevice8 > m_keyboard;

		/**
		 The key states of this keyboard. Each key state consists of two flags.

		 The first flag indicates whether the key state switched from being
		 passive to active or vice versa (i.e. activated or deactivated).

		 The second flag indicates whether the key state is active.
		 */
		std::bitset< 512 > m_key_states;
	};
}