#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering_state.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void RenderingState::Render() {
		m_device_context->OMSetBlendState(m_blend_state.Get(), nullptr, 0xFFFFFFFF);
		m_device_context->OMSetDepthStencilState(m_depth_stencil_state.Get(), 0);
		m_device_context->RSSetState(m_rasterizer_state.Get());
		m_device_context->PSSetSamplers(0, 1, m_sampler_state.GetAddressOf());
	}

	void RenderingState::SetDefaultRenderingState2D() {
		SetAlphaBlendState();
		SetDepthNoneDepthStencilState();
		SetCullCounterClockwiseRasterizerState();
		SetLinearClampSamplerState();
	}
	void RenderingState::SetDefaultRenderingState3D() {
		SetAlphaBlendState();
		SetDepthDefaultDepthStencilState();
		SetCullCounterClockwiseRasterizerState();
		SetLinearClampSamplerState();
	}

	//-------------------------------------------------------------------------
	// Blend state
	//-------------------------------------------------------------------------

	void RenderingState::SetBlendState(ComPtr< ID3D11BlendState > blend_state) {
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

	void RenderingState::SetDepthStencilState(ComPtr< ID3D11DepthStencilState > depth_stencil_state) {
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

	void RenderingState::SetRasterizerState(ComPtr< ID3D11RasterizerState > rasterizer_state) {
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

	void RenderingState::SetSamplerState(ComPtr< ID3D11SamplerState > sampler_state) {
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