//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "input\input_manager.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	InputManager::InputManager(HWND hwindow) 
		: Loadable(), m_hwindow(hwindow) {

		const HRESULT result_di = InitializeDI();
		if (FAILED(result_di)) {
			Error("DirectInput initialization failed: %ld", result_di);
			return;
		}
		const HRESULT result_input_systems = InitializeInputSystems();
		if (FAILED(result_input_systems)) {
			Error("Input systems initialization failed: %08X.", result_input_systems);
			return;
		}

		SetLoaded();
	}

	HRESULT InputManager::InitializeDI() {
		// Create a DirectInput interface.
		// 1. Instance handle to the application that is creating the DirectInput object.
		// 2. Version number of DirectInput for which the application is designed.
		// 3. Unique identifier of the desired interface. Passing IID_IDirectInput8 selects the ANSI or Unicode version of the interface.
		// 4. Address of a pointer to a variable to receive the IDirectInput8 interface pointer if successful.
		// 5. Pointer to the address of the controlling object's IUnknown interface for COM aggregation, or nullptr if the interface is not aggregated.
		return DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)m_di.ReleaseAndGetAddressOf(), nullptr);
	}

	HRESULT InputManager::InitializeInputSystems() {
		m_keyboard = make_unique< Keyboard >(m_hwindow, m_di);
		if (!m_keyboard->IsLoaded()) {
			Error("Keyboard creation failed.");
			return E_FAIL;
		}
		m_mouse = make_unique< Mouse >(m_hwindow, m_di);
		if (!m_mouse->IsLoaded()) {
			Error("Mouse creation failed.");
			return E_FAIL;
		}
		
		return S_OK;
	}

	void InputManager::Update() {
		m_keyboard->Update();
		m_mouse->Update();
	}
}