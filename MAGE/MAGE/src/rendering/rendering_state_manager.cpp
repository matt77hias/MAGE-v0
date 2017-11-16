#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "rendering\rendering_factory.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const RenderingStateManager *RenderingStateManager::Get() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetRenderingStateManager();
	}

	RenderingStateManager::RenderingStateManager(ID3D11Device5 *device)
		: m_blend_states{}, m_depth_stencil_states{}, 
		m_rasterizer_states{}, m_sampler_states{} {

		SetupRenderingStates(device);
	}

	RenderingStateManager::RenderingStateManager(
		RenderingStateManager &&rendering_state_manager) = default;

	RenderingStateManager::~RenderingStateManager() = default;

	void RenderingStateManager::SetupRenderingStates(ID3D11Device5 *device) {
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

	void RenderingStateManager::SetupBlendStates(ID3D11Device5 *device) {
		{
			const HRESULT result = CreateOpaqueBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Opaque));
			ThrowIfFailed(result,
				"Opaque blend state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateAlphaBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Alpha));
			ThrowIfFailed(result,
				"Alpha blend state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateAdditiveBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Additive));
			ThrowIfFailed(result,
				"Additive blend state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateMultiplicativeBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Multiplicative));
			ThrowIfFailed(result,
				"Multiplicative blend state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateBiMultiplicativeBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::BiMultiplicative));
			ThrowIfFailed(result,
				"Bi-multiplicative blend state creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreateTransparencyBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::Transparency));
			ThrowIfFailed(result,
				"Transparency blend state creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreateAlphaToCoverageBlendState(
				device, ReleaseAndGetAddressOfBlendState(BlendStateIndex::AlphaToCoverage));
			ThrowIfFailed(result,
				"Alpha-to-coverage blend state creation failed: %08X.",
				result);
		}
	}

	void RenderingStateManager::SetupDepthStencilStates(ID3D11Device5 *device) {
		{
			const HRESULT result = CreateDepthNoneDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::DepthNone));
			ThrowIfFailed(result,
				"No-read-no-write depth stencil state creation failed: %08X.", 
				result);
		}

#ifdef DISSABLE_INVERTED_Z_BUFFER

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::LessEqualDepthReadWrite),
				D3D11_COMPARISON_LESS_EQUAL);
			ThrowIfFailed(result,
				"Less-equal, read-write depth stencil state creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::LessEqualDepthRead),
				D3D11_COMPARISON_LESS_EQUAL);
			ThrowIfFailed(result,
				"Less-equal, read depth stencil state creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::LessDepthReadWrite),
				D3D11_COMPARISON_LESS);
			ThrowIfFailed(result,
				"Less, read-write depth stencil state creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::LessDepthRead),
				D3D11_COMPARISON_LESS);
			ThrowIfFailed(result,
				"Less, read depth stencil state creation failed: %08X.",
				result);
		}

#else  // DISSABLE_INVERTED_Z_BUFFER

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::GreaterEqualDepthReadWrite),
				D3D11_COMPARISON_GREATER_EQUAL);
			ThrowIfFailed(result,
				"Greater-equal, read-write depth stencil state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::GreaterEqualDepthRead), 
				D3D11_COMPARISON_GREATER_EQUAL);
			ThrowIfFailed(result,
				"Greater-equal, read depth stencil state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::GreaterDepthReadWrite), 
				D3D11_COMPARISON_GREATER);
			ThrowIfFailed(result,
				"Greater, read-write depth stencil state creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOfDepthStencilState(DepthStencilStateIndex::GreaterDepthRead), 
				D3D11_COMPARISON_GREATER);
			ThrowIfFailed(result,
				"Greater, read depth stencil state creation failed: %08X.",
				result);
		}

#endif // DISSABLE_INVERTED_Z_BUFFER
	}

	void RenderingStateManager::SetupRasterizerStates(ID3D11Device5 *device) {
		{
			const HRESULT result = CreateCullNoneRasterizerState(
				device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::NoCulling));
			ThrowIfFailed(result,
				"No-culling rasterizer state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateCullClockwiseRasterizerState(
				device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::ClockwiseCulling));
			ThrowIfFailed(result,
				"Clockwise-culling rasterizer state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateCullCounterClockwiseRasterizerState(
				device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::CounterClockwiseCulling));
			ThrowIfFailed(result,
				"Counter-clockwise-culling rasterizer state creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateWireframeRasterizerState(
				device, ReleaseAndGetAddressOfRasterizerState(RasterizerStateIndex::Wireframe));
			ThrowIfFailed(result,
				"Wireframe rasterizer state creation failed: %08X.",
				result);
		}
	}

	void RenderingStateManager::SetupSamplerStates(ID3D11Device5 *device) {
		{
			const HRESULT result = CreatePointWrapSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PointWrap));
			ThrowIfFailed(result,
				"Point sampling state with wrapping creation failed: %08X.",
				result);
		}

		{
			const HRESULT result = CreatePointClampSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PointClamp));
			ThrowIfFailed(result,
				"Point sampling state with clamping creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreatePointMirrorSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PointMirror));
			ThrowIfFailed(result,
				"Point sampling state with mirroring creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateLinearWrapSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::LinearWrap));
			ThrowIfFailed(result,
				"Linear sampling state with wrapping creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateLinearClampSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::LinearClamp));
			ThrowIfFailed(result,
				"Linear sampling state with clamping creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateLinearMirrorSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::LinearMirror));
			ThrowIfFailed(result,
				"Linear sampling state with mirroring creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateAnisotropicWrapSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::AnisotropicWrap));
			ThrowIfFailed(result,
				"Anisotropic sampling state with wrapping creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateAnisotropicClampSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::AnisotropicClamp));
			ThrowIfFailed(result,
				"Anisotropic sampling state with clamping creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreateAnisotropicMirrorSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::AnisotropicMirror));
			ThrowIfFailed(result,
				"Anisotropic sampling state with mirroring creation failed: %08X.", 
				result);
		}

		{
			const HRESULT result = CreatePCFSamplerState(
				device, ReleaseAndGetAddressOfSamplerState(SamplerStateIndex::PCF));
			ThrowIfFailed(result,
				"PCF sampling state creation failed: %08X.",
				result);
		}
	}

	void RenderingStateManager::BindPersistentState() const noexcept {
		
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
		Pipeline::BindSamplers(
			Pipeline::GetImmediateDeviceContext(),
			SLOT_SAMPLER_PERSISTENT_START,
			SLOT_SAMPLER_PERSISTENT_COUNT,
			samplers);
	}
}