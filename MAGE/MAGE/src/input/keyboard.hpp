#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\input.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 A class of keyboards.
	 */
	class Keyboard final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the keyboard of the input manager associated with the current 
		 engine.

		 @pre			The input manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the keyboard of the input manager 
						associated with the current engine.
		 */
		[[nodiscard]]static const Keyboard *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a keyboard.

		 @pre			@a window is not equal to @c nullptr.
		 @pre			@a di is not equal to @c nullptr.
		 @param[in]		window
						The handle of the parent window.
		 @param[in]		di
						A pointer to a direct input object.
		 @throws		Exception
						Failed to initialize the keyboard.
		 */
		explicit Keyboard(HWND window, IDirectInput8 *di);

		/**
		 Constructs a keyboard from the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy.
		 */
		Keyboard(const Keyboard &keyboard) = delete;

		/**
		 Constructs a keyboard by moving the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to move.
		 */
		Keyboard(Keyboard &&keyboard) noexcept;

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
		Keyboard &operator=(const Keyboard &keyboard) = delete;

		/**
		 Moves the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to move.
		 @return		A reference to the moved keyboard (i.e. this keyboard).
		 */
		Keyboard &operator=(Keyboard &&keyboard) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this keyboard.

		 @return		The window handle of this keyboard.
		 */
		[[nodiscard]]HWND GetWindow() noexcept {
			return m_window;
		}

		/**
		 Updates the state of this keyboard.
		 */
		void Update();

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
		HWND m_window;

		/**
		 A pointer to the DirectInput object of this keyboard.
		 */
		IDirectInput8 * const m_di;

		/**
		 A pointer to the DirectInput keyboard device of this keyboard.
		 */
		ComPtr< IDirectInputDevice8 > m_keyboard;

		/**
		 The current press stamp (incremented every frame) of this keyboard.
		 */
		U64 m_press_stamp;

		/**
		 The state of the key buttons of this keyboard.
		 */
		unsigned char m_key_state[256];

		/**
		 The key button press stamp of this keyboard.
		 
		 Stamps the keys pressed in the last frame of this keyboard.
		 */
		mutable U64 m_key_press_stamp[256];
	};
}