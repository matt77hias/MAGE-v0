//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input_manager.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::input {

	//-------------------------------------------------------------------------
	// InputManager::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of input managers.
	 */
	class InputManager::Impl final {

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
		explicit Impl(NotNull< HWND > window);

		/**
		 Constructs an input manager from the given input manager.

		 @param[in]		manager
						A reference to the input manager to copy.
		 */
		Impl(const Impl& manager) = delete;

		/**
		 Constructs an input manager by moving the given input manager.

		 @param[in]		manager
						A reference to the input manager to move.
		 */
		Impl(Impl&& manager) noexcept;

		/**
		 Destructs this input manager.
		 */
		~Impl();

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
		Impl& operator=(const Impl& manager) = delete;

		/**
		 Moves the given input manager to this input manager.

		 @param[in]		manager
						A reference to the input manager to move.
		 @return		A reference to the moved input manager (i.e. this 
						input manager).
		 */
		Impl& operator=(Impl&& manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the window handle of this input manager.

		 @return		The window handle of this input manager.
		 */
		[[nodiscard]]
		NotNull< HWND > GetWindow() noexcept {
			return m_window;
		}

		/**
		 Updates the state of the input systems of this input manager.
		 */
		void Update() noexcept {
			m_keyboard->Update();
			m_mouse->Update();
		}

		/**
		 Returns the keyboard of this input manager.

		 @return		A reference to the keyboard of this input manager.
		 */
		[[nodiscard]]
		const Keyboard& GetKeyboard() const noexcept {
			return *m_keyboard.get();
		}

		/**
		 Returns the mouse of this input manager.

		 @return		A reference to the mouse of this input manager.
		 */
		[[nodiscard]]
		const Mouse& GetMouse() const noexcept {
			return *m_mouse.get();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Initializes the DirectInput object of this input manager.

		 @throws		Exception
						Failed to initialize the DirectInput object.
		 */
		void InitializeDI();

		/**
		 Initializes the different input systems of this input manager.

		 @throws		Exception
						Failed to initialize the input systems.
		 */
		void InitializeInputSystems();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The handle of the parent window of this input manager.
		 */
		NotNull< HWND > m_window;

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

	InputManager::Impl::Impl(NotNull< HWND > window)
		: m_window(window), 
		m_di(), 
		m_keyboard(), 
		m_mouse() {

		InitializeDI();
		InitializeInputSystems();
	}

	InputManager::Impl::Impl(Impl&& manager) noexcept = default;

	InputManager::Impl::~Impl() = default;

	void InputManager::Impl::InitializeDI() {
		// Create a DirectInput interface.
		// 1. Instance handle to the application that is creating the 
		//    DirectInput object.
		// 2. Version number of DirectInput for which the application is 
		//    designed.
		// 3. Unique identifier of the desired interface. Passing 
		//    IID_IDirectInput8 selects the ANSI or Unicode version of the 
		//    interface.
		// 4. Address of a pointer to a variable to receive the IDirectInput8 
		//    interface pointer if successful.
		// 5. Pointer to the address of the controlling object's IUnknown 
		//    interface for COM aggregation, or nullptr if the interface is 
		//    not aggregated.
		const HRESULT result = DirectInput8Create(GetModuleHandle(nullptr), 
			                                      DIRECTINPUT_VERSION, 
			                                      IID_IDirectInput8, 
			                                      (void**)m_di.ReleaseAndGetAddressOf(), 
			                                      nullptr);
		ThrowIfFailed(result, "DirectInput initialization failed: %ld", result);
	}

	void InputManager::Impl::InitializeInputSystems() {
		m_keyboard = MakeUnique< Keyboard >(m_window, *m_di.Get());
		m_mouse    = MakeUnique< Mouse >(   m_window, *m_di.Get());
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// InputManager
	//-------------------------------------------------------------------------
	#pragma region

	InputManager::InputManager(NotNull< HWND > window) 
		: m_impl(MakeUnique< Impl >(std::move(window))) {}

	InputManager::InputManager(InputManager&& manager) noexcept = default;

	InputManager::~InputManager() = default;

	NotNull< HWND > InputManager::GetWindow() noexcept {
		return m_impl->GetWindow();
	}

	void InputManager::Update() noexcept {
		m_impl->Update();
	}

	[[nodiscard]]
	const Keyboard& InputManager::GetKeyboard() const noexcept {
		return m_impl->GetKeyboard();
	}

	[[nodiscard]]
	const Mouse& InputManager::GetMouse() const noexcept {
		return m_impl->GetMouse();
	}

	#pragma endregion
}