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
	 A class of mouses.
	 */
	class Mouse {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mouse.

		 @param[in]		window
						The handle of the parent window.
		 @param[in]		di
						A reference to a direct input object.
		 @throws		Exception
						Failed to initialize the mouse.
		 */
		explicit Mouse(NotNull< HWND > window, IDirectInput8& di);

		/**
		 Constructs a mouse from the given mouse.

		 @param[in]		mouse
						A reference to the mouse to copy.
		 */
		Mouse(const Mouse& mouse) = delete;

		/**
		 Constructs a mouse by moving the given mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 */
		Mouse(Mouse&& mouse) noexcept;

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
		Mouse& operator=(const Mouse& mouse) = delete;

		/**
		 Moves the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 @return		A reference to the moved mouse (i.e. this mouse).
		 */
		Mouse& operator=(Mouse&& mouse) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this mouse.

		 @return		The window handle of this mouse.
		 */
		[[nodiscard]]
		NotNull< HWND > GetWindow() noexcept {
			return m_window;
		}

		/**
		 Updates the state of this mouse.
		 */
		void Update() noexcept;

		/**
		 Checks whether the given button is active.

		 @param[in]		button
						The button.
		 @return		@c true if the given button is active. @c false otherwise.
		 */
		[[nodiscard]]
		bool IsActive(U8 button) const noexcept {
			const size_t index = 2 * button + 1;
			return m_button_states[index];
		}

		/**
		 Checks whether the given button is passive.

		 @param[in]		button
						The button.
		 @return		@c true if the given button is passive. @c false 
						otherwise.
		 */
		[[nodiscard]]
		bool IsPassive(U8 button) const noexcept {
			return !IsActive(button);
		}

		/**
		 Checks whether the given button is switched from being passive to 
		 active or vice versa (i.e. activated or deactivated).

		 @param[in]		button
						The button.
		 @return		@c true if the given button is switched from being 
						passive to active or vice versa (i.e. activated or 
						deactivated). @c false otherwise.
		 */
		[[nodiscard]]
		bool IsSwitched(U8 button) const noexcept {
			const size_t index = 2 * button;
			return m_button_states[index];
		}

		/**
		 Checks whether the given button is activated.

		 @param[in]		button
						The button.
		 @return		@c true if the given button is activated. @c false 
						otherwise.
		 */
		[[nodiscard]]
		bool IsActivated(U8 button) const noexcept {
			return IsActive(button) && IsSwitched(button);
		}

		/**
		 Checks whether the given button is deactivated.

		 @param[in]		button
						The button.
		 @return		@c true if the given button is deactivated. @c false 
						otherwise.
		 */
		[[nodiscard]]
		bool IsDeactivated(U8 button) const noexcept {
			return IsPassive(button) && IsSwitched(button);
		}

		/**
		 Returns the horizontal position of this mouse.

		 @return		The horizontal position of this mouse.
		 */
		[[nodiscard]]
		S32 GetPositionX() const noexcept {
			return m_position[0];
		}

		/**
		 Returns the vertical position of this mouse.

		 @return		The vertical position of this mouse.
		 */
		[[nodiscard]]
		S32 GetPositionY() const noexcept {
			return m_position[1];
		}

		/**
		 Returns the position of this mouse.

		 @return		The position of this mouse.
		 */
		[[nodiscard]]
		const S32x2 GetPosition() const noexcept {
			return m_position;
		}

		/**
		 Returns the change in this mouse's horizontal coordinate.

		 @return		The change in this mouse's horizontal coordinate.
		 */
		[[nodiscard]]
		S32 GetDeltaX() const noexcept {
			return m_delta[0];
		}

		/**
		 Returns the change in this mouse's vertical coordinate.

		 @return		The change in this mouse's vertical coordinate.
		 */
		[[nodiscard]]
		S32 GetDeltaY() const noexcept {
			return m_delta[1];
		}

		/**
		 Returns the change in this mouse's coordinates.

		 @return		The change in this mouse's coordinates.
		 */
		[[nodiscard]]
		const S32x2 GetDelta() const noexcept {
			return m_delta;
		}

		/**
		 Returns the change in this mouse's scroll wheel.

		 @return		The change in this mouse's scroll wheel.
		 */
		[[nodiscard]]
		S32 GetDeltaWheel() const noexcept {
			return m_delta_wheel;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the mouse device of this mouse.

		 @throws		Exception
						Failed to initialize the mouse.
		 */
		void InitializeMouse();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this mouse.
		 */
		NotNull< HWND > m_window;

		/**
		 A reference to the DirectInput object of this mouse.
		 */
		IDirectInput8& m_di;

		/**
		 A pointer to the DirectInput mouse device of this mouse.
		 */
		ComPtr< IDirectInputDevice8 > m_mouse;

		/**
		 The position of the mouse cursor on the screen of this mouse.
		 */
		S32x2 m_position;

		/**
		 The change in the horizontal and vertical coordinates of this mouse.
		 */
		S32x2 m_delta;

		/**
		 The change in the scroll wheel coordinates of this mouse.
		 */
		S32 m_delta_wheel;

		/**
		 The button states of this mouse. Each button state consists of two 
		 flags.

		 The first flag indicates whether the button state switched from being 
		 passive to active or vice versa (i.e. activated or deactivated).

		 The second flag indicates whether the button state is active.
		 */
		std::bitset< 16 > m_button_states;
	};
}