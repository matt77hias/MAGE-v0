//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "device\keyboard.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::input {

	Keyboard::Keyboard(NotNull< HWND > window, IDirectInput8& di)
		: m_window(window), 
		m_di(di), 
		m_keyboard(), 
		m_key_states{} {

		InitializeKeyboard();
	}

	Keyboard::Keyboard(Keyboard&& keyboard) noexcept = default;

	Keyboard::~Keyboard() = default;

	void Keyboard::InitializeKeyboard() {
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

	void Keyboard::Update() noexcept {
		unsigned char key_states[256u];

		// Poll the keyboard until it succeeds or returns an unknown error.
		while (true) {
			
			// Retrieves data from polled objects on a DirectInput device.
			m_keyboard->Poll();

			// Retrieves immediate data from the device. 
			const HRESULT result 
				= m_keyboard->GetDeviceState(static_cast< DWORD >(std::size(key_states)),
				                             (LPVOID)&key_states);

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

		// Update the key states.
		for (std::size_t i = 0u; i < std::size(key_states); ++i) {
			const bool active = key_states[i] & 0x80u;
			m_key_states[2u*i]    = (active != m_key_states[2u*i+1u]);
			m_key_states[2u*i+1u] = active;
		}
	}
}
