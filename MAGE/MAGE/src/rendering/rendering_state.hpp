#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_state_cache.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct RenderingState final {

	public:

		explicit RenderingState(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, RenderingStateCache *rendering_state_cache)
			: m_device(device), m_device_context(device_context), m_rendering_state_cache(rendering_state_cache) {}
		RenderingState(const RenderingState &rendering_state) = default;
		RenderingState(RenderingState &&rendering_state) = default;
		~RenderingState() = default;

		void Render();

		void SetDefaultRenderingState2D();
		void SetDefaultRenderingState3D();

		//---------------------------------------------------------------------
		// Blend state
		//---------------------------------------------------------------------

		void SetBlendState(ID3D11BlendState *blend_state);
		void SetOpaqueBlendState();
		void SetAlphaBlendState();
		void SetAdditiveBlendState();
		void SetNonPremultipliedBlendState();
		ID3D11BlendState *GetBlendState() const {
			return m_blend_state;
		}

		//---------------------------------------------------------------------
		// Depth stencil state
		//---------------------------------------------------------------------

		void SetDepthStencilState(ID3D11DepthStencilState *depth_stencil_state);
		void SetDepthNoneDepthStencilState();
		void SetDepthDefaultDepthStencilState();
		void SetDepthReadDepthStencilState();
		ID3D11DepthStencilState *GetDepthStencilState() const {
			return m_depth_stencil_state;
		}

		//---------------------------------------------------------------------
		// Rasterizer state
		//---------------------------------------------------------------------

		void SetRasterizerState(ID3D11RasterizerState *rasterizer_state);
		void SetCullNoneRasterizerState();
		void SetCullClockwiseRasterizerState();
		void SetCullCounterClockwiseRasterizerState();
		void SetWireframeRasterizerState();
		ID3D11RasterizerState *GetRasterizerState() const {
			return m_rasterizer_state;
		}

		//-------------------------------------------------------------------------
		// Sampler state
		//-------------------------------------------------------------------------

		void SetSamplerState(ID3D11SamplerState *sampler_state);
		void SetPointWrapSamplerState();
		void SetPointClampSamplerState();
		void SetLinearWrapSamplerState();
		void SetLinearClampSamplerState();
		void SetAnisotropicWrapSamplerState();
		void SetAnisotropicClampSamplerState();
		ID3D11SamplerState *GetSamplerState() const {
			return m_sampler_state;
		}

	private:

		RenderingState &operator=(const RenderingState &rendering_state) = delete;
		RenderingState &operator=(RenderingState &&rendering_state) = delete;

		/**
		 A pointer to the device of this rendering state.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this rendering state.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the rendering state cache of this rendering state.
		 */
		RenderingStateCache * const m_rendering_state_cache;

		/**
		 A pointer to the blend state of this rendering state.
		 */
		ID3D11BlendState *m_blend_state;

		/**
		 A pointer to the depth stencil state of this rendering state.
		 */
		ID3D11DepthStencilState *m_depth_stencil_state;

		/**
		 A pointer to the rasterizer state of this rendering state.
		 */
		ID3D11RasterizerState *m_rasterizer_state;

		/**
		 A pointer to the sampler state of this rendering state.
		 */
		ID3D11SamplerState *m_sampler_state;
	};
}
