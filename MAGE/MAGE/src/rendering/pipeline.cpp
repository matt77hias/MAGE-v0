//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	ID3D11Device2 *GetRenderingDevice() noexcept {
		Assert(Renderer::Get());
		Assert(Renderer::Get()->GetDevice());

		return Renderer::Get()->GetDevice();
	}

	ID3D11DeviceContext2 *GetRenderingDeviceContext() noexcept {
		Assert(Renderer::Get());
		Assert(Renderer::Get()->GetDeviceContext());

		return Renderer::Get()->GetDeviceContext();
	}
}
