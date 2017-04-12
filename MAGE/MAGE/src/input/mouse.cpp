//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\mouse.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Mouse::Mouse(HWND hwindow, IDirectInput8 *di) 
		: Loadable(), m_hwindow(hwindow), m_di(di),
		m_press_stamp(0), m_mouse_button_press_stamp() {

		const HRESULT result_mouse = InitializeMouse();
		if (FAILED(result_mouse)) {
			Error("Mouse initialization failed: %08X.", result_mouse);
			return;
		}

		SetLoaded();
	}

	HRESULT Mouse::InitializeMouse() {
		// Create and initialize an instance of a device based on a given globally unique identifier (GUID), 
		// and obtain an IDirectInputDevice8 Interface interface. 
		// 1. Reference to the GUID for the desired input device.
		// 2. Address of a variable to receive the IDirectInputDevice8 Interface interface pointer if successful.
		// 3. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or nullptr if the interface is not aggregated.
		const HRESULT result_mouse_create = m_di->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
		if (FAILED(result_mouse_create)) {
			Error("Mouse device creation failed: %08X.", result_mouse_create);
			return result_mouse_create;
		}
		// Set the data format for the DirectInput device. 
		const HRESULT result_mouse_format = m_mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result_mouse_format)) {
			Error("Setting data format for mouse device failed: %08X.", result_mouse_format);
			return result_mouse_format;
		}
		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device interacts 
		// with other instances of the device and the rest of the system. 
		const HRESULT result_mouse_cooperative = m_mouse->SetCooperativeLevel(m_hwindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result_mouse_cooperative)) {
			Error("Setting cooperation level for mouse device failed: %08X.", result_mouse_cooperative);
			return result_mouse_cooperative;
		}
		// Obtain access to the input device. 
		m_mouse->Acquire();

		return S_OK;
	}

	bool Mouse::GetMouseButtonPress(char mouse_button, bool ignore_press_stamp) const {
		if ((m_mouse_state.rgbButtons[mouse_button] & 0x80) == false) {
			return false;
		}

		const bool pressed = (!ignore_press_stamp && (m_mouse_button_press_stamp[mouse_button] == m_press_stamp - 1)) 
							? false : true;

		m_mouse_button_press_stamp[mouse_button] = m_press_stamp;

		return pressed;
	}

	void Mouse::Update() {
		// Poll the mouse until it succeeds or returns an unknown error.
		while (true) {
			// Retrieves data from polled objects on a DirectInput device.
			m_mouse->Poll();

			// Retrieves immediate data from the device. 
			// 1. Size of the buffer in bytes.
			// 2. Address of a structure that receives the current state of the device. (format determined by SetDataFormat)
			const HRESULT result_mouse_state = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouse_state);
			if (SUCCEEDED(result_mouse_state)) {
				break;
			}
			if (result_mouse_state != DIERR_INPUTLOST && result_mouse_state != DIERR_NOTACQUIRED) {
				return;
			}
			// Reacquire the device if the focus was lost.
			if (FAILED(m_mouse->Acquire())) {
				return;
			}
		}

		// Retrieve the position of the mouse cursor, in screen coordinates.
		GetCursorPos(&m_mouse_position);
		// Convert the screen coordinates of a specified point on the screen to client-area coordinates.
		ScreenToClient(m_hwindow, &m_mouse_position);

		// Increment the press stamp.
		++m_press_stamp;
	}
}