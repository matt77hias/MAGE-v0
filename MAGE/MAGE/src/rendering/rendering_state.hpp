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

		RenderingState(ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context, SharedPtr< RenderingStateCache > rendering_state_cache)
			: m_device(device), m_device_context(device_context), m_rendering_state_cache(rendering_state_cache) {}
		RenderingState(const RenderingState &rendering_state) = default;
		RenderingState(RenderingState &&rendering_state) = default;
		~RenderingState() = default;

		RenderingState &operator=(const RenderingState &rendering_state) = default;
		RenderingState &operator=(RenderingState &&rendering_state) = default;

		void Render();

		void SetDefaultRenderingState2D();
		void SetDefaultRenderingState3D();

		//---------------------------------------------------------------------
		// Blend state
		//---------------------------------------------------------------------

		void SetBlendState(ComPtr< ID3D11BlendState > blend_state);
		void SetOpaqueBlendState();
		void SetAlphaBlendState();
		void SetAdditiveBlendState();
		void SetNonPremultipliedBlendState();
		ID3D11BlendState &GetBlendState() const {
			return *m_blend_state.Get();
		}

		//---------------------------------------------------------------------
		// Depth stencil state
		//---------------------------------------------------------------------

		void SetDepthStencilState(ComPtr< ID3D11DepthStencilState > depth_stencil_state);
		void SetDepthNoneDepthStencilState();
		void SetDepthDefaultDepthStencilState();
		void SetDepthReadDepthStencilState();
		ID3D11DepthStencilState &GetDepthStencilState() const {
			return *m_depth_stencil_state.Get();
		}

		//---------------------------------------------------------------------
		// Rasterizer state
		//---------------------------------------------------------------------

		void SetRasterizerState(ComPtr< ID3D11RasterizerState > rasterizer_state);
		void SetCullNoneRasterizerState();
		void SetCullClockwiseRasterizerState();
		void SetCullCounterClockwiseRasterizerState();
		void SetWireframeRasterizerState();
		ID3D11RasterizerState &GetRasterizerState() const {
			return *m_rasterizer_state.Get();
		}

		//-------------------------------------------------------------------------
		// Sampler state
		//-------------------------------------------------------------------------

		void SetSamplerState(ComPtr< ID3D11SamplerState > sampler_state);
		void SetPointWrapSamplerState();
		void SetPointClampSamplerState();
		void SetLinearWrapSamplerState();
		void SetLinearClampSamplerState();
		void SetAnisotropicWrapSamplerState();
		void SetAnisotropicClampSamplerState();
		ID3D11SamplerState &GetSamplerState() const {
			return *m_sampler_state.Get();
		}

	private:

		/**
		 The device of this rendering state.
		 */
		ComPtr< ID3D11Device2 > m_device;

		/**
		 The device context of this rendering state.
		 */
		ComPtr< ID3D11DeviceContext2 > m_device_context;

		/**
		 The rendering state cache of this rendering state.
		 */
		SharedPtr< RenderingStateCache > m_rendering_state_cache;

		/**
		 The blend state of this rendering state.
		 */
		ComPtr< ID3D11BlendState > m_blend_state;

		/**
		 The depth stencil state of this rendering state.
		 */
		ComPtr< ID3D11DepthStencilState > m_depth_stencil_state;

		/**
		 The rasterizer state of this rendering state.
		 */
		ComPtr< ID3D11RasterizerState > m_rasterizer_state;

		/**
		 The sampler state of this rendering state.
		 */
		ComPtr< ID3D11SamplerState > m_sampler_state;
	};
}
