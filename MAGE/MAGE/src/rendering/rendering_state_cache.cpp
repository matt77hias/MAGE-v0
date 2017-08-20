#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	RenderingStateCache *RenderingStateCache::Get() noexcept {
		Assert(Renderer::Get());
		Assert(Renderer::Get()->GetRenderingStateCache());

		return Renderer::Get()->GetRenderingStateCache();
	}

	RenderingStateCache::RenderingStateCache(ID3D11Device2 *device, 
		ID3D11DeviceContext2 *device_context)
		: m_device(device), m_device_context(device_context),
		m_opaque_blend_state(), m_alpha_blend_state(), m_additive_blend_state(), m_non_premultiplied_blend_state(),
		m_depth_none_depth_stencil_state(), m_depth_default_depth_stencil_state(), m_depth_read_depth_stencil_state(),
		m_cull_none_rasterizer_state(), m_cull_clockwise_rasterizer_state(), m_cull_counter_clockwise_rasterizer_state(), m_wireframe_rasterizer_state(),
		m_point_wrap_sampler_state(), m_point_clamp_sampler_state(), m_linear_wrap_sampler_state(),
		m_linear_clamp_sampler_state(), m_anisotropic_wrap_sampler_state(), m_anisotropic_clamp_sampler_state(),
		m_mutex() {

		Assert(m_device);
		Assert(m_device_context);
	}

	RenderingStateCache::RenderingStateCache(RenderingStateCache &&rendering_state_cache) = default;

	RenderingStateCache::~RenderingStateCache() = default;

	//-------------------------------------------------------------------------
	// Blend states
	//-------------------------------------------------------------------------
	
	ID3D11BlendState *RenderingStateCache::GetOpaqueBlendState() {
		MutexLock lock(m_mutex);
		if (!m_opaque_blend_state) {
			const HRESULT result_create = CreateOpaqueBlendState(m_device, m_opaque_blend_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Opaque blend state creation failed: %08X.", result_create);
			}
		}
		return m_opaque_blend_state.Get();
	}
	
	ID3D11BlendState *RenderingStateCache::GetAlphaBlendState() {
		MutexLock lock(m_mutex);
		if (!m_alpha_blend_state) {
			const HRESULT result_create = CreateAlphaBlendState(m_device, m_alpha_blend_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Alpha blend state creation failed: %08X.", result_create);
			}
		}
		return m_alpha_blend_state.Get();

	}
	
	ID3D11BlendState *RenderingStateCache::GetAdditiveBlendState() {
		MutexLock lock(m_mutex);
		if (!m_additive_blend_state) {
			const HRESULT result_create = CreateAdditiveBlendState(m_device, m_additive_blend_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Additive blend state creation failed: %08X.", result_create);
			}
		}
		return m_additive_blend_state.Get();
	}
	
	ID3D11BlendState *RenderingStateCache::GetNonPremultipliedBlendState() {
		MutexLock lock(m_mutex);
		if (!m_non_premultiplied_blend_state) {
			const HRESULT result_create = CreateNonPremultipliedBlendState(m_device, m_non_premultiplied_blend_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Non-premultiplied blend state creation failed: %08X.", result_create);
			}
		}
		return m_non_premultiplied_blend_state.Get();
	}

	//-------------------------------------------------------------------------
	// Depth stencil states
	//-------------------------------------------------------------------------

	ID3D11DepthStencilState *RenderingStateCache::GetDepthNoneDepthStencilState() {
		MutexLock lock(m_mutex);
		if (!m_depth_none_depth_stencil_state) {
			const HRESULT result_create = CreateDepthNoneDepthStencilState(m_device, m_depth_none_depth_stencil_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Depth non depth stencil state creation failed: %08X.", result_create);
			}
		}
		return m_depth_none_depth_stencil_state.Get();
	}
	
	ID3D11DepthStencilState *RenderingStateCache::GetDepthDefaultDepthStencilState() {
		MutexLock lock(m_mutex);
		if (!m_depth_default_depth_stencil_state) {
			const HRESULT result_create = CreateDepthDefaultDepthStencilState(m_device, m_depth_default_depth_stencil_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Depth default depth stencil state creation failed: %08X.", result_create);
			}
		}
		return m_depth_default_depth_stencil_state.Get();
	}
	
	ID3D11DepthStencilState *RenderingStateCache::GetDepthReadDepthStencilState() {
		MutexLock lock(m_mutex);
		if (!m_depth_read_depth_stencil_state) {
			const HRESULT result_create = CreateDepthReadDepthStencilState(m_device, m_depth_read_depth_stencil_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Depth read depth stencil state creation failed: %08X.", result_create);
			}
		}
		return m_depth_read_depth_stencil_state.Get();
	}

	//-------------------------------------------------------------------------
	// Rasterizer states
	//-------------------------------------------------------------------------

	ID3D11RasterizerState *RenderingStateCache::GetCullNoneRasterizerState() {
		MutexLock lock(m_mutex);
		if (!m_cull_none_rasterizer_state) {
			const HRESULT result_create = CreateCullNoneRasterizerState(m_device, m_cull_none_rasterizer_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Cull none rasterizer state creation failed: %08X.", result_create);
			}
		}
		return m_cull_none_rasterizer_state.Get();
	}
	
	ID3D11RasterizerState *RenderingStateCache::GetCullClockwiseRasterizerState() {
		MutexLock lock(m_mutex);
		if (!m_cull_clockwise_rasterizer_state) {
			const HRESULT result_create = CreateCullClockwiseRasterizerState(m_device, m_cull_clockwise_rasterizer_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Cull clockwise rasterizer state creation failed: %08X.", result_create);
			}
		}
		return m_cull_clockwise_rasterizer_state.Get();
	}
	
	ID3D11RasterizerState *RenderingStateCache::GetCullCounterClockwiseRasterizerState() {
		MutexLock lock(m_mutex);
		if (!m_cull_counter_clockwise_rasterizer_state) {
			const HRESULT result_create = CreateCullCounterClockwiseRasterizerState(m_device, m_cull_counter_clockwise_rasterizer_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Cull counter clockwise state creation failed: %08X.", result_create);
			}
		}
		return m_cull_counter_clockwise_rasterizer_state.Get();
	}
	
	ID3D11RasterizerState *RenderingStateCache::GetWireframeRasterizerState() {
		MutexLock lock(m_mutex);
		if (!m_wireframe_rasterizer_state) {
			const HRESULT result_create = CreateWireframeRasterizerState(m_device, m_wireframe_rasterizer_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Wireframe rasterizer state creation failed: %08X.", result_create);
			}
		}
		return m_wireframe_rasterizer_state.Get();
	}

	//-------------------------------------------------------------------------
	// Sampler states
	//-------------------------------------------------------------------------

	ID3D11SamplerState *RenderingStateCache::GetPointWrapSamplerState() {
		MutexLock lock(m_mutex);
		if (!m_point_wrap_sampler_state) {
			const HRESULT result_create = CreatePointWrapSamplerState(m_device, m_point_wrap_sampler_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Point wrap sampler state creation failed: %08X.", result_create);
			}
		}
		return m_point_wrap_sampler_state.Get();
	}
	
	ID3D11SamplerState *RenderingStateCache::GetPointClampSamplerState() {
		MutexLock lock(m_mutex);
		if (!m_point_clamp_sampler_state) {
			const HRESULT result_create = CreatePointClampSamplerState(m_device, m_point_clamp_sampler_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Point clamp sampler state creation failed: %08X.", result_create);
			}
		}
		return m_point_clamp_sampler_state.Get();
	}
	
	ID3D11SamplerState *RenderingStateCache::GetLinearWrapSamplerState() {
		MutexLock lock(m_mutex);
		if (!m_linear_wrap_sampler_state) {
			const HRESULT result_create = CreateLinearWrapSamplerState(m_device, m_linear_wrap_sampler_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Linear wrap sampler state creation failed: %08X.", result_create);
			}
		}
		return m_linear_wrap_sampler_state.Get();
	}
	
	ID3D11SamplerState *RenderingStateCache::GetLinearClampSamplerState() {
		MutexLock lock(m_mutex);
		if (!m_linear_clamp_sampler_state) {
			const HRESULT result_create = CreateLinearClampSamplerState(m_device, m_linear_clamp_sampler_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Linear clamp sampler state creation failed: %08X.", result_create);
			}
		}
		return m_linear_clamp_sampler_state.Get();
	}
	
	ID3D11SamplerState *RenderingStateCache::GetAnisotropicWrapSamplerState() {
		MutexLock lock(m_mutex);
		if (!m_anisotropic_wrap_sampler_state) {
			const HRESULT result_create = CreateAnisotropicWrapSamplerState(m_device, m_anisotropic_wrap_sampler_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Anistropic wrap sampler state creation failed: %08X.", result_create);
			}
		}
		return m_anisotropic_wrap_sampler_state.Get();
	}
	
	ID3D11SamplerState *RenderingStateCache::GetAnisotropicClampSamplerState() {
		MutexLock lock(m_mutex);
		if (!m_anisotropic_clamp_sampler_state) {
			const HRESULT result_create = CreateAnisotropicClampSamplerState(m_device, m_anisotropic_clamp_sampler_state.ReleaseAndGetAddressOf());
			if (FAILED(result_create)) {
				throw FormattedException("Anistropic clamp sampler state creation failed: %08X.", result_create);
			}
		}
		return m_anisotropic_clamp_sampler_state.Get();
	}
}