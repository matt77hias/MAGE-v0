//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Input::Input(HWND hwindow) : m_hwindow(hwindow), m_press_stamp(0) {

		// DIRECTINPUT

		// Create a DirectInput interface.
		// 1. Instance handle to the application that is creating the DirectInput object.
		// 2. Version number of DirectInput for which the application is designed.
		// 3. Unique identifier of the desired interface. Passing IID_IDirectInput8 selects the ANSI or Unicode version of the interface.
		// 4. Address of a pointer to a variable to receive the IDirectInput8 interface pointer if successful.
		// 5. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or NULL if the interface is not aggregated.
		const HRESULT result_di_create = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_di, NULL);
		if (FAILED(result_di_create)) {
			Severe("DirectInput8Create: %d", result_di_create);
		}

		// KEYBOARD

		// Create and initialize an instance of a device based on a given globally unique identifier (GUID), 
		// and obtain an IDirectInputDevice8 Interface interface. 
		// 1. Reference to the GUID for the desired input device.
		// 2. Address of a variable to receive the IDirectInputDevice8 Interface interface pointer if successful.
		// 3. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or NULL if the interface is not aggregated.
		const HRESULT result_keyboard_create = m_di->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
		if (FAILED(result_keyboard_create)) {
			Severe("IDirectInput8::CreateDevice: %d", result_keyboard_create);
		}
		// Set the data format for the DirectInput device. 
		const HRESULT result_keyboard_format = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result_keyboard_format)) {
			Severe("IDirectInputDevice8::SetDataFormat: %d", result_keyboard_format);
		}
		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device interacts 
		// with other instances of the device and the rest of the system. 
		const HRESULT result_keyboard_cooperative = m_keyboard->SetCooperativeLevel(m_hwindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result_keyboard_cooperative)) {
			Severe("IDirectInputDevice8::SetCooperativeLevel: %d", result_keyboard_cooperative);
		}
		// Obtain access to the input device. 
		m_keyboard->Acquire();

		// MOUSE

		// Create and initialize an instance of a device based on a given globally unique identifier (GUID), 
		// and obtain an IDirectInputDevice8 Interface interface. 
		// 1. Reference to the GUID for the desired input device.
		// 2. Address of a variable to receive the IDirectInputDevice8 Interface interface pointer if successful.
		// 3. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or NULL if the interface is not aggregated.
		const HRESULT result_mouse_create = m_di->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if (FAILED(result_mouse_create)) {
			Severe("IDirectInput8::CreateDevice: %d", result_mouse_create);
		}
		// Set the data format for the DirectInput device. 
		const HRESULT result_mouse_format = m_mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result_mouse_format)) {
			Severe("IDirectInputDevice8::SetDataFormat: %d", result_mouse_format);
		}
		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device interacts 
		// with other instances of the device and the rest of the system. 
		const HRESULT result_mouse_cooperative = m_mouse->SetCooperativeLevel(m_hwindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result_mouse_cooperative)) {
			Severe("IDirectInputDevice8::SetCooperativeLevel: %d", result_mouse_cooperative);
		}
		// Obtain access to the input device. 
		m_mouse->Acquire();
	}

	void Input::Update() {
		
		// KEYBOARD
		
		// Poll the keyboard until it succeeds or returns an unknown error.
		while (true) {
			// Retrieves data from polled objects on a DirectInput device.
			m_keyboard->Poll();

			// Retrieves immediate data from the device. 
			// 1. Size of the buffer in bytes.
			// 2. Address of a structure that receives the current state of the device. (format determined by SetDataFormat)
			const HRESULT result_keyboard_state = m_keyboard->GetDeviceState(256, (LPVOID)&m_key_state);
			if (SUCCEEDED(result_keyboard_state)) {
				break;
			}
			if (result_keyboard_state != DIERR_INPUTLOST && result_keyboard_state != DIERR_NOTACQUIRED) {
				return;
			}
			// Reacquire the device if the focus was lost.
			if (FAILED(m_keyboard->Acquire())) {
				return;
			}
		}

		// MOUSE

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