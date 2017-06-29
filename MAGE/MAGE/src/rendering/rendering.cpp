//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Integrated + Dedicated GPU on notebooks  
//-----------------------------------------------------------------------------
#pragma region

/**
 NVIDIA Optimus enablement

 @pre NVIDIA Control Panel > Preferred graphics processor > "Auto-select"
 */
extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

/**
 AMD "Optimus" enablement
 */
extern "C" {
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	ID3D11Device2 *GetRenderingDevice() noexcept {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);

		return renderer->GetDevice();
	}

	ID3D11DeviceContext2 *GetRenderingDeviceContext() noexcept {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		const Renderer * const renderer = g_engine->GetRenderer();
		Assert(renderer);

		return renderer->GetDeviceContext();
	}
}
