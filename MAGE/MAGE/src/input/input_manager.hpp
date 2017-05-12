#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\keyboard.hpp"
#include "input\mouse.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of input managers.
	 */
	class InputManager final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an input manager for the given window handle.

		 @pre			@a hwindow is not equal to @c nullptr.
		 @param[in]		hwindow
						The handle of the parent window.
		 @throws		FormattedException
						Failed to initialize the DirectInput object.
		 @throws		FormattedException
						Failed to initialize the input systems.
		 */
		explicit InputManager(HWND hwindow);

		/**
		 Constructs an input manager from the given input manager.

		 @param[in]		input_manager
						A reference to the input manager to copy.
		 */
		InputManager(const InputManager &input_manager) = delete;

		/**
		 Constructs an input manager by moving the given input manager.

		 @param[in]		input_manager
						A reference to the input manager to move.
		 */
		InputManager(InputManager &&input_manager);

		/**
		 Destructs this input manager.
		 */
		~InputManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given input manager to this input manager.

		 @param[in]		input_manager
						A reference to the input manager to copy.
		 @return		A reference to the copy of the given input manager
						(i.e. this input manager).
		 */
		InputManager &operator=(const InputManager &input_manager) = delete;

		/**
		 Moves the given input manager to this input manager.

		 @param[in]		input_manager
						A reference to the input manager to move.
		 @return		A reference to the moved input manager
						(i.e. this input manager).
		 */
		InputManager &operator=(InputManager &&input_manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the state of the input systems of this input manager.
		 */
		void Update() {
			m_keyboard->Update();
			m_mouse->Update();
		}

		/**
		 Returns the keyboard of this input manager.

		 @return		A pointer to the keyboard of this input manager.
		 */
		const Keyboard *GetKeyboard() const noexcept {
			return m_keyboard.get();
		}

		/**
		 Returns the mouse of this input manager.

		 @return		A pointer to the mouse of this input manager.
		 */
		const Mouse *GetMouse() const noexcept {
			return m_mouse.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the DirectInput object of this input manager.

		 @throws		FormattedException
						Failed to initialize the DirectInput object.
		 */
		void InitializeDI();

		/**
		 Initializes the different input systems of this input manager.

		 @throws		FormattedException
						Failed to initialize the input systems.
		 */
		void InitializeInputSystems();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this input manager.
		 */
		const HWND m_hwindow;

		/**
		 A pointer to the DirectInput object of this input manager.

		 The methods of the IDirectInput8 interface are used to enumerate,
		 create, and retrieve the status of Microsoft DirectInput device.
		 */
		ComPtr< IDirectInput8 > m_di;

		/**
		 A pointer to the keyboard of this input manager.
		 */
		UniquePtr< Keyboard > m_keyboard;

		/**
		 A pointer to the mouse of this input manager.
		 */
		UniquePtr< Mouse > m_mouse;
	};
}