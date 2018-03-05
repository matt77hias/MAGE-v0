#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct_input.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::input {

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
		NotNull< HWND > GetWindow() noexcept;

		/**
		 Updates the state of this mouse.
		 */
		void Update() noexcept;

		/**
		 Checks whether the given mouse button of this mouse is pressed.

		 @param[in]		button
						The mouse button.
		 @param[in]		ignore_press_stamp
						Flag indicating whether press stamps should be 
						ignored. Consistent presses will return false when 
						using the press stamp.
		 @return		@c true if the given mouse button is pressed. @c false 
						otherwise.
		 */
		bool GetMouseButtonPress(char button, 
			                     bool ignore_press_stamp = false) const noexcept;

		/**
		 Returns the horizontal position of this mouse.

		 @return		The horizontal position of this mouse.
		 */
		[[nodiscard]]
		S32 GetPositionX() const noexcept;

		/**
		 Returns the vertical position of this mouse.

		 @return		The vertical position of this mouse.
		 */
		[[nodiscard]]
		S32 GetPositionY() const noexcept;

		/**
		 Returns the position of this mouse.

		 @return		The position of this mouse.
		 */
		[[nodiscard]]
		const S32x2 GetPosition() const noexcept;

		/**
		 Returns the change in this mouse's horizontal coordinate.

		 @return		The change in this mouse's horizontal coordinate.
		 */
		[[nodiscard]]
		S32 GetDeltaX() const noexcept;

		/**
		 Returns the change in this mouse's vertical coordinate.

		 @return		The change in this mouse's vertical coordinate.
		 */
		[[nodiscard]]
		S32 GetDeltaY() const noexcept;

		/**
		 Returns the change in this mouse's coordinates.

		 @return		The change in this mouse's coordinates.
		 */
		[[nodiscard]]
		const S32x2 GetDelta() const noexcept;

		/**
		 Returns the change in this mouse's scroll wheel.

		 @return		The change in this mouse's scroll wheel.
		 */
		[[nodiscard]]
		S32 GetDeltaWheel() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this mouse.
		 */
		UniquePtr< Impl > m_impl;
	};
}