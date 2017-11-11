#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename PipelineStageT >
	inline void Texture::Bind(
		ID3D11DeviceContext4 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSRV(device_context, slot, Get());
	}
}