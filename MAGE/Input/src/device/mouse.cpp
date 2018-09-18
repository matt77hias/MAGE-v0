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
	// Mouse
	//-------------------------------------------------------------------------
	#pragma region

	Mouse::Mouse(NotNull< HWND > window, IDirectInput8& di)
		: m_window(window), 
		m_di(di), 
		m_mouse(), 
		m_position(), 
		m_delta(), 
		m_delta_wheel(0), 
		m_button_states{} {

		InitializeMouse();
	}

	Mouse::Mouse(Mouse&& mouse) noexcept = default;

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
				= m_di.CreateDevice(GUID_SysMouse, 
									m_mouse.ReleaseAndGetAddressOf(), 
									nullptr);
			ThrowIfFailed(result,
						  "Failed to create mouse device: {:08X}.",
						  result);
		}
		
		// Set the data format for the DirectInput device.
		{
			const HRESULT result = m_mouse->SetDataFormat(&c_dfDIMouse2);
			ThrowIfFailed(result,
						  "Failed to set data format for mouse device: {:08X}.",
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
						  "Failed to set cooperation level for mouse device: {:08X}.",
						  result);
		}
		
		// Obtain access to the input device. 
		m_mouse->Acquire();
	}

	void Mouse::Update() noexcept {
		DIMOUSESTATE2 mouse_state = {};
		
		// Poll the mouse until it succeeds or returns an unknown error.
		while (true) {
			
			// Retrieves data from polled objects on a DirectInput device.
			m_mouse->Poll();

			// Retrieves immediate data from the device. 
			const HRESULT result = m_mouse->GetDeviceState(sizeof(mouse_state),
				                                           &mouse_state);
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
		
		// Updates the mouse position.
		m_position = GetMousePosition(m_window);

		// Update the mouse deltas.
		m_delta[0u]   = static_cast< S32 >(mouse_state.lX);
		m_delta[1u]   = static_cast< S32 >(mouse_state.lY);
		m_delta_wheel = static_cast< S32 >(mouse_state.lZ);

		// Update the button states.
		for (std::size_t i = 0u; i < std::size(mouse_state.rgbButtons); ++i) {
			const bool active = mouse_state.rgbButtons[i] & 0x80u;
			m_button_states[2u*i]    = (active != m_button_states[2u*i+1u]);
			m_button_states[2u*i+1u] = active;
		}
	}

	#pragma endregion
}
