#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "device\keyboard.hpp"
#include "device\mouse.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::input {

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

		 @param[in]		window
						The handle of the parent window.
		 @throws		Exception
						Failed to initialize the DirectInput object.
		 @throws		Exception
						Failed to initialize the input systems.
		 */
		explicit InputManager(NotNull< HWND > window);

		/**
		 Constructs an input manager from the given input manager.

		 @param[in]		manager
						A reference to the input manager to copy.
		 */
		InputManager(const InputManager& manager) = delete;

		/**
		 Constructs an input manager by moving the given input manager.

		 @param[in]		manager
						A reference to the input manager to move.
		 */
		InputManager(InputManager&& manager) noexcept;

		/**
		 Destructs this input manager.
		 */
		~InputManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given input manager to this input manager.

		 @param[in]		manager
						A reference to the input manager to copy.
		 @return		A reference to the copy of the given input manager 
						(i.e. this input manager).
		 */
		InputManager& operator=(const InputManager& manager) = delete;

		/**
		 Moves the given input manager to this input manager.

		 @param[in]		manager
						A reference to the input manager to move.
		 @return		A reference to the moved input manager (i.e. this 
						input manager).
		 */
		InputManager& operator=(InputManager&& manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this input manager.

		 @return		The window handle of this input manager.
		 */
		[[nodiscard]]
		NotNull< HWND > GetWindow() noexcept;

		/**
		 Updates the state of the input systems of this input manager.
		 */
		void Update() noexcept;

		/**
		 Returns the keyboard of this input manager.

		 @return		A reference to the keyboard of this input manager.
		 */
		[[nodiscard]]
		const Keyboard& GetKeyboard() const noexcept;

		/**
		 Returns the mouse of this input manager.

		 @return		A reference to the mouse of this input manager.
		 */
		[[nodiscard]]
		const Mouse& GetMouse() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		class Impl;

		/** 
		 A pointer to the implementation of this input manager.
		 */
		UniquePtr< Impl > m_impl;
	};
}