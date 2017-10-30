//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Blend states
	//-------------------------------------------------------------------------

	HRESULT CreateOpaqueBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {
		
		Assert(device);
		Assert(blend_state);

		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable           = FALSE;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		
		return device->CreateBlendState(&desc, blend_state);
	}
	
	HRESULT CreateAlphaBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {
	
		Assert(device);
		Assert(blend_state);

		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable           = TRUE;
		desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_INV_DEST_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, blend_state);
	}
	
	HRESULT CreateAdditiveBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {
		
		Assert(device);
		Assert(blend_state);

		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable           = TRUE;
		desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlend             = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_INV_DEST_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, blend_state);
	}
	
	HRESULT CreateMultiplicativeBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {
		
		Assert(device);
		Assert(blend_state);

		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable           = TRUE;
		desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].DestBlend             = D3D11_BLEND_SRC_COLOR;
		desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_INV_DEST_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, blend_state);
	}

	HRESULT CreateBiMultiplicativeBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {

		Assert(device);
		Assert(blend_state);

		D3D11_BLEND_DESC desc = {};
		desc.RenderTarget[0].BlendEnable           = TRUE;
		desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_DEST_COLOR;
		desc.RenderTarget[0].DestBlend             = D3D11_BLEND_SRC_COLOR;
		desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_INV_DEST_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, blend_state);
	}

	HRESULT CreateTransparencyBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {
	
		Assert(device);
		Assert(blend_state);

		D3D11_BLEND_DESC desc = {};
		desc.IndependentBlendEnable                = TRUE;
		// Blending of the color.
		desc.RenderTarget[0].BlendEnable           = TRUE;
		desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_INV_DEST_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		// Blending of the normal and the remaining.
		for (size_t i = 1; i < 8; ++i) {
			desc.RenderTarget[i].BlendEnable       = FALSE;
		}
	
		return device->CreateBlendState(&desc, blend_state);
	}

	HRESULT CreateAlphaToCoverageBlendState(
		ID3D11Device2 *device, ID3D11BlendState **blend_state) noexcept {
		
		Assert(device);
		Assert(blend_state);
		
		D3D11_BLEND_DESC desc = {};
		desc.AlphaToCoverageEnable                 = TRUE;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		return device->CreateBlendState(&desc, blend_state);
	}

	//-------------------------------------------------------------------------
	// Depth stencil states
	//-------------------------------------------------------------------------

	HRESULT CreateDepthNoneDepthStencilState(
		ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state) noexcept {
		
		Assert(device);
		Assert(depth_stencil_state);

		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable   = FALSE;
		desc.StencilEnable = FALSE;
		
		return device->CreateDepthStencilState(&desc, depth_stencil_state);
	}
	
	HRESULT CreateDepthReadWriteDepthStencilState(
		ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state,
		D3D11_COMPARISON_FUNC depth_comparison_function) noexcept {
		
		Assert(device);
		Assert(depth_stencil_state);

		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable    = TRUE;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc      = depth_comparison_function;
		desc.StencilEnable  = FALSE;

		return device->CreateDepthStencilState(&desc, depth_stencil_state);
	}
	
	HRESULT CreateDepthReadDepthStencilState(
		ID3D11Device2 *device, ID3D11DepthStencilState **depth_stencil_state,
		D3D11_COMPARISON_FUNC depth_comparison_function) noexcept {
		
		Assert(device);
		Assert(depth_stencil_state);

		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable    = TRUE;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc      = depth_comparison_function;
		desc.StencilEnable  = FALSE;

		return device->CreateDepthStencilState(&desc, depth_stencil_state);
	}

	//-------------------------------------------------------------------------
	// Rasterizer states
	//-------------------------------------------------------------------------

	HRESULT CreateRasterizerState(
		ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state, 
		D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode,
		S32 depth_bias, F32 slope_scaled_depth_bias, F32 depth_bias_clamp) noexcept {
		
		Assert(device);
		Assert(rasterizer_state);
		
		D3D11_RASTERIZER_DESC desc = {};
		desc.CullMode             = cull_mode;
		desc.FillMode             = fill_mode;
		
#ifdef DISSABLE_INVERTED_Z_BUFFER
		desc.DepthBias            = depth_bias;
		desc.SlopeScaledDepthBias = slope_scaled_depth_bias;
		desc.DepthBiasClamp       = depth_bias_clamp;
#else  // DISSABLE_INVERTED_Z_BUFFER
		desc.DepthBias            = -depth_bias;
		desc.SlopeScaledDepthBias = -slope_scaled_depth_bias;
		desc.DepthBiasClamp       = -depth_bias_clamp;
#endif // DISSABLE_INVERTED_Z_BUFFER
		
		desc.DepthClipEnable      = true;
		desc.MultisampleEnable    = true;

		return device->CreateRasterizerState(&desc, rasterizer_state);
	}
	
	HRESULT CreateCullNoneRasterizerState(
		ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias, F32 slope_scaled_depth_bias, F32 depth_bias_clamp) noexcept {
		
		Assert(device);
		Assert(rasterizer_state);
		
		return CreateRasterizerState(
			device, rasterizer_state, 
			D3D11_CULL_NONE, D3D11_FILL_SOLID,
			depth_bias, slope_scaled_depth_bias, depth_bias_clamp);
	}
	
	HRESULT CreateCullClockwiseRasterizerState(
		ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias, F32 slope_scaled_depth_bias, F32 depth_bias_clamp) noexcept {
		
		Assert(device);
		Assert(rasterizer_state);
		
		return CreateRasterizerState(
			device, rasterizer_state, 
			D3D11_CULL_FRONT, D3D11_FILL_SOLID,
			depth_bias, slope_scaled_depth_bias, depth_bias_clamp);
	}
	
	HRESULT CreateCullCounterClockwiseRasterizerState(
		ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias, F32 slope_scaled_depth_bias, F32 depth_bias_clamp) noexcept {
		
		Assert(device);
		Assert(rasterizer_state);
		
		return CreateRasterizerState(
			device, rasterizer_state, 
			D3D11_CULL_BACK, D3D11_FILL_SOLID,
			depth_bias, slope_scaled_depth_bias, depth_bias_clamp);
	}
	
	HRESULT CreateWireframeRasterizerState(
		ID3D11Device2 *device, ID3D11RasterizerState **rasterizer_state,
		S32 depth_bias, F32 slope_scaled_depth_bias, F32 depth_bias_clamp) noexcept {
		
		Assert(device);
		Assert(rasterizer_state);
		
		return CreateRasterizerState(
			device, rasterizer_state, 
			D3D11_CULL_NONE, D3D11_FILL_WIREFRAME,
			depth_bias, slope_scaled_depth_bias, depth_bias_clamp);
	}

	//-------------------------------------------------------------------------
	// Sampler states
	//-------------------------------------------------------------------------

	HRESULT CreateSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state, 
		D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address_mode) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		D3D11_SAMPLER_DESC desc = {};
		desc.Filter         = filter;
		desc.AddressU       = address_mode;
		desc.AddressV       = address_mode;
		desc.AddressW       = address_mode;
		desc.MaxAnisotropy  = (device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) 
								? D3D11_MAX_MAXANISOTROPY : 2;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MaxLOD         = D3D11_FLOAT32_MAX;

		return device->CreateSamplerState(&desc, sampler_state);
	}
	
	HRESULT CreatePointWrapSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
	}
	
	HRESULT CreatePointClampSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_CLAMP);
	}
	
	HRESULT CreatePointMirrorSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_MIRROR);
	}

	HRESULT CreateLinearWrapSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
	}
	
	HRESULT CreateLinearClampSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_CLAMP);
	}
	
	HRESULT CreateLinearMirrorSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {

		Assert(device);
		Assert(sampler_state);

		return CreateSamplerState(device, sampler_state,
			D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_MIRROR);
	}

	HRESULT CreateAnisotropicWrapSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);
		
		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_WRAP);
	}
	
	HRESULT CreateAnisotropicClampSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {
		
		Assert(device);
		Assert(sampler_state);

		return CreateSamplerState(device, sampler_state, 
			D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_CLAMP);
	}

	HRESULT CreateAnisotropicMirrorSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {

		Assert(device);
		Assert(sampler_state);

		return CreateSamplerState(device, sampler_state,
			D3D11_FILTER_ANISOTROPIC, D3D11_TEXTURE_ADDRESS_MIRROR);
	}

	HRESULT CreatePCFSamplerState(
		ID3D11Device2 *device, ID3D11SamplerState **sampler_state) noexcept {

		Assert(device);
		Assert(sampler_state);
		
		D3D11_SAMPLER_DESC desc = {};
		desc.Filter         = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
		desc.AddressU       = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.AddressV       = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.AddressW       = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.MaxAnisotropy  = (device->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) 
								? D3D11_MAX_MAXANISOTROPY : 2;
		
#ifdef DISSABLE_INVERTED_Z_BUFFER
		desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
#else  // DISSABLE_INVERTED_Z_BUFFER
		desc.ComparisonFunc = D3D11_COMPARISON_GREATER_EQUAL;
#endif // DISSABLE_INVERTED_Z_BUFFER
		
		desc.MaxLOD         = D3D11_FLOAT32_MAX;

		return device->CreateSamplerState(&desc, sampler_state);
	}
}