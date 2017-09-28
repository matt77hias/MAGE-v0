#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindPointWrapSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PointWrap));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindPointClampSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PointClamp));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindPointMirrorSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PointMirror));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindLinearWrapSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::LinearWrap));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindLinearClampSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::LinearClamp));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindLinearMirrorSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::LinearMirror));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindAnisotropicWrapSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::AnisotropicWrap));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindAnisotropicClampSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::AnisotropicClamp));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindAnisotropicMirrorSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::AnisotropicMirror));
	}

	template< typename PipelineStageT >
	inline void RenderingStateCache::BindPCFSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PCF));
	}
}