//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	ID3D11Device2 *GetDevice() noexcept {
		Assert(Renderer::Get());

		return Renderer::Get()->GetDevice();
	}

	ID3D11DeviceContext2 *GetImmediateDeviceContext() noexcept {
		Assert(Renderer::Get());

		return Renderer::Get()->GetDeviceContext();
	}
}
