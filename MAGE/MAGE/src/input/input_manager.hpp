#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of input managers.
	 */
	class InputManager : public Loadable {

	friend class Engine;

	public:

		/**
		 Returns the keyboard of this input manager.

		 @return		A pointer to the keyboard of this input manager.
		 */
		const Keyboard *GetKeyboard() const {
			return m_keyboard;
		}

		/**
		 Returns the mouse of this input manager.

		 @return		A pointer to the mouse of this input manager.
		 */
		const Mouse *GetMouse() const {
			return m_mouse;
		}

	protected:

		/**
		 Constructs an input manager for the given window handle.

		 @param[in]		hwindow
						The handle of the parent window.
		 */
		InputManager(HWND hwindow);

		/**
		 Destructs this input manager.
		 */
		virtual ~InputManager();

		/**
		 Initializes the DirectInput object of this input manager.

		 @return		A success/error value.
		 */
		HRESULT InitializeDI();

		/**
		 Uninitializes the DirectInput object of this input manager.

		 @return		A success/error value.
		 */
		HRESULT UninitializeDI();

		/**
		 Initializes the different input systems of this input manager.
		 */
		HRESULT InitializeInputSystems();

		/**
		 Initializes the different input systems of this manager.
		 */
		HRESULT UninitializeInputSystems();

		/**
		 Updates the state of the input systems of this input manager.
		 */
		void Update();

		/**
		 The handle of the parent window.
		 */
		HWND m_hwindow;

		/**
		 The DirectInput object of this input manager.

		 The methods of the IDirectInput8 interface are used to enumerate,
		 create, and retrieve the status of Microsoft DirectInput device.
		 */
		IDirectInput8 *m_di;

		/**
		 A pointer to the keyboard of this input manager.
		 */
		Keyboard *m_keyboard;

		/**
		 A pointer to the mouse of this input manager.
		 */
		Mouse *m_mouse;

	private:

		/**
		 Constructs an input manager from the given input manager.

		 @param[in]		input_manager
						A reference to the input manager.
		 */
		InputManager(const InputManager &input_manager);

		/**
		 Copies the given input manager to this input manager.

		 @param[in]		input_manager
						A reference to the input manager to copy from.
		 @return		A reference to the copy of the given input manager (i.e. this input manager).
		 */
		InputManager &operator=(const InputManager &input_manager);
	};
}