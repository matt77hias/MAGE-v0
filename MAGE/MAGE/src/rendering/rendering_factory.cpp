//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT CreateLinearSamplerState(ComPtr< ID3D11Device2 > device, ID3D11SamplerState **sampler_state) {
		// Create the sample state.
		D3D11_SAMPLER_DESC sampler_desc;
		ZeroMemory(&sampler_desc, sizeof(sampler_desc));
		sampler_desc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampler_desc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampler_desc.MinLOD         = 0;
		sampler_desc.MaxLOD         = D3D11_FLOAT32_MAX;

		return device->CreateSamplerState(&sampler_desc, sampler_state);
	}
}