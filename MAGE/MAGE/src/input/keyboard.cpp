//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\input.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Keyboard::Keyboard(HWND hwindow, IDirectInput8 *di) : Loadable(), 
		m_press_stamp(0), m_hwindow(hwindow) {

		const HRESULT result_keyboard = InitializeKeyboard(di);
		if (FAILED(result_keyboard)) {
			Error("Keyboard initialization failed: %ld.", result_keyboard);
			return;
		}

		SetLoaded();
	}

	Keyboard::~Keyboard() {
		const HRESULT result_keyboard = UninitializeKeyboard();
		if (FAILED(result_keyboard)) {
			Error("Keyboard uninitialization failed: %ld.", result_keyboard);
		}
	}

	HRESULT Keyboard::InitializeKeyboard(IDirectInput8 *di) {
		// Create and initialize an instance of a device based on a given globally unique identifier (GUID), 
		// and obtain an IDirectInputDevice8 Interface interface. 
		// 1. Reference to the GUID for the desired input device.
		// 2. Address of a variable to receive the IDirectInputDevice8 Interface interface pointer if successful.
		// 3. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or nullptr if the interface is not aggregated.
		const HRESULT result_keyboard_create = di->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
		if (FAILED(result_keyboard_create)) {
			Error("Keyboard device creation failed: %ld.", result_keyboard_create);
			return result_keyboard_create;
		}
		// Set the data format for the DirectInput device. 
		const HRESULT result_keyboard_format = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result_keyboard_format)) {
			Error("Setting data format for keyboard device failed: %ld.", result_keyboard_format);
			return result_keyboard_format;
		}
		// Establish the cooperative level for this instance of the device. 
		// The cooperative level determines how this instance of the device interacts 
		// with other instances of the device and the rest of the system. 
		const HRESULT result_keyboard_cooperative = m_keyboard->SetCooperativeLevel(m_hwindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result_keyboard_cooperative)) {
			Error("Setting cooperation level for keyboard device failed: %ld.", result_keyboard_cooperative);
			return result_keyboard_cooperative;
		}
		// Obtain access to the input device. 
		m_keyboard->Acquire();

		return S_OK;
	}

	HRESULT Keyboard::UninitializeKeyboard() {
		SAFE_RELEASE(m_keyboard);
		return S_OK;
	}

	void Keyboard::Update() {
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

		// Increment the press stamp.
		++m_press_stamp;
	}
}