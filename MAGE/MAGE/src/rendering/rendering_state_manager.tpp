#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindPointWrapSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PointWrap));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindPointClampSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PointClamp));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindPointMirrorSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PointMirror));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindLinearWrapSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::LinearWrap));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindLinearClampSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::LinearClamp));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindLinearMirrorSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::LinearMirror));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindAnisotropicWrapSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::AnisotropicWrap));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindAnisotropicClampSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::AnisotropicClamp));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindAnisotropicMirrorSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::AnisotropicMirror));
	}

	template< typename PipelineStageT >
	inline void RenderingStateManager::BindPCFSamplerState(
		ID3D11DeviceContext2 *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot,
			GetSamplerState(SamplerStateIndex::PCF));
	}
}