#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Buffers
	//-------------------------------------------------------------------------

	template < typename VertexT >
	HRESULT CreateStaticVertexBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices);
	template < typename VertexT >
	HRESULT CreateDynamicVertexBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer, const VertexT *vertices, size_t nb_vertices);
	template < typename IndexT >
	HRESULT CreateIndexBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer, const IndexT *indices, size_t nb_indices);
	template < typename BufferT >
	HRESULT CreateConstantBuffer(ID3D11Device2 *device, ID3D11Buffer **buffer);

	//-------------------------------------------------------------------------
	// Blend states
	//-------------------------------------------------------------------------

	HRESULT CreateBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state, D3D11_BLEND src_blend, D3D11_BLEND dest_blend);
	HRESULT CreateOpaqueBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state);
	HRESULT CreateAlphaBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state);
	HRESULT CreateAdditiveBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state);
	HRESULT CreateNonPremultipliedBlendState(ID3D11Device2 *device, ID3D11BlendState **blend_state);

	//-------------------------------------------------------------------------
	// Depth stencil states
	//-------------------------------------------------------------------------

	HRESULT CreateDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state, bool enable, bool write_enable);
	HRESULT CreateDepthNoneDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state);
	HRESULT CreateDepthDefaultDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state);
	HRESULT CreateDepthReadDepthStencilState(ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state);

	//-------------------------------------------------------------------------
	// Rasterizer states
	//-------------------------------------------------------------------------

	HRESULT CreateRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state, D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode);
	HRESULT CreateCullNoneRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state);
	HRESULT CreateCullClockwiseRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state);
	HRESULT CreateCullCounterClockwiseRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state);
	HRESULT CreateWireframeRasterizerState(ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state);

	//-------------------------------------------------------------------------
	// Sampler states
	//-------------------------------------------------------------------------

	HRESULT CreateSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode);
	HRESULT CreatePointWrapSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state);
	HRESULT CreatePointClampSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state);
	HRESULT CreateLinearWrapSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state);
	HRESULT CreateLinearClampSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state);
	HRESULT CreateAnisotropicWrapSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state);
	HRESULT CreateAnisotropicClampSamplerState(ID3D11Device2 *device, ID3D11SamplerState **sampler_state);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.tpp"

#pragma endregion