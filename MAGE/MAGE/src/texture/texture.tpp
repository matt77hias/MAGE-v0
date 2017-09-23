#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename PipelineStageT >
	inline void Texture::Bind(
		ID3D11DeviceContext2 *device_context, UINT slot) const noexcept {

		PipelineStageT::BindSRV(device_context, slot, Get());
	}
}