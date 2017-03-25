#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "parallel\lock.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct RenderingStateCache {

	public:

		RenderingStateCache(ComPtr< ID3D11Device2 > device)
			: m_device(device) {}
		RenderingStateCache(const RenderingStateCache &rendering_state_cache) = default;
		RenderingStateCache(RenderingStateCache &&rendering_state_cache) = default;
		~RenderingStateCache() = default;

		RenderingStateCache &operator=(const RenderingStateCache &rendering_state_cache) = default;
		RenderingStateCache &operator=(RenderingStateCache &&rendering_state_cache) = default;

		//---------------------------------------------------------------------
		// Blend states
		//---------------------------------------------------------------------

		ComPtr< ID3D11BlendState > GetOpaqueBlendState();
		ComPtr< ID3D11BlendState > GetAlphaBlendState();
		ComPtr< ID3D11BlendState > GetAdditiveBlendState();
		ComPtr< ID3D11BlendState > GetNonPremultipliedBlendState();

		//---------------------------------------------------------------------
		// Depth stencil states
		//---------------------------------------------------------------------

		ComPtr< ID3D11DepthStencilState > GetDepthNoneDepthStencilState();
		ComPtr< ID3D11DepthStencilState > GetDepthDefaultDepthStencilState();
		ComPtr< ID3D11DepthStencilState > GetDepthReadDepthStencilState();

		//-------------------------------------------------------------------------
		// Rasterizer states
		//-------------------------------------------------------------------------

		ComPtr< ID3D11RasterizerState > GetCullNoneRasterizerState();
		ComPtr< ID3D11RasterizerState > GetCullClockwiseRasterizerState();
		ComPtr< ID3D11RasterizerState > GetCullCounterClockwiseRasterizerState();
		ComPtr< ID3D11RasterizerState > GetWireframeRasterizerState();

		//-------------------------------------------------------------------------
		// Sampler states
		//-------------------------------------------------------------------------

		ComPtr< ID3D11SamplerState > GetPointWrapSamplerState();
		ComPtr< ID3D11SamplerState > GetPointClampSamplerState();
		ComPtr< ID3D11SamplerState > GetLinearWrapSamplerState();
		ComPtr< ID3D11SamplerState > GetLinearClampSamplerState();
		ComPtr< ID3D11SamplerState > GetAnisotropicWrapSamplerState();
		ComPtr< ID3D11SamplerState > GetAnisotropicClampSamplerState();

	private:

		/**
		 The device of this rendering state.
		 */
		ComPtr< ID3D11Device2 > m_device;

		ComPtr< ID3D11BlendState > m_opaque_blend_state;
		ComPtr< ID3D11BlendState > m_alpha_blend_state;
		ComPtr< ID3D11BlendState > m_additive_blend_state;
		ComPtr< ID3D11BlendState > m_non_premultiplied_blend_state;

		ComPtr< ID3D11DepthStencilState > m_depth_none_depth_stencil_state;
		ComPtr< ID3D11DepthStencilState > m_depth_default_depth_stencil_state;
		ComPtr< ID3D11DepthStencilState > m_depth_read_depth_stencil_state;

		ComPtr< ID3D11RasterizerState > m_cull_none_rasterizer_state;
		ComPtr< ID3D11RasterizerState > m_cull_clockwise_rasterizer_state;
		ComPtr< ID3D11RasterizerState > m_cull_counter_clockwise_rasterizer_state;
		ComPtr< ID3D11RasterizerState > m_wireframe_rasterizer_state;

		ComPtr< ID3D11SamplerState > m_point_wrap_sampler_state;
		ComPtr< ID3D11SamplerState > m_point_clamp_sampler_state;
		ComPtr< ID3D11SamplerState > m_linear_wrap_sampler_state;
		ComPtr< ID3D11SamplerState > m_linear_clamp_sampler_state;
		ComPtr< ID3D11SamplerState > m_anisotropic_wrap_sampler_state;
		ComPtr< ID3D11SamplerState > m_anisotropic_clamp_sampler_state;

		Mutex m_mutex;
	};
}
