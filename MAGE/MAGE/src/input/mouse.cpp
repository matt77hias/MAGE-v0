//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\input_manager.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]]const Mouse *Mouse::Get() noexcept {
		Assert(InputManager::Get());

		return InputManager::Get()->GetMouse();
	}

	Mouse::Mouse(HWND window, IDirectInput8 *di) 
		: m_window(window), 
		m_di(di), 
		m_mouse(),
		m_press_stamp(0ull), 
		m_button_state{}, 
		m_button_press_stamp(), 
		m_position{} {

		Assert(m_window);
		Assert(m_di);

		InitializeMouse();
	}

	Mouse::Mouse(Mouse &&mouse) noexcept = default;

	Mouse::~Mouse() = default;

	void Mouse::InitializeMouse() {
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
				= m_di->CreateDevice(GUID_SysMouse,
				                     m_mouse.ReleaseAndGetAddressOf(),
				                     nullptr);
			ThrowIfFailed(result, 
				"Mouse device creation failed: %08X.", result);
		}
		
		// Set the data format for the DirectInput device.
		{
			const HRESULT result = m_mouse->SetDataFormat(&c_dfDIMouse);
			ThrowIfFailed(result, 
				          "Setting data format for mouse device failed: %08X.",
				          result);
		}
		
		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device 
		// interacts with other instances of the device and the rest of the 
		// system.
		{
			const HRESULT result 
				= m_mouse->SetCooperativeLevel(m_window,
				                               DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
			ThrowIfFailed(result,
				          "Setting cooperation level for mouse device failed: %08X.",
				          result);
		}
		
		// Obtain access to the input device. 
		m_mouse->Acquire();
	}

	bool Mouse::GetMouseButtonPress(char button, 
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

	void Mouse::Update() {
		// Poll the mouse until it succeeds or returns an unknown error.
		while (true) {
			
			// Retrieves data from polled objects on a DirectInput device.
			m_mouse->Poll();

			// Retrieves immediate data from the device. 
			// 1. Size of the buffer in bytes.
			// 2. Address of a structure that receives the current state of 
			//    the device. (format determined by SetDataFormat)
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

		// Retrieve the position of the mouse cursor, in screen coordinates.
		GetCursorPos(&m_position);
		// Convert the screen coordinates of a specified point on the screen 
		// to client-area coordinates.
		ScreenToClient(m_window, &m_position);

		// Increment the press stamp.
		++m_press_stamp;
	}
}