#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "rendering\rendering_factory.hpp"
#include "logging\error.hpp"
#include "exception\exception.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <iterator>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	[[nodiscard]] const StateManager *StateManager::Get() noexcept {
		Assert(RenderingManager::Get());

		return RenderingManager::Get()->GetStateManager();
	}

	StateManager::StateManager(ID3D11Device *device)
		: m_blend_states{}, 
		m_depth_stencil_states{}, 
		m_rasterizer_states{}, 
		m_sampler_states{} {

		SetupRenderingStates(device);
	}

	StateManager::StateManager(StateManager &&manager) noexcept = default;

	StateManager::~StateManager() = default;

	void StateManager::SetupRenderingStates(ID3D11Device *device) {
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

	void StateManager::SetupBlendStates(ID3D11Device *device) {
		{
			const HRESULT result = CreateOpaqueBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::Opaque));
			ThrowIfFailed(result, 
						  "Opaque blend state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateAlphaBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::Alpha));
			ThrowIfFailed(result, 
						  "Alpha blend state creation failed: %08X.",
						  result);
		}

		{
			const HRESULT result = CreateAdditiveBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::Additive));
			ThrowIfFailed(result, "Additive blend state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateMultiplicativeBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::Multiplicative));
			ThrowIfFailed(result, 
						  "Multiplicative blend state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateBiMultiplicativeBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::BiMultiplicative));
			ThrowIfFailed(result, 
						  "Bi-multiplicative blend state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateTransparencyBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::Transparency));
			ThrowIfFailed(result, 
						  "Transparency blend state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateAlphaToCoverageBlendState(
				device, ReleaseAndGetAddressOf(BlendStateIndex::AlphaToCoverage));
			ThrowIfFailed(result, 
						  "Alpha-to-coverage blend state creation failed: %08X.", 
						  result);
		}
	}

	void StateManager::SetupDepthStencilStates(ID3D11Device *device) {
		{
			const HRESULT result = CreateDepthNoneDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::DepthNone));
			ThrowIfFailed(result, 
						  "No-read-no-write depth stencil state creation failed: %08X.", 
						  result);
		}

		#ifdef DISABLE_INVERTED_Z_BUFFER

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::LessEqualDepthReadWrite),
				D3D11_COMPARISON_LESS_EQUAL);
			ThrowIfFailed(result, 
						  "Less-equal, read-write depth stencil state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::LessEqualDepthRead),
				D3D11_COMPARISON_LESS_EQUAL);
			ThrowIfFailed(result, 
						  "Less-equal, read depth stencil state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::LessDepthReadWrite),
				D3D11_COMPARISON_LESS);
			ThrowIfFailed(result, 
						  "Less, read-write depth stencil state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::LessDepthRead),
				D3D11_COMPARISON_LESS);
			ThrowIfFailed(result, 
						  "Less, read depth stencil state creation failed: %08X.", 
						  result);
		}

		#else  // DISABLE_INVERTED_Z_BUFFER

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::GreaterEqualDepthReadWrite),
				D3D11_COMPARISON_GREATER_EQUAL);
			ThrowIfFailed(result, 
						  "Greater-equal, read-write depth stencil state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::GreaterEqualDepthRead), 
				D3D11_COMPARISON_GREATER_EQUAL);
			ThrowIfFailed(result, 
						  "Greater-equal, read depth stencil state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::GreaterDepthReadWrite), 
				D3D11_COMPARISON_GREATER);
			ThrowIfFailed(result, 
						  "Greater, read-write depth stencil state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				device, ReleaseAndGetAddressOf(DepthStencilStateIndex::GreaterDepthRead), 
				D3D11_COMPARISON_GREATER);
			ThrowIfFailed(result, 
						  "Greater, read depth stencil state creation failed: %08X.", 
						  result);
		}

		#endif // DISABLE_INVERTED_Z_BUFFER
	}

	void StateManager::SetupRasterizerStates(ID3D11Device *device) {
		{
			const HRESULT result = CreateCullNoneRasterizerState(
				device, ReleaseAndGetAddressOf(RasterizerStateIndex::NoCulling));
			ThrowIfFailed(result, 
						  "No-culling rasterizer state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateCullClockwiseRasterizerState(
				device, ReleaseAndGetAddressOf(RasterizerStateIndex::ClockwiseCulling));
			ThrowIfFailed(result, 
						  "Clockwise-culling rasterizer state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateCullCounterClockwiseRasterizerState(
				device, ReleaseAndGetAddressOf(RasterizerStateIndex::CounterClockwiseCulling));
			ThrowIfFailed(result, 
						  "Counter-clockwise-culling rasterizer state creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateWireframeRasterizerState(
				device, ReleaseAndGetAddressOf(RasterizerStateIndex::Wireframe));
			ThrowIfFailed(result, 
						  "Wireframe rasterizer state creation failed: %08X.", 
						  result);
		}
	}

	void StateManager::SetupSamplerStates(ID3D11Device *device) {
		{
			const HRESULT result = CreatePointWrapSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::PointWrap));
			ThrowIfFailed(result, 
						  "Point sampling state with wrapping creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreatePointClampSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::PointClamp));
			ThrowIfFailed(result, 
						  "Point sampling state with clamping creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreatePointMirrorSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::PointMirror));
			ThrowIfFailed(result, 
						  "Point sampling state with mirroring creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateLinearWrapSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::LinearWrap));
			ThrowIfFailed(result, 
						  "Linear sampling state with wrapping creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateLinearClampSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::LinearClamp));
			ThrowIfFailed(result, 
						  "Linear sampling state with clamping creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateLinearMirrorSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::LinearMirror));
			ThrowIfFailed(result, 
						  "Linear sampling state with mirroring creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateAnisotropicWrapSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::AnisotropicWrap));
			ThrowIfFailed(result, 
						  "Anisotropic sampling state with wrapping creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateAnisotropicClampSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::AnisotropicClamp));
			ThrowIfFailed(result, 
						  "Anisotropic sampling state with clamping creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreateAnisotropicMirrorSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::AnisotropicMirror));
			ThrowIfFailed(result, 
						  "Anisotropic sampling state with mirroring creation failed: %08X.", 
						  result);
		}

		{
			const HRESULT result = CreatePCFSamplerState(
				device, ReleaseAndGetAddressOf(SamplerStateIndex::PCF));
			ThrowIfFailed(result, 
						  "PCF sampling state creation failed: %08X.", 
						  result);
		}
	}

	void StateManager::BindPersistentState() const noexcept {
		static_assert(SLOT_SAMPLER_POINT_CLAMP        == SLOT_SAMPLER_POINT_WRAP + 1);
		static_assert(SLOT_SAMPLER_POINT_MIRROR       == SLOT_SAMPLER_POINT_WRAP + 2);
		static_assert(SLOT_SAMPLER_LINEAR_WRAP        == SLOT_SAMPLER_POINT_WRAP + 3);
		static_assert(SLOT_SAMPLER_LINEAR_CLAMP       == SLOT_SAMPLER_POINT_WRAP + 4);
		static_assert(SLOT_SAMPLER_LINEAR_MIRROR      == SLOT_SAMPLER_POINT_WRAP + 5);
		static_assert(SLOT_SAMPLER_ANISOTROPIC_WRAP   == SLOT_SAMPLER_POINT_WRAP + 6);
		static_assert(SLOT_SAMPLER_ANISOTROPIC_CLAMP  == SLOT_SAMPLER_POINT_WRAP + 7);
		static_assert(SLOT_SAMPLER_ANISOTROPIC_MIRROR == SLOT_SAMPLER_POINT_WRAP + 8);
		static_assert(SLOT_SAMPLER_PCF                == SLOT_SAMPLER_POINT_WRAP + 9);

		// Collect the samplers.
		ID3D11SamplerState * const samplers[] = {
			Get(SamplerStateIndex::PointWrap),
			Get(SamplerStateIndex::PointClamp),
			Get(SamplerStateIndex::PointMirror),
			Get(SamplerStateIndex::LinearWrap),
			Get(SamplerStateIndex::LinearClamp),
			Get(SamplerStateIndex::LinearMirror),
			Get(SamplerStateIndex::AnisotropicWrap),
			Get(SamplerStateIndex::AnisotropicClamp),
			Get(SamplerStateIndex::AnisotropicMirror),
			Get(SamplerStateIndex::PCF),
		};

		// Bind the samplers.
		Pipeline::BindSamplers(Pipeline::GetImmediateDeviceContext(),
							   SLOT_SAMPLER_POINT_WRAP,
			                   static_cast< U32 >(std::size(samplers)),
			                   samplers);
	}
}