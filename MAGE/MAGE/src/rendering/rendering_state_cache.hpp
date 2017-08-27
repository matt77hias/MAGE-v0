#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\pipeline.hpp"
#include "parallel\lock.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of rendering state caches.
	 */
	struct RenderingStateCache final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the renderer state cache associated with the current engine.

		 @pre			The renderer associated with the 
						current engine must be loaded.
		 @return		A pointer to the renderer state cache associated
						with the current engine.
		 */
		static RenderingStateCache *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering state cache.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 */
		explicit RenderingStateCache(ID3D11Device2 *device);

		/**
		 Constructs a rendering state cache from the given rendering state cache.

		 @param[in]		rendering_state_cache
						A reference to the rendering state cache to copy.
		 */
		RenderingStateCache(const RenderingStateCache &rendering_state_cache) = delete;

		/**
		 Constructs a rendering state cache by moving the given rendering state cache.

		 @param[in]		rendering_state_cache
						A reference to the rendering state cache to move.
		 */
		RenderingStateCache(RenderingStateCache &&rendering_state_cache);

		/**
		 Destructs this rendering state cache.
		 */
		~RenderingStateCache();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given rendering state cache to this rendering state cache.

		 @param[in]		rendering_state_cache
						A reference to the rendering state cache to copy.
		 @return		A reference to the copy of the given rendering state cache
						(i.e. this rendering state cache).
		 */
		RenderingStateCache &operator=(const RenderingStateCache &rendering_state_cache) = delete;

		/**
		 Moves the given rendering state cache to this rendering state cache.

		 @param[in]		rendering_state_cache
						A reference to the rendering state cache to move.
		 @return		A reference to the moved rendering state cache
						(i.e. this rendering state cache).
		 */
		RenderingStateCache &operator=(RenderingStateCache &&rendering_state_cache) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Blend States
		//---------------------------------------------------------------------

		/**
		 Returns the opaque blend state of this rendering cache.

		 @return		A pointer to the opaque blend state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the blend state
						of this rendering state cache.
		 */
		ID3D11BlendState *GetOpaqueBlendState();

		/**
		 Binds the opaque blend state of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the blend state.
		 */
		void BindOpaqueBlendState(ID3D11DeviceContext2 *device_context) {
			OM::BindBlendState(device_context, GetOpaqueBlendState());
		}

		/**
		 Returns the alpha blend state of this rendering cache.

		 @return		A pointer to the alpha blend state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the blend state
						of this rendering state cache.
		 */
		ID3D11BlendState *GetAlphaBlendState();

		/**
		 Binds the alpha blend state of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the blend state.
		 */
		void BindAlphaBlendState(ID3D11DeviceContext2 *device_context) {
			OM::BindBlendState(device_context, GetAlphaBlendState());
		}

		/**
		 Returns the additive blend state of this rendering cache.

		 @return		A pointer to the additive blend state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the blend state
						of this rendering state cache.
		 */
		ID3D11BlendState *GetAdditiveBlendState();

		/**
		 Binds the additive blend state of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the blend state.
		 */
		void BindAdditiveBlendState(ID3D11DeviceContext2 *device_context) {
			OM::BindBlendState(device_context, GetAdditiveBlendState());
		}

		/**
		 Returns the non-premultiplied blend state of this rendering cache.

		 @return		A pointer to the non-premultiplied blend state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the blend state
						of this rendering state cache.
		 */
		ID3D11BlendState *GetNonPremultipliedBlendState();

		/**
		 Binds the non-premultiplied blend state of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the blend state.
		 */
		void BindNonPremultipliedBlendState(ID3D11DeviceContext2 *device_context) {
			OM::BindBlendState(device_context, GetNonPremultipliedBlendState());
		}

		/**
		 Returns the alpha-to-coverage blend state of this rendering cache.

		 @return		A pointer to the alpha-to-coverage blend state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the blend state
						of this rendering state cache.
		 */
		ID3D11BlendState *GetAlphaToCoverageBlendState();

		/**
		 Binds the alpha-to-coverage blend state of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the blend state.
		 */
		void BindAlphaToCoverageBlendState(ID3D11DeviceContext2 *device_context) {
			OM::BindBlendState(device_context, GetAlphaToCoverageBlendState());
		}

		//---------------------------------------------------------------------
		// Member Methods: Depth Stencil States
		//---------------------------------------------------------------------

		/**
		 Returns the no-depth stencil state of this rendering cache.

		 @return		A pointer to the read depth stencil state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the depth stencil state
						of this rendering state cache.
		 */
		ID3D11DepthStencilState *GetDepthNoneDepthStencilState();

		/**
		 Binds the no-depth stencil state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the depth stencil state.
		 */
		void BindDepthNoneDepthStencilState(ID3D11DeviceContext2 *device_context) {
			OM::BindDepthStencilState(device_context, GetDepthNoneDepthStencilState());
		}

		/**
		 Returns the default depth stencil state of this rendering cache.

		 @return		A pointer to the read depth stencil state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the depth stencil state
						of this rendering state cache.
		 */
		ID3D11DepthStencilState *GetDepthDefaultDepthStencilState();

		/**
		 Binds the default depth stencil state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the depth stencil state.
		 */
		void BindDepthDefaultDepthStencilState(ID3D11DeviceContext2 *device_context) {
			OM::BindDepthStencilState(device_context, GetDepthDefaultDepthStencilState());
		}

		/**
		 Returns the read depth stencil state of this rendering cache.

		 @return		A pointer to the read depth stencil state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the depth stencil state
						of this rendering state cache.
		 */
		ID3D11DepthStencilState *GetDepthReadDepthStencilState();

		/**
		 Binds the read depth stencil state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the depth stencil state.
		 */
		void BindDepthReadDepthStencilState(ID3D11DeviceContext2 *device_context) {
			OM::BindDepthStencilState(device_context, GetDepthReadDepthStencilState());
		}

		//-------------------------------------------------------------------------
		// Member Methods: Rasterizer States
		//-------------------------------------------------------------------------

		/**
		 Returns the no-culling rasterizer state of this rendering cache.

		 @return		A pointer to the no-culling rasterizer state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the rasterizer state
						of this rendering state cache.
		 */
		ID3D11RasterizerState *GetCullNoneRasterizerState();

		/**
		 Binds the no-culling rasterizer state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the rasterizer state.
		 */
		void BindCullNoneRasterizerState(ID3D11DeviceContext2 *device_context) {
			RS::BindState(device_context, GetCullNoneRasterizerState());
		}

		/**
		 Returns the clockwise-culling rasterizer state of this rendering cache.

		 @return		A pointer to the clockwise-culling rasterizer state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the rasterizer state
						of this rendering state cache.
		 */
		ID3D11RasterizerState *GetCullClockwiseRasterizerState();

		/**
		 Binds the clockwise-culling rasterizer state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the rasterizer state.
		 */
		void BindCullClockwiseRasterizerState(ID3D11DeviceContext2 *device_context) {
			RS::BindState(device_context, GetCullClockwiseRasterizerState());
		}

		/**
		 Returns the counter-clockwise-culling rasterizer state of this rendering cache.

		 @return		A pointer to the counter-clockwise-culling rasterizer state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the rasterizer state
						of this rendering state cache.
		 */
		ID3D11RasterizerState *GetCullCounterClockwiseRasterizerState();

		/**
		 Binds the counter-clockwise-culling rasterizer state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the rasterizer state.
		 */
		void BindCullCounterClockwiseRasterizerState(ID3D11DeviceContext2 *device_context) {
			RS::BindState(device_context, GetCullCounterClockwiseRasterizerState());
		}

		/**
		 Returns the wireframe rasterizer state of this rendering cache.

		 @return		A pointer to the wireframe rasterizer state
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the rasterizer state
						of this rendering state cache.
		 */
		ID3D11RasterizerState *GetWireframeRasterizerState();

		/**
		 Binds the wireframe rasterizer state
		 of this rendering cache.

		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to bind the rasterizer state.
		 */
		void BindWireframeRasterizerState(ID3D11DeviceContext2 *device_context) {
			RS::BindState(device_context, GetWireframeRasterizerState());
		}

		//-------------------------------------------------------------------------
		// Member Methods: Sampler States
		//-------------------------------------------------------------------------

		/**
		 Returns the point sampling state with wrapping of this rendering cache.

		 @return		A pointer to the point sampling state with wrapping
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the sampler state
						of this rendering state cache.
		 */
		ID3D11SamplerState *GetPointWrapSamplerState();

		/**
		 Returns the point sampling state with clamping of this rendering cache.

		 @return		A pointer to the point sampling state with clamping
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the sampler state
						of this rendering state cache.
		 */
		ID3D11SamplerState *GetPointClampSamplerState();

		/**
		 Returns the point sampling state with wrapping of this rendering cache.

		 @return		A pointer to the point sampling state with wrapping
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the sampler state
						of this rendering state cache.
		 */
		ID3D11SamplerState *GetLinearWrapSamplerState();

		/**
		 Returns the linear sampling state with clamping of this rendering cache.

		 @return		A pointer to the linear sampling state with clamping
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the sampler state
						of this rendering state cache.
		 */
		ID3D11SamplerState *GetLinearClampSamplerState();

		/**
		 Returns the anisotropic sampling state with wrapping of this rendering cache.

		 @return		A pointer to the anisotropic sampling state with wrapping
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the sampler state
						of this rendering state cache.
		 */
		ID3D11SamplerState *GetAnisotropicWrapSamplerState();

		/**
		 Returns the anisotropic sampling state with clamping of this rendering cache.

		 @return		A pointer to the anisotropic sampling state with clamping
						of this rendering cache.
		 @throws		FormattedException
						Failed to create the sampler state
						of this rendering state cache.
		 */
		ID3D11SamplerState *GetAnisotropicClampSamplerState();

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The device of this rendering state.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the opaque blend state
		 of this rendering cache.
		 */
		ComPtr< ID3D11BlendState > m_opaque_blend_state;

		/**
		 A pointer to the alpha blend state
		 of this rendering cache.
		 */
		ComPtr< ID3D11BlendState > m_alpha_blend_state;

		/**
		 A pointer to the additive blend state
		 of this rendering cache.
		 */
		ComPtr< ID3D11BlendState > m_additive_blend_state;

		/**
		 A pointer to the non-premultiplied blend state
		 of this rendering cache.
		 */
		ComPtr< ID3D11BlendState > m_non_premultiplied_blend_state;

		/**
		 A pointer to the alpha-to-coverage blend state
		 of this rendering cache.
		 */
		ComPtr< ID3D11BlendState > m_alpha_to_coverage_blend_state;

		/**
		 A pointer to the no-depth stencil state
		 of this rendering cache.
		 */
		ComPtr< ID3D11DepthStencilState > m_depth_none_depth_stencil_state;

		/**
		 A pointer to the default depth stencil state
		 of this rendering cache.
		 */
		ComPtr< ID3D11DepthStencilState > m_depth_default_depth_stencil_state;

		/**
		 A pointer to the read depth stencil state
		 of this rendering cache.
		 */
		ComPtr< ID3D11DepthStencilState > m_depth_read_depth_stencil_state;

		/**
		 A pointer to the no-culling rasterizer state
		 of this rendering cache.
		 */
		ComPtr< ID3D11RasterizerState > m_cull_none_rasterizer_state;

		/**
		 A pointer to the clockwise-culling rasterizer state
		 of this rendering cache.
		 */
		ComPtr< ID3D11RasterizerState > m_cull_clockwise_rasterizer_state;

		/**
		 A pointer to the counter-clockwise-culling rasterizer state
		 of this rendering cache.
		 */
		ComPtr< ID3D11RasterizerState > m_cull_counter_clockwise_rasterizer_state;

		/**
		 A pointer to the wireframe rasterizer state
		 of this rendering cache.
		 */
		ComPtr< ID3D11RasterizerState > m_wireframe_rasterizer_state;

		/**
		 A pointer to the point sampling state with wrapping
		 of this rendering cache.
		 */
		ComPtr< ID3D11SamplerState > m_point_wrap_sampler_state;

		/**
		 A pointer to the point sampling state with clamping
		 of this rendering cache.
		 */
		ComPtr< ID3D11SamplerState > m_point_clamp_sampler_state;

		/**
		 A pointer to the linear sampling state with wrapping
		 of this rendering cache.
		 */
		ComPtr< ID3D11SamplerState > m_linear_wrap_sampler_state;

		/**
		 A pointer to the linear sampling state with clamping
		 of this rendering cache.
		 */
		ComPtr< ID3D11SamplerState > m_linear_clamp_sampler_state;

		/**
		 A pointer to the anisotropic sampling state with wrapping
		 of this rendering cache.
		 */
		ComPtr< ID3D11SamplerState > m_anisotropic_wrap_sampler_state;

		/**
		 A pointer to the anisotropic sampling state with clamping
		 of this rendering cache.
		 */
		ComPtr< ID3D11SamplerState > m_anisotropic_clamp_sampler_state;

		/**
		 The mutex of this rendering state cache.
		 */
		Mutex m_mutex;
	};
}
