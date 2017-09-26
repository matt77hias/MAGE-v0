#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\renderer.hpp"
#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const RenderingStateCache *RenderingStateCache::Get() noexcept {
		Assert(Renderer::Get());

		return Renderer::Get()->GetRenderingStateCache();
	}

	RenderingStateCache::RenderingStateCache(ID3D11Device2 *device)
		: m_blend_states{}, m_depth_stencil_states{}, 
		m_rasterizer_states{}, m_sampler_states{} {

		SetupRenderingStates(device);
	}

	RenderingStateCache::RenderingStateCache(
		RenderingStateCache &&rendering_state_cache) = default;

	RenderingStateCache::~RenderingStateCache() = default;

	void RenderingStateCache::SetupRenderingStates(ID3D11Device2 *device) {
		Assert(device);

		// Setup the blend states.
		SetupBlendStates(device);
		// Setup the depth stencil states.
		SetupDepthStencilStates(device);
		// Setup the rasterizer states.
		SetupRasterizerStates(device);
		// Setup the sampler states.
		SetupSamplerStates(device);
	}

	void RenderingStateCache::SetupBlendStates(ID3D11Device2 *device) {
		const HRESULT result_opaque             = CreateOpaqueBlendState(
			device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Opaque));
		ThrowIfFailed(result_opaque, 
			"Opaque blend state creation failed: %08X.", 
			result_opaque);
		
		const HRESULT result_alpha              = CreateAlphaBlendState(
			device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Alpha));
		ThrowIfFailed(result_alpha, 
			"Alpha blend state creation failed: %08X.", 
			result_alpha);
		
		const HRESULT result_additive           = CreateAdditiveBlendState(
			device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Additive));
		ThrowIfFailed(result_additive, 
			"Additive blend state creation failed: %08X.", 
			result_additive);
		
		const HRESULT result_non_premultiplied  = CreateNonPremultipliedBlendState(
			device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::NonPremultiplied));
		ThrowIfFailed(result_non_premultiplied, 
			"Non-premultiplied blend state creation failed: %08X.", 
			result_non_premultiplied);
		
		const HRESULT result_alpha_to_coverage  = CreateAlphaToCoverageBlendState(
			device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::AlphaToCoverage));
		ThrowIfFailed(result_alpha_to_coverage, 
			"Alpha-to-Coverage blend state creation failed: %08X.", 
			result_alpha_to_coverage);
	}

	void RenderingStateCache::SetupDepthStencilStates(ID3D11Device2 *device) {
		const HRESULT result_depth_none         = CreateDepthNoneDepthStencilState(
			device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::DepthNone));
		ThrowIfFailed(result_depth_none, 
			"No-read-no-write depth stencil state creation failed: %08X.", 
			result_depth_none);
		
		const HRESULT result_depth_read_write   = CreateDepthReadWriteDepthStencilState(
			device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::DepthReadWrite));
		ThrowIfFailed(result_depth_read_write, 
			"Read-write depth stencil state creation failed: %08X.", 
			result_depth_read_write);
		
		const HRESULT result_depth_read         = CreateDepthReadDepthStencilState(
			device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::DepthRead));
		ThrowIfFailed(result_depth_read, 
			"Read depth stencil state creation failed: %08X.", 
			result_depth_read);
	}

	void RenderingStateCache::SetupRasterizerStates(ID3D11Device2 *device) {
		const HRESULT result_no_culling         = CreateCullNoneRasterizerState(
			device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::NoCulling));
		ThrowIfFailed(result_no_culling, 
			"No-culling rasterizer state creation failed: %08X.", 
			result_no_culling);
		
		const HRESULT result_clockwise_culling  = CreateCullClockwiseRasterizerState(
			device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::ClockwiseCulling));
		ThrowIfFailed(result_clockwise_culling, 
			"Clockwise-culling rasterizer state creation failed: %08X.", 
			result_clockwise_culling);
		
		const HRESULT result_counter_clockwise_culling = CreateCullCounterClockwiseRasterizerState(
			device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::CounterClockwiseCulling));
		ThrowIfFailed(result_counter_clockwise_culling, 
			"Counter-clockwise-culling rasterizer state creation failed: %08X.", 
			result_counter_clockwise_culling);
		
		const HRESULT result_wireframe          = CreateWireframeRasterizerState(
			device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::Wireframe));
		ThrowIfFailed(result_wireframe, 
			"Wireframe rasterizer state creation failed: %08X.", 
			result_wireframe);
	}

	void RenderingStateCache::SetupSamplerStates(ID3D11Device2 *device) {
		const HRESULT result_point_wrap         = CreatePointWrapSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PointWrap));
		ThrowIfFailed(result_point_wrap, 
			"Point sampling state with wrapping creation failed: %08X.", 
			result_point_wrap);
		
		const HRESULT result_point_clamp        = CreatePointClampSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PointClamp));
		ThrowIfFailed(result_point_clamp, 
			"Point sampling state with clamping creation failed: %08X.", 
			result_point_clamp);
		
		const HRESULT result_point_mirror       = CreatePointMirrorSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PointMirror));
		ThrowIfFailed(result_point_mirror, 
			"Point sampling state with mirroring creation failed: %08X.", 
			result_point_mirror);
		
		const HRESULT result_linear_wrap        = CreateLinearWrapSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::LinearWrap));
		ThrowIfFailed(result_linear_wrap, 
			"Linear sampling state with wrapping creation failed: %08X.", 
			result_linear_wrap);
		
		const HRESULT result_linear_clamp       = CreateLinearClampSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::LinearClamp));
		ThrowIfFailed(result_linear_clamp, 
			"Linear sampling state with clamping creation failed: %08X.", 
			result_linear_clamp);
		
		const HRESULT result_linear_mirror      = CreateLinearMirrorSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::LinearMirror));
		ThrowIfFailed(result_linear_mirror, 
			"Linear sampling state with mirroring creation failed: %08X.", 
			result_linear_mirror);
		
		const HRESULT result_anisotropic_wrap   = CreateAnisotropicWrapSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::AnisotropicWrap));
		ThrowIfFailed(result_anisotropic_wrap, 
			"Anisotropic sampling state with wrapping creation failed: %08X.", 
			result_anisotropic_wrap);
		
		const HRESULT result_anisotropic_clamp  = CreateAnisotropicClampSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::AnisotropicClamp));
		ThrowIfFailed(result_anisotropic_clamp, 
			"Anisotropic sampling state with clamping creation failed: %08X.", 
			result_anisotropic_clamp);
		
		const HRESULT result_anisotropic_mirror = CreateAnisotropicMirrorSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::AnisotropicMirror));
		ThrowIfFailed(result_anisotropic_mirror, 
			"Anisotropic sampling state with mirroring creation failed: %08X.", 
			result_anisotropic_mirror);
		
		const HRESULT result_pcf                = CreatePCFSamplerState(
			device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PCF));
		ThrowIfFailed(result_pcf, 
			"PCF sampling state creation failed: %08X.", 
			result_pcf);
	}

	void RenderingStateCache::BindTransparentBlendState(
		ID3D11DeviceContext2 *device_context) const noexcept {

		if (Renderer::Get()->HasMSAA()) {
			BindAlphaToCoverageBlendState(device_context);
		}
		else {
			BindAlphaBlendState(device_context);
		}
	}

	void RenderingStateCache::BindPersistentSamplers(
		ID3D11DeviceContext2 *device_context) const noexcept {
		
		// Collect the samplers.
		ID3D11SamplerState * const samplers[SLOT_SAMPLER_PERSISTENT_COUNT] = {
			GetSamplerState(SamplerStateIndex::PointWrap),
			GetSamplerState(SamplerStateIndex::PointClamp),
			GetSamplerState(SamplerStateIndex::PointMirror),
			GetSamplerState(SamplerStateIndex::LinearWrap),
			GetSamplerState(SamplerStateIndex::LinearClamp),
			GetSamplerState(SamplerStateIndex::LinearMirror),
			GetSamplerState(SamplerStateIndex::AnisotropicWrap),
			GetSamplerState(SamplerStateIndex::AnisotropicClamp),
			GetSamplerState(SamplerStateIndex::AnisotropicMirror),
			GetSamplerState(SamplerStateIndex::PCF),
		};

		// Bind the samplers.
		Pipeline::BindSamplers(device_context,
			SLOT_SAMPLER_PERSISTENT_START,
			SLOT_SAMPLER_PERSISTENT_COUNT,
			samplers);
	}
}