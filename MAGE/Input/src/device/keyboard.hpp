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
	 A class of keyboards.
	 */
	class Keyboard final {

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
		NotNull< HWND > GetWindow() noexcept;

		/**
		 Updates the state of this keyboard.
		 */
		void Update() noexcept;

		/**
		 Checks whether the given key of this keyboard is pressed.

		 @param[in]		key
						The key.
		 @param[in]		ignore_press_stamp
						Flag indicating whether press stamps should be 
						ignored. Consistent presses will return false when 
						using the press stamp.
		 @return		@c true if the given key of this keyboard is pressed.
						@c false otherwise.
		 */
		bool GetKeyPress(unsigned char key, 
			             bool ignore_press_stamp = false) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/**
		 A pointer to the implementation of this keyboard.
		 */
		UniquePtr< Impl > m_impl;
	};
}