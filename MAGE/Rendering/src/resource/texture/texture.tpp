#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename PipelineStageT >
	inline void Texture
		::Bind(ID3D11DeviceContext& device_context, U32 slot) const noexcept {

		PipelineStageT::BindSRV(device_context, slot, Get());
	}
}