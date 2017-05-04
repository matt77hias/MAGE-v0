#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering_state.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	RenderingState::RenderingState(ID3D11Device2 *device, 
		ID3D11DeviceContext2 *device_context, 
		RenderingStateCache *rendering_state_cache)
		: m_device(device), 
		m_device_context(device_context), 
		m_rendering_state_cache(rendering_state_cache) {

		Assert(device);
		Assert(device_context);
		Assert(rendering_state_cache);
	}

	RenderingState::RenderingState(const RenderingState &rendering_state) = default;

	RenderingState::RenderingState(RenderingState &&rendering_state) = default;

	RenderingState::~RenderingState() = default;

	void RenderingState::PrepareRendering() {
		m_device_context->OMSetBlendState(m_blend_state, nullptr, 0xFFFFFFFF);
		m_device_context->OMSetDepthStencilState(m_depth_stencil_state, 0);
		m_device_context->RSSetState(m_rasterizer_state);
		m_device_context->PSSetSamplers(0, 1, &m_sampler_state);
	}

	void RenderingState::SetDefaultRenderingState2D() {
		SetAlphaBlendState();
		SetDepthNoneDepthStencilState();
		SetCullCounterClockwiseRasterizerState();
		SetLinearWrapSamplerState();
	}
	
	void RenderingState::SetDefaultRenderingState3D() {
		SetAlphaBlendState();
		SetDepthDefaultDepthStencilState();
		SetCullCounterClockwiseRasterizerState();
		SetLinearWrapSamplerState();
	}

	//-------------------------------------------------------------------------
	// Blend state
	//-------------------------------------------------------------------------

	void RenderingState::SetBlendState(ID3D11BlendState *blend_state) {
		Assert(blend_state);
		m_blend_state = blend_state;
	}
	
	void RenderingState::SetOpaqueBlendState() {
		m_blend_state = m_rendering_state_cache->GetOpaqueBlendState();
	}
	
	void RenderingState::SetAlphaBlendState() {
		m_blend_state = m_rendering_state_cache->GetAlphaBlendState();
	}
	
	void RenderingState::SetAdditiveBlendState() {
		m_blend_state = m_rendering_state_cache->GetAdditiveBlendState();
	}
	
	void RenderingState::SetNonPremultipliedBlendState() {
		m_blend_state = m_rendering_state_cache->GetNonPremultipliedBlendState();
	}

	//-------------------------------------------------------------------------
	// Depth stencil state
	//-------------------------------------------------------------------------

	void RenderingState::SetDepthStencilState(ID3D11DepthStencilState *depth_stencil_state) {
		Assert(depth_stencil_state);
		m_depth_stencil_state = depth_stencil_state;
	}
	
	void RenderingState::SetDepthNoneDepthStencilState() {
		m_depth_stencil_state = m_rendering_state_cache->GetDepthNoneDepthStencilState();
	}
	
	void RenderingState::SetDepthDefaultDepthStencilState() {
		m_depth_stencil_state = m_rendering_state_cache->GetDepthDefaultDepthStencilState();
	}
	
	void RenderingState::SetDepthReadDepthStencilState() {
		m_depth_stencil_state = m_rendering_state_cache->GetDepthReadDepthStencilState();
	}

	//-------------------------------------------------------------------------
	// Rasterizer state
	//-------------------------------------------------------------------------

	void RenderingState::SetRasterizerState(ID3D11RasterizerState *rasterizer_state) {
		Assert(rasterizer_state);
		m_rasterizer_state = rasterizer_state;
	}
	
	void RenderingState::SetCullNoneRasterizerState() {
		m_rasterizer_state = m_rendering_state_cache->GetCullNoneRasterizerState();
	}
	
	void RenderingState::SetCullClockwiseRasterizerState() {
		m_rasterizer_state = m_rendering_state_cache->GetCullClockwiseRasterizerState();
	}
	
	void RenderingState::SetCullCounterClockwiseRasterizerState() {
		m_rasterizer_state = m_rendering_state_cache->GetCullCounterClockwiseRasterizerState();
	}
	
	void RenderingState::SetWireframeRasterizerState() {
		m_rasterizer_state = m_rendering_state_cache->GetWireframeRasterizerState();
	}

	//-------------------------------------------------------------------------
	// Sampler state
	//-------------------------------------------------------------------------

	void RenderingState::SetSamplerState(ID3D11SamplerState *sampler_state) {
		Assert(sampler_state);
		m_sampler_state = sampler_state;
	}
	
	void RenderingState::SetPointWrapSamplerState() {
		m_sampler_state = m_rendering_state_cache->GetPointWrapSamplerState();
	}
	
	void RenderingState::SetPointClampSamplerState() {
		m_sampler_state = m_rendering_state_cache->GetPointClampSamplerState();
	}
	
	void RenderingState::SetLinearWrapSamplerState() {
		m_sampler_state = m_rendering_state_cache->GetLinearWrapSamplerState();
	}
	
	void RenderingState::SetLinearClampSamplerState() {
		m_sampler_state = m_rendering_state_cache->GetLinearClampSamplerState();
	}
	
	void RenderingState::SetAnisotropicWrapSamplerState() {
		m_sampler_state = m_rendering_state_cache->GetAnisotropicWrapSamplerState();
	}
	
	void RenderingState::SetAnisotropicClampSamplerState() {
		m_sampler_state = m_rendering_state_cache->GetAnisotropicClampSamplerState();
	}
}