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

	struct RenderingStateCache final {

	public:

		explicit RenderingStateCache(ID3D11Device2 *device)
			: m_device(device), 
			m_opaque_blend_state(), m_alpha_blend_state(), m_additive_blend_state(), m_non_premultiplied_blend_state(),
			m_depth_none_depth_stencil_state(), m_depth_default_depth_stencil_state(), m_depth_read_depth_stencil_state(),
			m_cull_none_rasterizer_state(), m_cull_clockwise_rasterizer_state(), m_cull_counter_clockwise_rasterizer_state(), m_wireframe_rasterizer_state(),
			m_point_wrap_sampler_state(), m_point_clamp_sampler_state(), m_linear_wrap_sampler_state(), 
			m_linear_clamp_sampler_state(), m_anisotropic_wrap_sampler_state(), m_anisotropic_clamp_sampler_state(),
			m_mutex() {}
		RenderingStateCache(const RenderingStateCache &rendering_state_cache) = delete;
		RenderingStateCache(RenderingStateCache &&rendering_state_cache) = default;
		~RenderingStateCache() = default;

		RenderingStateCache &operator=(const RenderingStateCache &rendering_state_cache) = delete;
		RenderingStateCache &operator=(RenderingStateCache &&rendering_state_cache) = delete;

		//---------------------------------------------------------------------
		// Blend states
		//---------------------------------------------------------------------

		ID3D11BlendState *GetOpaqueBlendState();
		ID3D11BlendState *GetAlphaBlendState();
		ID3D11BlendState *GetAdditiveBlendState();
		ID3D11BlendState *GetNonPremultipliedBlendState();

		//---------------------------------------------------------------------
		// Depth stencil states
		//---------------------------------------------------------------------

		ID3D11DepthStencilState *GetDepthNoneDepthStencilState();
		ID3D11DepthStencilState *GetDepthDefaultDepthStencilState();
		ID3D11DepthStencilState *GetDepthReadDepthStencilState();

		//-------------------------------------------------------------------------
		// Rasterizer states
		//-------------------------------------------------------------------------

		ID3D11RasterizerState *GetCullNoneRasterizerState();
		ID3D11RasterizerState *GetCullClockwiseRasterizerState();
		ID3D11RasterizerState *GetCullCounterClockwiseRasterizerState();
		ID3D11RasterizerState *GetWireframeRasterizerState();

		//-------------------------------------------------------------------------
		// Sampler states
		//-------------------------------------------------------------------------

		ID3D11SamplerState *GetPointWrapSamplerState();
		ID3D11SamplerState *GetPointClampSamplerState();
		ID3D11SamplerState *GetLinearWrapSamplerState();
		ID3D11SamplerState *GetLinearClampSamplerState();
		ID3D11SamplerState *GetAnisotropicWrapSamplerState();
		ID3D11SamplerState *GetAnisotropicClampSamplerState();

	private:

		/**
		 The device of this rendering state.
		 */
		ID3D11Device2 * const m_device;

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
