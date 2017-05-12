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

	/**
	 A struct of rendering states containing a blend, depth stencil, rasterizer
	 and sampler state for rendering.
	 */
	struct RenderingState final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering state.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a rendering_state_cache is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		rendering_state_cache
						A pointer to the rendering state cache.
		 */
		explicit RenderingState(ID3D11Device2 *device, 
			ID3D11DeviceContext2 *device_context,
			RenderingStateCache *rendering_state_cache);
		
		/**
		 Constructs a rendering state from the given rendering state.

		 @param[in]		rendering_state
						A reference to the rendering state to copy.
		 */
		RenderingState(const RenderingState &rendering_state);

		/**
		 Constructs a rendering state by moving the given rendering state.

		 @param[in]		rendering_state
						A reference to the rendering state to move.
		 */
		RenderingState(RenderingState &&rendering_state);

		/**
		 Destructs this rendering state.
		 */
		~RenderingState();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given rendering state to this rendering state.

		 @param[in]		rendering_state
						A reference to the rendering state to copy.
		 @return		A reference to the copy of the given rendering state
						(i.e. this rendering state).
		 */
		RenderingState &operator=(const RenderingState &rendering_state) = delete;

		/**
		 Moves the given rendering state to this rendering state.

		 @param[in]		rendering_state
						A reference to the rendering state to move.
		 @return		A reference to the moved rendering state
						(i.e. this rendering state).
		 */
		RenderingState &operator=(RenderingState &&rendering_state) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this rendering state for rendering.

		 @pre			All states (blend, depth stencil, rasterizer, sampler) 
						of this rendering state must be set.
		 */
		void PrepareRendering();

		/**
		 Sets the states (blend, depth stencil, rasterizer, sampler)  
		 of this rendering state to the default rendering states for 2D rendering.

		 @throws		FormattedException
						Failed to set the states of this rendering state.
		 */
		void SetDefaultRenderingState2D();

		/**
		 Sets the states (blend, depth stencil, rasterizer, sampler)
		 of this rendering state to the default rendering states for 3D rendering.

		 @throws		FormattedException
						Failed to set the states of this rendering state.
		 */
		void SetDefaultRenderingState3D();

		//---------------------------------------------------------------------
		// Member Methods: Blend State
		//---------------------------------------------------------------------

		/**
		 Sets the blend state of this rendering state to
		 the given blend state.

		 @throws		FormattedException
						Failed to set the blend state
						of this rendering state.
		 */
		void SetBlendState(ID3D11BlendState *blend_state) noexcept;

		/**
		 Sets the blend state of this rendering state to
		 the an opaque blend state.

		 @throws		FormattedException
						Failed to set the blend state
						of this rendering state.
		 */
		void SetOpaqueBlendState();

		/**
		 Sets the blend state of this rendering state to
		 the an alpha blend state.

		 @throws		FormattedException
						Failed to set the blend state
						of this rendering state.
		 */
		void SetAlphaBlendState();

		/**
		 Sets the blend state of this rendering state to
		 the an additive blend state.

		 @throws		FormattedException
						Failed to set the blend state
						of this rendering state.
		 */
		void SetAdditiveBlendState();

		/**
		 Sets the blend state of this rendering state to
		 the a non-premultiplied blend state.

		 @throws		FormattedException
						Failed to set the blend state
						of this rendering state.
		 */
		void SetNonPremultipliedBlendState();
		
		/**
		 Returns the blend state of this rendering state.

		 @return		A pointer to the blend state
						of this rendering state.
		 */
		ID3D11BlendState *GetBlendState() const noexcept {
			return m_blend_state;
		}

		//---------------------------------------------------------------------
		// Member Methods: Depth Stencil State
		//---------------------------------------------------------------------

		/**
		 Sets the depth stencil state of this rendering state to
		 the given depth stencil state.

		 @throws		FormattedException
						Failed to set the depth stencil state
						of this rendering state.
		 */
		void SetDepthStencilState(ID3D11DepthStencilState *depth_stencil_state) noexcept;

		/**
		 Sets the depth stencil state of this rendering state to
		 the a no-depth stencil state.

		 @throws		FormattedException
						Failed to set the depth stencil state
						of this rendering state.
		 */
		void SetDepthNoneDepthStencilState();

		/**
		 Sets the depth stencil state of this rendering state to
		 the a default depth stencil state.

		 @throws		FormattedException
						Failed to set the depth stencil state
						of this rendering state.
		 */
		void SetDepthDefaultDepthStencilState();

		/**
		 Sets the depth stencil state of this rendering state to
		 the a read depth stencil state.

		 @throws		FormattedException
						Failed to set the depth stencil state
						of this rendering state.
		 */
		void SetDepthReadDepthStencilState();
		
		/**
		 Returns the depth stencil state of this rendering state.

		 @return		A pointer to the depth stencil state
						of this rendering state.
		 */
		ID3D11DepthStencilState *GetDepthStencilState() const noexcept {
			return m_depth_stencil_state;
		}

		//---------------------------------------------------------------------
		// Member Methods: Rasterizer State
		//---------------------------------------------------------------------

		/**
		 Sets the rasterizer state of this rendering state to
		 the given rasterizer state.

		 @throws		FormattedException
						Failed to set the rasterizer state
						of this rendering state.
		 */
		void SetRasterizerState(ID3D11RasterizerState *rasterizer_state) noexcept;

		/**
		 Sets the rasterizer state of this rendering state to
		 the a no-culling rasterizer state.

		 @throws		FormattedException
						Failed to set the rasterizer state
						of this rendering state.
		 */
		void SetCullNoneRasterizerState();

		/**
		 Sets the rasterizer state of this rendering state to
		 the a clockwise-culling rasterizer state.

		 @throws		FormattedException
						Failed to set the rasterizer state
						of this rendering state.
		 */
		void SetCullClockwiseRasterizerState();

		/**
		 Sets the rasterizer state of this rendering state to
		 the a counter-clockwise-culling rasterizer state.

		 @throws		FormattedException
						Failed to set the rasterizer state
						of this rendering state.
		 */
		void SetCullCounterClockwiseRasterizerState();

		/**
		 Sets the rasterizer state of this rendering state to
		 the a wireframe rasterizer state.

		 @throws		FormattedException
						Failed to set the rasterizer state
						of this rendering state.
		 */
		void SetWireframeRasterizerState();
		
		/**
		 Returns the rasterizer state of this rendering state.

		 @return		A pointer to the rasterizer state
						of this rendering state.
		 */
		ID3D11RasterizerState *GetRasterizerState() const noexcept {
			return m_rasterizer_state;
		}

		//-------------------------------------------------------------------------
		// Member Methods: Sampler State
		//-------------------------------------------------------------------------

		/**
		 Sets the sampler state of this rendering state to
		 the given sampler state.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetSamplerState(ID3D11SamplerState *sampler_state) noexcept;
		
		/**
		 Sets the sampler state of this rendering state to
		 a point sampling state with wrapping.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetPointWrapSamplerState();

		/**
		 Sets the sampler state of this rendering state to
		 a point sampling state with clamping.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetPointClampSamplerState();
		
		/**
		 Sets the sampler state of this rendering state to
		 a linear sampling state with wrapping.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetLinearWrapSamplerState();

		/**
		 Sets the sampler state of this rendering state to
		 a linear sampling state with clamping.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetLinearClampSamplerState();

		/**
		 Sets the sampler state of this rendering state to
		 an anisotropic sampling state with wrapping.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetAnisotropicWrapSamplerState();

		/**
		 Sets the sampler state of this rendering state to
		 an anisotropic sampling state with clamping.

		 @throws		FormattedException
						Failed to set the sampler state
						of this rendering state.
		 */
		void SetAnisotropicClampSamplerState();
		
		/**
		 Returns the sampler state of this rendering state.

		 @return		A pointer to the sampler state
						of this rendering state.
		 */
		ID3D11SamplerState *GetSamplerState() const noexcept {
			return m_sampler_state;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

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
