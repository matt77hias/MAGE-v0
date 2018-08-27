#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "direct3d11.hpp"
#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Buffers
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a static vertex buffer.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		vertices
					The vertices.
	 @return		A success/error value.
	 */
	template< typename VertexT >
	[[nodiscard]]
	HRESULT CreateStaticVertexBuffer(ID3D11Device& device, 
									 NotNull< ID3D11Buffer** > buffer,
									 gsl::span< const VertexT > vertices) noexcept;
	
	/**
	 Creates a dynamic vertex buffer.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		vertices
					The vertices.
	 @return		A success/error value.
	 */
	template< typename VertexT >
	[[nodiscard]]
	HRESULT CreateDynamicVertexBuffer(ID3D11Device& device,
									  NotNull< ID3D11Buffer** > buffer,
									  gsl::span< const VertexT > vertices) noexcept;

	/**
	 Creates a dynamic vertex buffer.

	 @tparam		VertexT
					The vertex type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		nb_vertices
					The number of vertices.
	 @return		A success/error value.
	 */
	template< typename VertexT >
	[[nodiscard]]
	HRESULT CreateDynamicVertexBuffer(ID3D11Device& device,
									  NotNull< ID3D11Buffer** > buffer,
									  size_t nb_vertices) noexcept;
	
	/**
	 Creates a static index buffer.

	 @tparam		IndexT
					The index type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		indices
					The indices.
	 @return		A success/error value.
	 */
	template< typename IndexT >
	[[nodiscard]]
	HRESULT CreateStaticIndexBuffer(ID3D11Device& device, 
									NotNull< ID3D11Buffer** > buffer,
									gsl::span< const IndexT > indices) noexcept;
	
	/**
	 Creates a static constant buffer.

	 @tparam		T
					The data type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					The data.
	 @return		A success/error value.
	 */
	template< typename T >
	[[nodiscard]]
	HRESULT CreateStaticConstantBuffer(ID3D11Device& device, 
									   NotNull< ID3D11Buffer** > buffer,
									   gsl::span< const T > data) noexcept;
	
	/**
	 Creates a dynamic constant buffer.

	 @tparam		T
					The data type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					The data.
	 @return		A success/error value.
	 */
	template< typename T >
	[[nodiscard]]
	HRESULT CreateDynamicConstantBuffer(ID3D11Device& device, 
										NotNull< ID3D11Buffer** > buffer,
										gsl::span< const T > data) noexcept;

	/**
	 Creates a dynamic constant buffer.

	 @tparam		T
					The data type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		nb_data_elements
					The number of data elements.
	 @return		A success/error value.
	 */
	template< typename T >
	[[nodiscard]]
	HRESULT CreateDynamicConstantBuffer(ID3D11Device& device, 
										NotNull< ID3D11Buffer** > buffer,
										size_t nb_data_elements = 1u) noexcept;
	
	/**
	 Creates a static structured buffer.

	 @tparam		T
					The data type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					The data.
	 @return		A success/error value.
	 */
	template< typename T >
	[[nodiscard]]
	HRESULT CreateStaticStructuredBuffer(ID3D11Device& device, 
										 NotNull< ID3D11Buffer** > buffer,
										 gsl::span< const T > data) noexcept;
	
	/**
	 Creates a dynamic structured buffer.

	 @tparam		T
					The data type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		data
					The data.
	 @return		A success/error value.
	 */
	template< typename T >
	[[nodiscard]]
	HRESULT CreateDynamicStructuredBuffer(ID3D11Device& device, 
										  NotNull< ID3D11Buffer** > buffer,
										  gsl::span< const T > data) noexcept;

	/**
	 Creates a dynamic structured buffer.

	 @tparam		T
					The data type.
	 @param[in]		device
					A reference to the device.
	 @param[out]	buffer
					A pointer to a pointer to the buffer.
	 @param[in]		nb_data_elements
					The number of data elements.
	 @return		A success/error value.
	 */
	template< typename T >
	[[nodiscard]]
	HRESULT CreateDynamicStructuredBuffer(ID3D11Device& device, 
										  NotNull< ID3D11Buffer** > buffer,
										  size_t nb_data_elements) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Blend states
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates an opaque blend state (i.e. no blending).

	 The blend formula (i.e. no blending) is defined as:
	 (source.rgb × 1) + (destination.rgb × 0) = source.rgb
	 (source.a   × 1) + (destination.a   × 0) = source.a.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateOpaqueBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;
	
	/**
	 Creates an alpha blend state.

	 The blend formula is defined as:
	 (source.rgb ×  source.a        ) + (destination.rgb × (1-source.a))
	 (source.a   × (1-destination.a)) + (destination.a   ×  1          ).

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateAlphaBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;
	
	/**
	 Creates an additive blend state.

	 The blend formula is defined as:
	 (source.rgb ×  1               ) + (destination.rgb × 1)
	 (source.a   × (1-destination.a)) + (destination.a   × 1).

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateAdditiveBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;
	
	/**
	 Creates a multiplicative blend state.

	 The blend formula is defined as:
	 (source.rgb ×  0               ) + (destination.rgb × source.rgb)
	 (source.a   × (1-destination.a)) + (destination.a   × 1         ).

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateMultiplicativeBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;

	/**
	 Creates a bi-multiplicative blend state.

	 The blend formula is defined as:
	 (source.rgb ×  destination.rgb ) + (destination.rgb × source.rgb)
	 (source.a   × (1-destination.a)) + (destination.a   × 1         ).

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateBiMultiplicativeBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;

	/**
	 Creates an transparency blend state.

	 The blend formula for the first RTV is defined as:
	 (source.rgb ×  1               ) + (destination.rgb × 1)
	 (source.a   × (1-destination.a)) + (destination.a   × 1).
	 The blend formula (i.e. no blending) for the remaining RTVs is defined as:
	 (source.rgb × 1) + (destination.rgb × 0) = source.rgb
	 (source.a   × 1) + (destination.a   × 0) = source.a.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateTransparencyBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;

	/**
	 Creates a alpha-to-coverage blend state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the blend state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateAlphaToCoverageBlendState(
		ID3D11Device& device, NotNull< ID3D11BlendState** > state) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Depth stencil states
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a no-read-no-write depth stencil state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the depth stencil state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateDepthNoneDepthStencilState(
		ID3D11Device& device, NotNull< ID3D11DepthStencilState** > state) noexcept;
	
	/**
	 Creates a read-write depth stencil state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the depth stencil state.
	 @param[in]		func
					The depth comparison function.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateDepthReadWriteDepthStencilState(
		ID3D11Device& device, NotNull< ID3D11DepthStencilState** > state,
		D3D11_COMPARISON_FUNC func) noexcept;
	
	/**
	 Creates a read-only depth stencil state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the depth stencil state.
	 @param[in]		func
					The depth comparison function.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateDepthReadDepthStencilState(
		ID3D11Device& device, NotNull< ID3D11DepthStencilState** > state, 
		D3D11_COMPARISON_FUNC func) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Rasterizer states
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a rasterizer state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
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
	[[nodiscard]]
	HRESULT CreateRasterizerState(ID3D11Device& device, 
								  NotNull< ID3D11RasterizerState** > state,
								  D3D11_CULL_MODE cull_mode, 
								  D3D11_FILL_MODE fill_mode, 
								  S32 depth_bias = 0,
								  F32 slope_scaled_depth_bias = 0.0f, 
								  F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a no-culling (solid) rasterizer state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateCullNoneRasterizerState(
		ID3D11Device& device,
		NotNull< ID3D11RasterizerState** > state,
		S32 depth_bias = 0,
		F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a clockwise-culling (solid) rasterizer state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateCullClockwiseRasterizerState(
		ID3D11Device& device,
		NotNull< ID3D11RasterizerState** > state,
		S32 depth_bias = 0,
		F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a counter-clockwise-culling (solid) rasterizer state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateCullCounterClockwiseRasterizerState(
		ID3D11Device& device, 
		NotNull< ID3D11RasterizerState** > state, 
		S32 depth_bias = 0, 
		F32 slope_scaled_depth_bias = 0.0f, 
		F32 depth_bias_clamp = 0.0f) noexcept;
	
	/**
	 Creates a wireframe rasterizer state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the rasterizer state.
	 @param[in]		depth_bias
					The depth value added to a given pixel.
	 @param[in]		slope_scaled_depth_bias
					The scalar on a given pixel's slope.
	 @param[in]		depth_bias_clamp
					The maximum depth bias of a pixel.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateWireframeRasterizerState(
		ID3D11Device& device,
		NotNull< ID3D11RasterizerState** > state,
		S32 depth_bias = 0,
		F32 slope_scaled_depth_bias = 0.0f,
		F32 depth_bias_clamp = 0.0f) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Sampler states
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Creates a sampling state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @param[in]		filter
					The filtering options during texture sampling.
	 @param[in]		address_mode
					The resolving of texture coordinates that are outside of 
					the boundaries of a texture.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateSamplerState(ID3D11Device& device, 
							   NotNull< ID3D11SamplerState** > state,
							   D3D11_FILTER filter, 
							   D3D11_TEXTURE_ADDRESS_MODE address_mode) noexcept;
	
	/**
	 Creates a point sampling state with wrapping.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreatePointWrapSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;
	
	/**
	Creates a point sampling state with clamping.

	@param[in]		device
					A reference to the device.
	@param[out]		state
					A pointer to a pointer to the sampler state.
	@return			A success/error value.
	*/
	[[nodiscard]]
	HRESULT CreatePointClampSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;

	/**
	Creates a point sampling state with mirroring.

	@param[in]		device
					A reference to the device.
	@param[out]		state
					A pointer to a pointer to the sampler state.
	@return			A success/error value.
	*/
	[[nodiscard]]
	HRESULT CreatePointMirrorSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;
	
	/**
	 Creates a linear sampling state with wrapping.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateLinearWrapSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;
	
	/**
	 Creates a linear sampling state with clamping.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateLinearClampSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;

	/**
	 Creates a linear sampling state with mirroring.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateLinearMirrorSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;
	
	/**
	 Creates an anisotropic sampling state with wrapping.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateAnisotropicWrapSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;

	/**
	 Creates an anisotropic sampling state with clamping.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateAnisotropicClampSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;

	/**
	 Creates an anisotropic sampling state with mirroring.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreateAnisotropicMirrorSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;

	/**
	 Creates a PCF sampling state.

	 @param[in]		device
					A reference to the device.
	 @param[out]	state
					A pointer to a pointer to the sampler state.
	 @return		A success/error value.
	 */
	[[nodiscard]]
	HRESULT CreatePCFSamplerState(
		ID3D11Device& device, NotNull< ID3D11SamplerState** > state) noexcept;

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\factory.tpp"

#pragma endregion