#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Buffers
	//-------------------------------------------------------------------------

	/**
	 Creates a static vertex buffer.

	 @tparam		VertexT
					The vertex type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			@a vertices is not equal to @c nullptr.
	 @pre			@a vertices points to an array containing at least 
					@a nb_vertices elements.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		vertices
					A pointer to the vertices.
	 @param[in]		nb_vertices
					The number of vertices.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT CreateStaticVertexBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const VertexT *vertices, size_t nb_vertices) noexcept;
	
	/**
	 Creates a dynamic vertex buffer.

	 @tparam		VertexT
					The vertex type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			If @a vertices is not equal to @c nullptr, then @a vertices 
					points to an array containing at least @a nb_vertices 
					elements.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		vertices
					A pointer to the vertices.
	 @param[in]		nb_vertices
					The number of vertices.
	 @return		A success/error value.
	 */
	template < typename VertexT >
	HRESULT CreateDynamicVertexBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const VertexT *vertices, size_t nb_vertices) noexcept;
	
	/**
	 Creates a static index buffer.

	 @tparam		IndexT
					The index type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			@a indices is not equal to @c nullptr.
	 @pre			@a indices points to an array containing at least 
					@a nb_indices elements.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		indices
					A pointer to the indices.
	 @param[in]		nb_indices
					The number of indices.
	 @return		A success/error value.
	 */
	template < typename IndexT >
	HRESULT CreateStaticIndexBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const IndexT *indices, size_t nb_indices) noexcept;
	
	/**
	 Creates a static constant buffer.

	 @tparam		DataT
					The data type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			@a data is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					A pointer to the data.
	 @param[in]		count
					The number of elements.
	 @return		A success/error value.
	 */
	template < typename DataT >
	HRESULT CreateStaticConstantBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const DataT *data, size_t count = 1) noexcept;
	
	/**
	 Creates a dynamic constant buffer.

	 @tparam		DataT
					The data type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			If @a data is not equal to @c nullptr, then @a data points 
					to an array containing at least @a count elements.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					A pointer to the data.
	 @param[in]		count
					The number of elements.
	 @return		A success/error value.
	 */
	template < typename DataT >
	HRESULT CreateDynamicConstantBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const DataT *data, size_t count = 1) noexcept;
	
	/**
	 Creates a static structured buffer.

	 @tparam		DataT
					The data type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			@a data is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					A pointer to the data.
	 @param[in]		count
					The number of elements.
	 @return		A success/error value.
	 */
	template < typename DataT >
	HRESULT CreateStaticStructuredBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const DataT *data, size_t count = 1) noexcept;
	
	/**
	 Creates a dynamic structured buffer.

	 @tparam		DataT
					The data type.
	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a buffer is not equal to @c nullptr.
	 @pre			If @a data is not equal to @c nullptr, then @a data points 
					to an array containing at least @a count elements.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					A pointer to the data.
	 @param[in]		count
					The number of elements.
	 @return		A success/error value.
	 */
	template < typename DataT >
	HRESULT CreateDynamicStructuredBuffer(
		ID3D11Device5 *device, ID3D11Buffer **buffer, 
		const DataT *data, size_t count = 1) noexcept;

	//-------------------------------------------------------------------------
	// Blend states
	//-------------------------------------------------------------------------

	/**
	 Creates an opaque blend state (i.e. no blending).

	 The blend formula (i.e. no blending) is defined as:
	 (source.rgb × 1) + (destination.rgb × 0) = source.rgb
	 (source.a   × 1) + (destination.a   × 0) = source.a.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateOpaqueBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;
	
	/**
	 Creates an alpha blend state.

	 The blend formula is defined as:
	 (source.rgb × source.alpha)      + (destination.rgb × (1-source.alpha))
	 (source.a   × (1-destination.a)) + (destination.a   × 1).

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateAlphaBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;
	
	/**
	 Creates an additive blend state.

	 The blend formula is defined as:
	 (source.rgb × 1)                 + (destination.rgb × 1)
	 (source.a   × (1-destination.a)) + (destination.a   × 1).

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateAdditiveBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;
	
	/**
	 Creates a multiplicative blend state.

	 The blend formula is defined as:
	 (source.rgb × 0)                 + (destination.rgb × source.rgb)
	 (source.a   × (1-destination.a)) + (destination.a   × 1).

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateMultiplicativeBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;

	/**
	 Creates a bi-multiplicative blend state.

	 The blend formula is defined as:
	 (source.rgb × destination.rgb)   + (destination.rgb × source.rgb)
	 (source.a   × (1-destination.a)) + (destination.a   × 1).

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateBiMultiplicativeBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;

	/**
	 Creates an transparency blend state.

	 The blend formula for the first RTV is defined as:
	 (source.rgb × 1)                 + (destination.rgb × 1)
	 (source.a   × (1-destination.a)) + (destination.a   × 1).
	 The blend formula (i.e. no blending) for the remaining RTVs is defined as:
	 (source.rgb × 1) + (destination.rgb × 0) = source.rgb
	 (source.a   × 1) + (destination.a   × 0) = source.a.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateTransparencyBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;

	/**
	 Creates a alpha-to-coverage blend state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a blend_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	blend_state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	HRESULT CreateAlphaToCoverageBlendState(
		ID3D11Device5 *device, ID3D11BlendState **blend_state) noexcept;

	//-------------------------------------------------------------------------
	// Depth stencil states
	//-------------------------------------------------------------------------

	/**
	 Creates a no-read-no-write depth stencil state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a depth_stencil_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	depth_stencil_state
					A pointer to a pointer to the depth stencil state.
	 @return		A success/error value.
	 */
	HRESULT CreateDepthNoneDepthStencilState(
		ID3D11Device5 *device, ID3D11DepthStencilState **depth_stencil_state) noexcept;
	
	/**
	 Creates a read-write depth stencil state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a depth_stencil_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	depth_stencil_state
					A pointer to a pointer to the depth stencil state.
	 @param[in]		depth_comparison_function
					The depth comparison function.
	 @return		A success/error value.
	 */
	HRESULT CreateDepthReadWriteDepthStencilState(
		ID3D11Device5 *device, ID3D11DepthStencilState **depth_stencil_state,
		D3D11_COMPARISON_FUNC depth_comparison_function) noexcept;
	
	/**
	 Creates a read-only depth stencil state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a depth_stencil_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	depth_stencil_state
					A pointer to a pointer to the depth stencil state.
	 @param[in]		depth_comparison_function
					The depth comparison function.
	 @return		A success/error value.
	 */
	HRESULT CreateDepthReadDepthStencilState(
		ID3D11Device5 *device, ID3D11DepthStencilState **depth_stencil_state,
		D3D11_COMPARISON_FUNC depth_comparison_function) noexcept;

	//-------------------------------------------------------------------------
	// Rasterizer states
	//-------------------------------------------------------------------------

	/**
	 Creates a rasterizer state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a rasterizer_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	rasterizer_state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		cull_mode
					The cull mode of the rasterization.
	 @param[in]		fill_mode
					The fill mode of the rasterization.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	HRESULT CreateRasterizerState(
		ID3D11Device5 *device, ID3D11RasterizerState **rasterizer_state, 
		D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode,
		S32 depth_bias = 0u, F32 slope_scaled_depth_bias = 0.0f, 
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a no-culling (solid) rasterizer state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a rasterizer_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	rasterizer_state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	HRESULT CreateCullNoneRasterizerState(
		ID3D11Device5 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias = 0u, F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a clockwise-culling (solid) rasterizer state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a rasterizer_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	rasterizer_state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	HRESULT CreateCullClockwiseRasterizerState(
		ID3D11Device5 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias = 0u, F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a counter-clockwise-culling (solid) rasterizer state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a rasterizer_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	rasterizer_state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	HRESULT CreateCullCounterClockwiseRasterizerState(
		ID3D11Device5 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias = 0u, F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a wireframe rasterizer state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a rasterizer_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	rasterizer_state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	HRESULT CreateWireframeRasterizerState(
		ID3D11Device5 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias = 0u, F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;

	//-------------------------------------------------------------------------
	// Sampler states
	//-------------------------------------------------------------------------

	/**
	 Creates a sampling state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @param[in]		filter
					The filtering options during texture sampling.
	 @param[in]		address_mode
					The resolving of texture coordinates that are outside of 
					the boundaries of a texture.
	 @return		A success/error value.
	 */
	HRESULT CreateSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state, 
		D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode) noexcept;
	
	/**
	 Creates a point sampling state with wrapping.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreatePointWrapSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;
	
	/**
	Creates a point sampling state with clamping.

	@pre			@a device is not equal to @c nullptr.
	@pre			@a sampler_state is not equal to @c nullptr.
	@param[in]		device
					A pointer to the device.
	@param[out]		sampler_state
					A pointer to a pointer to the sampler state.
	@return			A success/error value.
	*/
	HRESULT CreatePointClampSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;

	/**
	Creates a point sampling state with mirroring.

	@pre			@a device is not equal to @c nullptr.
	@pre			@a sampler_state is not equal to @c nullptr.
	@param[in]		device
					A pointer to the device.
	@param[out]		sampler_state
					A pointer to a pointer to the sampler state.
	@return			A success/error value.
	*/
	HRESULT CreatePointMirrorSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;
	
	/**
	 Creates a linear sampling state with wrapping.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreateLinearWrapSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;
	
	/**
	 Creates a linear sampling state with clamping.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreateLinearClampSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;

	/**
	 Creates a linear sampling state with mirroring.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreateLinearMirrorSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;
	
	/**
	 Creates an anisotropic sampling state with wrapping.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreateAnisotropicWrapSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;

	/**
	 Creates an anisotropic sampling state with clamping.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreateAnisotropicClampSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;

	/**
	 Creates an anisotropic sampling state with mirroring.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreateAnisotropicMirrorSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;

	/**
	 Creates a PCF sampling state.

	 @pre			@a device is not equal to @c nullptr.
	 @pre			@a sampler_state is not equal to @c nullptr.
	 @param[in]		device
					A pointer to the device.
	 @param[out]	sampler_state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	HRESULT CreatePCFSamplerState(
		ID3D11Device5 *device, ID3D11SamplerState **sampler_state) noexcept;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.tpp"

#pragma endregion