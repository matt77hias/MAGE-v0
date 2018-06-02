//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "device\mouse.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::input {

	//-------------------------------------------------------------------------
	// Mouse Utilities
	//-------------------------------------------------------------------------
	namespace {

		/**
		 Returns the mouse position expressed in client-area coordinates.

		 @param[in]		window
						The handle of the parent window.
		 @return		The mouse position expressed in client-area coordinates.
		 */
		[[nodiscard]]
		inline const S32x2 GetMousePosition(NotNull< HWND > window) noexcept {
			POINT position;
			// Retrieve the position of the mouse cursor, in screen coordinates.
			GetCursorPos(&position);
			// Convert the screen coordinates of a specified point on the screen 
			// to client-area coordinates.
			ScreenToClient(window, &position);

			return { static_cast< S32 >(position.x),
					 static_cast< S32 >(position.y) };
		}

	}

	//-------------------------------------------------------------------------
	// Mouse::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of mouses.
	 */
	class Mouse::Impl final {

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
		explicit Impl(NotNull< HWND > window, IDirectInput8& di);

		/**
		 Constructs a mouse from the given mouse.

		 @param[in]		mouse
						A reference to the mouse to copy.
		 */
		Impl(const Impl& mouse) = delete;

		/**
		 Constructs a mouse by moving the given mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 */
		Impl(Impl&& mouse) noexcept;

		/**
		 Destructs this mouse.
		 */
		~Impl();

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
		Impl& operator=(const Impl& mouse) = delete;

		/**
		 Moves the given mouse to this mouse.

		 @param[in]		mouse
						A reference to the mouse to move.
		 @return		A reference to the moved mouse (i.e. this mouse).
		 */
		Impl& operator=(Impl&& mouse) = delete;

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
			return static_cast< S32 >(m_button_state.lX);
		}

		/**
		 Returns the change in this mouse's vertical coordinate.

		 @return		The change in this mouse's vertical coordinate.
		 */
		[[nodiscard]]
		S32 GetDeltaY() const noexcept {
			return static_cast< S32 >(m_button_state.lY);
		}

		/**
		 Returns the change in this mouse's coordinates.

		 @return		The change in this mouse's coordinates.
		 */
		[[nodiscard]]
		const S32x2 GetDelta() const noexcept {
			return { GetDeltaX(), GetDeltaY() };
		}

		/**
		 Returns the change in this mouse's scroll wheel.

		 @return		The change in this mouse's scroll wheel.
		 */
		[[nodiscard]]
		S32 GetDeltaWheel() const noexcept {
			return static_cast< S32 >(m_button_state.lZ);
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
		 The current press stamp (incremented every frame) of this mouse.
		 */
		U64 m_press_stamp;

		/**
		 The state of the mouse buttons of this mouse.

		 Describes the state of a mouse device that has up to four buttons, or 
		 another device that is being accessed as if it were a mouse device.
		 */
		DIMOUSESTATE m_button_state;

		/**
		 The mouse button press stamp of this mouse.

		 Stamps the mouse buttons pressed in the last frame of this mouse.
		 */
		mutable U64 m_button_press_stamp[3];

		/**
		 The position of the mouse cursor on the screen of this mouse.
		 */
		S32x2 m_position;
	};

	Mouse::Impl::Impl(NotNull< HWND > window, IDirectInput8& di)
		: m_window(window), 
		m_di(di), 
		m_mouse(),
		m_press_stamp(0ull), 
		m_button_state{}, 
		m_button_press_stamp(), 
		m_position{} {

		InitializeMouse();
	}

	Mouse::Impl::Impl(Impl&& mouse) noexcept = default;

	Mouse::Impl::~Impl() = default;

	void Mouse::Impl::InitializeMouse() {
		// Create and initialize an instance of a device based on a given 
		// globally unique identifier (GUID), and obtain an IDirectInputDevice8 
		// Interface interface. 
		// 1. Reference to the GUID for the desired input device.
		// 2. Address of a variable to receive the IDirectInputDevice8 
		//    Interface interface pointer if successful.
		// 3. Pointer to the address of the controlling object's IUnknown 
		//    interface for COM aggregation, or nullptr if the interface is not 
		//    aggregated.
		{
			const HRESULT result 
				= m_di.CreateDevice(GUID_SysMouse, 
									m_mouse.ReleaseAndGetAddressOf(), 
									nullptr);
			ThrowIfFailed(result,
						  "Failed to create mouse device: %08X.",
						  result);
		}
		
		// Set the data format for the DirectInput device.
		{
			const HRESULT result = m_mouse->SetDataFormat(&c_dfDIMouse);
			ThrowIfFailed(result,
						  "Failed to set data format for mouse device: %08X.",
						  result);
		}
		
		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device 
		// interacts with other instances of the device and the rest of the 
		// system.
		{
			const HRESULT result 
				= m_mouse->SetCooperativeLevel(m_window,
				                               DISCL_FOREGROUND 
											 | DISCL_NONEXCLUSIVE);
			ThrowIfFailed(result,
						  "Failed to set cooperation level for mouse device: %08X.",
						  result);
		}
		
		// Obtain access to the input device. 
		m_mouse->Acquire();
	}

	bool Mouse::Impl::GetMouseButtonPress(char button, 
										  bool ignore_press_stamp) const noexcept {
		
		if (false == (m_button_state.rgbButtons[button] & 0x80)) {
			return false;
		}

		const auto prev_press_stamp = m_press_stamp - 1;
		const auto pressed = (!ignore_press_stamp
			                  && 
			                 (prev_press_stamp == m_button_press_stamp[button]))
			                 ? false : true;

		m_button_press_stamp[button] = m_press_stamp;

		return pressed;
	}

	void Mouse::Impl::Update() noexcept {
		// Poll the mouse until it succeeds or returns an unknown error.
		while (true) {
			
			// Retrieves data from polled objects on a DirectInput device.
			m_mouse->Poll();

			// Retrieves immediate data from the device. 
			const HRESULT result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), 
				                                           &m_button_state);
			if (SUCCEEDED(result)) {
				break;
			}
			if ( DIERR_NOTACQUIRED != result
				&& DIERR_INPUTLOST != result) {
				return;
			}
			
			// Reacquire the device if the focus was lost.
			if (FAILED(m_mouse->Acquire())) {
				return;
			}
		}

		// Updates the position of this mouse.
		m_position = GetMousePosition(m_window);

		// Increment the press stamp.
		++m_press_stamp;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Mouse
	//-------------------------------------------------------------------------
	#pragma region

	Mouse::Mouse(NotNull< HWND > window, IDirectInput8& di)
		: m_impl(MakeUnique< Impl >(std::move(window), di)) {}

	Mouse::Mouse(Mouse&& mouse) noexcept = default;

	Mouse::~Mouse() = default;

	[[nodiscard]]
	NotNull< HWND > Mouse::GetWindow() noexcept {
		return m_impl->GetWindow();
	}

	void Mouse::Update() noexcept {
		m_impl->Update();
	}

	bool Mouse::GetMouseButtonPress(char button, 
									bool ignore_press_stamp) const noexcept {

		return m_impl->GetMouseButtonPress(button, ignore_press_stamp);
	}

	[[nodiscard]]
	S32 Mouse::GetPositionX() const noexcept {
		return m_impl->GetPositionX();
	}

	[[nodiscard]]
	S32 Mouse::GetPositionY() const noexcept {
		return m_impl->GetPositionY();
	}

	[[nodiscard]]
	const S32x2 Mouse::GetPosition() const noexcept {
		return m_impl->GetPosition();
	}

	[[nodiscard]]
	S32 Mouse::GetDeltaX() const noexcept {
		return m_impl->GetDeltaX();
	}

	[[nodiscard]]
	S32 Mouse::GetDeltaY() const noexcept {
		return m_impl->GetDeltaY();
	}

	[[nodiscard]]
	const S32x2 Mouse::GetDelta() const noexcept {
		return m_impl->GetDelta();
	}

	[[nodiscard]]
	S32 Mouse::GetDeltaWheel() const noexcept {
		return m_impl->GetDeltaWheel();
	}

	#pragma endregion
}