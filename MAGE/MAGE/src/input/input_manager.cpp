//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\input_manager.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	InputManager::InputManager(HWND hwindow) 
		: m_hwindow(hwindow), m_di(), m_keyboard(), m_mouse() {

		InitializeDI();
		InitializeInputSystems();
	}

	void InputManager::InitializeDI() {
		// Create a DirectInput interface.
		// 1. Instance handle to the application that is creating the DirectInput object.
		// 2. Version number of DirectInput for which the application is designed.
		// 3. Unique identifier of the desired interface. Passing IID_IDirectInput8 selects the ANSI or Unicode version of the interface.
		// 4. Address of a pointer to a variable to receive the IDirectInput8 interface pointer if successful.
		// 5. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or nullptr if the interface is not aggregated.
		const HRESULT result_di = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)m_di.ReleaseAndGetAddressOf(), nullptr);
		if (FAILED(result_di)) {
			throw FormattedException("DirectInput initialization failed: %ld", result_di);
		}
	}

	void InputManager::InitializeInputSystems() {
		m_keyboard = make_unique< Keyboard >(m_hwindow, m_di.Get());
		m_mouse = make_unique< Mouse >(m_hwindow, m_di.Get());
	}
}