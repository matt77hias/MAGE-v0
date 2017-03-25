#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_state.hpp"
#include "rendering\rendering_state_cache.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline RenderingStateCache &GetRenderingStateCache() {
		return RenderingStateCache(nullptr); //@TODO
	}

	RenderingState::RenderingState(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context)
		: m_device(device), m_device_context(device_context) {
		
		SetAlphaBlendState();
		SetDepthNoneDepthStencilState();
		SetCullCounterClockwiseRasterizerState();
		SetLinearClampSamplerState();
	}
	
	void RenderingState::Render() {
		m_device_context->OMSetBlendState(m_blend_state.Get(), nullptr, 0xFFFFFFFF);
		m_device_context->OMSetDepthStencilState(m_depth_stencil_state.Get(), 0);
		m_device_context->RSSetState(m_rasterizer_state.Get());
		m_device_context->PSSetSamplers(0, 1, m_sampler_state.GetAddressOf());
	}

	//-------------------------------------------------------------------------
	// Blend state
	//-------------------------------------------------------------------------

	void RenderingState::SetBlendState(ComPtr< ID3D11BlendState > blend_state) {
		Assert(blend_state);
		m_blend_state = blend_state;
	}
	void RenderingState::SetOpaqueBlendState() {
		m_blend_state = GetRenderingStateCache().GetOpaqueBlendState();
	}
	void RenderingState::SetAlphaBlendState() {
		m_blend_state = GetRenderingStateCache().GetAlphaBlendState();
	}
	void RenderingState::SetAdditiveBlendState() {
		m_blend_state = GetRenderingStateCache().GetAdditiveBlendState();
	}
	void RenderingState::SetNonPremultipliedBlendState() {
		m_blend_state = GetRenderingStateCache().GetNonPremultipliedBlendState();
	}

	//-------------------------------------------------------------------------
	// Depth stencil state
	//-------------------------------------------------------------------------

	void RenderingState::SetDepthStencilState(ComPtr< ID3D11DepthStencilState > depth_stencil_state) {
		Assert(depth_stencil_state);
		m_depth_stencil_state = depth_stencil_state;
	}
	void RenderingState::SetDepthNoneDepthStencilState() {
		m_depth_stencil_state = GetRenderingStateCache().GetDepthNoneDepthStencilState();
	}
	void RenderingState::SetDepthDefaultDepthStencilState() {
		m_depth_stencil_state = GetRenderingStateCache().GetDepthDefaultDepthStencilState();
	}
	void RenderingState::SetDepthReadDepthStencilState() {
		m_depth_stencil_state = GetRenderingStateCache().GetDepthReadDepthStencilState();
	}

	//-------------------------------------------------------------------------
	// Rasterizer state
	//-------------------------------------------------------------------------

	void RenderingState::SetRasterizerState(ComPtr< ID3D11RasterizerState > rasterizer_state) {
		Assert(rasterizer_state);
		m_rasterizer_state = rasterizer_state;
	}
	void RenderingState::SetCullNoneRasterizerState() {
		m_rasterizer_state = GetRenderingStateCache().GetCullNoneRasterizerState();
	}
	void RenderingState::SetCullClockwiseRasterizerState() {
		m_rasterizer_state = GetRenderingStateCache().GetCullClockwiseRasterizerState();
	}
	void RenderingState::SetCullCounterClockwiseRasterizerState() {
		m_rasterizer_state = GetRenderingStateCache().GetCullCounterClockwiseRasterizerState();
	}
	void RenderingState::SetWireframeRasterizerState() {
		m_rasterizer_state = GetRenderingStateCache().GetWireframeRasterizerState();
	}

	//-------------------------------------------------------------------------
	// Sampler state
	//-------------------------------------------------------------------------

	void RenderingState::SetSamplerState(ComPtr< ID3D11SamplerState > sampler_state) {
		Assert(sampler_state);
		m_sampler_state = sampler_state;
	}
	void RenderingState::SetPointWrapSamplerState() {
		m_sampler_state = GetRenderingStateCache().GetPointWrapSamplerState();
	}
	void RenderingState::SetPointClampSamplerState() {
		m_sampler_state = GetRenderingStateCache().GetPointClampSamplerState();
	}
	void RenderingState::SetLinearWrapSamplerState() {
		m_sampler_state = GetRenderingStateCache().GetLinearWrapSamplerState();
	}
	void RenderingState::SetLinearClampSamplerState() {
		m_sampler_state = GetRenderingStateCache().GetLinearClampSamplerState();
	}
	void RenderingState::SetAnisotropicWrapSamplerState() {
		m_sampler_state = GetRenderingStateCache().GetAnisotropicWrapSamplerState();
	}
	void RenderingState::SetAnisotropicClampSamplerState() {
		m_sampler_state = GetRenderingStateCache().GetAnisotropicClampSamplerState();
	}
}