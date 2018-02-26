#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename PipelineStageT >
	inline void StateManager::BindPointWrapSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::PointWrap));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindPointClampSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::PointClamp));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindPointMirrorSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::PointMirror));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindLinearWrapSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::LinearWrap));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindLinearClampSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::LinearClamp));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindLinearMirrorSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::LinearMirror));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindAnisotropicWrapSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::AnisotropicWrap));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindAnisotropicClampSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::AnisotropicClamp));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindAnisotropicMirrorSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::AnisotropicMirror));
	}

	template< typename PipelineStageT >
	inline void StateManager::BindPCFSamplerState(
		ID3D11DeviceContext *device_context, U32 slot) const noexcept {

		PipelineStageT::BindSampler(device_context, slot, 
									Get(SamplerStateIndex::PCF));
	}
}