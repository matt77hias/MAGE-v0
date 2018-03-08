//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "device\keyboard.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::input {

	//-------------------------------------------------------------------------
	// Keyboard::Impl
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of keyboards.
	 */
	class Keyboard::Impl final {

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
		explicit Impl(NotNull< HWND > window, IDirectInput8& di);

		/**
		 Constructs a keyboard from the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to copy.
		 */
		Impl(const Impl& keyboard) = delete;

		/**
		 Constructs a keyboard by moving the given keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to move.
		 */
		Impl(Impl&& keyboard) noexcept;

		/**
		 Destructs this keyboard.
		 */
		~Impl();

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
		Impl& operator=(const Impl& keyboard) = delete;

		/**
		 Moves the given keyboard to this keyboard.

		 @param[in]		keyboard
						A reference to the keyboard to move.
		 @return		A reference to the moved keyboard (i.e. this keyboard).
		 */
		Impl& operator=(Impl&& keyboard) = delete;

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

	Keyboard::Impl::Impl(NotNull< HWND > window, IDirectInput8& di)
		: m_window(window), 
		m_di(di), 
		m_keyboard(),
		m_press_stamp(0ull), 
		m_key_state{}, 
		m_key_press_stamp{} {

		InitializeKeyboard();
	}

	Keyboard::Impl::Impl(Impl&& keyboard) noexcept = default;

	Keyboard::Impl::~Impl() = default;

	void Keyboard::Impl::InitializeKeyboard() {
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
				= m_di.CreateDevice(GUID_SysKeyboard, 
									m_keyboard.ReleaseAndGetAddressOf(), 
									nullptr);
			ThrowIfFailed(result, 
						  "Failed to create keyboard device: %08X.", 
						  result);
		}
		
		// Set the data format for the DirectInput device.
		{
			const HRESULT result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
			ThrowIfFailed(result, 
						  "Failed to set data format for keyboard device: %08X.",
				          result);
		}

		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device 
		// interacts with other instances of the device and the rest of the 
		// system.
		{
			const HRESULT result 
				= m_keyboard->SetCooperativeLevel(m_window, 
												  DISCL_FOREGROUND 
												| DISCL_NONEXCLUSIVE);
			ThrowIfFailed(result,
				          "Failed to set cooperation level for keyboard device: %08X.",
				          result);
		}

		// Obtain access to the input device. 
		m_keyboard->Acquire();
	}

	bool Keyboard::Impl::GetKeyPress(unsigned char key, 
									 bool ignore_press_stamp) const noexcept {
		
		if (false == (m_key_state[key] & 0x80)) {
			return false;
		}

		const auto prev_press_stamp = m_press_stamp - 1;
		const auto pressed = (!ignore_press_stamp
			                   && 
			                 (prev_press_stamp == m_key_press_stamp[key]))
			                 ? false : true;

		m_key_press_stamp[key] = m_press_stamp;

		return pressed;
	}

	void Keyboard::Impl::Update() noexcept {
		// Poll the keyboard until it succeeds or returns an unknown error.
		while (true) {
			
			// Retrieves data from polled objects on a DirectInput device.
			m_keyboard->Poll();

			// Retrieves immediate data from the device. 
			const HRESULT result 
				= m_keyboard->GetDeviceState(static_cast< DWORD >(std::size(m_key_state)), 
				                             (LPVOID)&m_key_state);

			if (SUCCEEDED(result)) {
				break;
			}
			if ( DIERR_NOTACQUIRED != result
				&& DIERR_INPUTLOST != result) {
				return;
			}
			
			// Reacquire the device if the focus was lost.
			if (FAILED(m_keyboard->Acquire())) {
				return;
			}
		}

		// Increment the press stamp.
		++m_press_stamp;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Keyboard::Impl
	//-------------------------------------------------------------------------
	#pragma region

	Keyboard::Keyboard(NotNull< HWND > window, IDirectInput8& di)
		: m_impl(MakeUnique< Impl >(std::move(window), di)) {}

	Keyboard::Keyboard(Keyboard&& keyboard) noexcept = default;

	Keyboard::~Keyboard() = default;

	[[nodiscard]]
	NotNull< HWND > Keyboard::GetWindow() noexcept {
		return m_impl->GetWindow();
	}

	void Keyboard::Update() noexcept {
		return m_impl->Update();
	}

	bool Keyboard::GetKeyPress(unsigned char key,
							   bool ignore_press_stamp) const noexcept {
		
		return m_impl->GetKeyPress(key, ignore_press_stamp);
	}

	#pragma endregion
}