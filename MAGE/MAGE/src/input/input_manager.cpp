//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const InputManager *InputManager::Get() noexcept {
		Assert(Engine::Get());

		return Engine::Get()->GetInputManager();
	}

	InputManager::InputManager(HWND window) 
		: m_window(window), m_di(), m_keyboard(), m_mouse() {

		Assert(m_window);

		InitializeDI();
		InitializeInputSystems();
	}

	InputManager::InputManager(InputManager &&manager) noexcept = default;

	InputManager::~InputManager() = default;

	void InputManager::InitializeDI() {
		// Create a DirectInput interface.
		// 1. Instance handle to the application that is creating the 
		//    DirectInput object.
		// 2. Version number of DirectInput for which the application is 
		//    designed.
		// 3. Unique identifier of the desired interface. Passing 
		//    IID_IDirectInput8 selects the ANSI or Unicode version of the 
		//    interface.
		// 4. Address of a pointer to a variable to receive the IDirectInput8 
		//    interface pointer if successful.
		// 5. Pointer to the address of the controlling object's IUnknown 
		//    interface for COM aggregation, or nullptr if the interface is 
		//    not aggregated.
		const HRESULT result = DirectInput8Create(GetModuleHandle(nullptr), 
			                                      DIRECTINPUT_VERSION, 
			                                      IID_IDirectInput8, 
			                                      (void **)m_di.ReleaseAndGetAddressOf(), 
			                                      nullptr);
		ThrowIfFailed(result, "DirectInput initialization failed: %ld", result);
	}

	void InputManager::InitializeInputSystems() {
		m_keyboard = MakeUnique< Keyboard >(m_window, m_di.Get());
		m_mouse    = MakeUnique< Mouse >(   m_window, m_di.Get());
	}
}