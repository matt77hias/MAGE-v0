#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\state_manager.hpp"
#include "renderer\factory.hpp"
#include "exception\exception.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	StateManager::StateManager(ID3D11Device& device)
		: m_device(device),
		m_blend_states{}, 
		m_depth_stencil_states{}, 
		m_rasterizer_states{}, 
		m_sampler_states{} {

		SetupRenderingStates();
	}

	StateManager::StateManager(StateManager&& manager) noexcept = default;

	StateManager::~StateManager() = default;

	StateManager& StateManager
		::operator=(StateManager&& manager) noexcept = default;

	void StateManager::SetupRenderingStates() {
		// Setup the blend states.
		SetupBlendStates();
		// Setup the depth stencil states.
		SetupDepthStencilStates();
		// Setup the rasterizer states.
		SetupRasterizerStates();
		// Setup the sampler states.
		SetupSamplerStates();
	}

	void StateManager::SetupBlendStates() {
		{
			const HRESULT result = CreateOpaqueBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::Opaque));
			ThrowIfFailed(result, 
						  "Opaque blend state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateAlphaBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::Alpha));
			ThrowIfFailed(result, 
						  "Alpha blend state creation failed: {:08X}.",
						  result);
		}

		{
			const HRESULT result = CreateAdditiveBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::Additive));
			ThrowIfFailed(result, "Additive blend state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateMultiplicativeBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::Multiplicative));
			ThrowIfFailed(result, 
						  "Multiplicative blend state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateBiMultiplicativeBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::BiMultiplicative));
			ThrowIfFailed(result, 
						  "Bi-multiplicative blend state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateTransparencyBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::Transparency));
			ThrowIfFailed(result, 
						  "Transparency blend state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateAlphaToCoverageBlendState(
				m_device, ReleaseAndGetAddressOf(BlendStateID::AlphaToCoverage));
			ThrowIfFailed(result, 
						  "Alpha-to-coverage blend state creation failed: {:08X}.", 
						  result);
		}
	}

	void StateManager::SetupDepthStencilStates() {
		{
			const HRESULT result = CreateDepthNoneDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::DepthNone));
			ThrowIfFailed(result, 
						  "No-read-no-write depth stencil state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::GreaterEqualDepthReadWrite),
				D3D11_COMPARISON_GREATER_EQUAL);
			ThrowIfFailed(result, 
						  "Greater-equal, read-write depth stencil state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::GreaterEqualDepthRead),
				D3D11_COMPARISON_GREATER_EQUAL);
			ThrowIfFailed(result, 
						  "Greater-equal, read depth stencil state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::GreaterDepthReadWrite),
				D3D11_COMPARISON_GREATER);
			ThrowIfFailed(result, 
						  "Greater, read-write depth stencil state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::GreaterDepthRead),
				D3D11_COMPARISON_GREATER);
			ThrowIfFailed(result, 
						  "Greater, read depth stencil state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::LessEqualDepthReadWrite),
				D3D11_COMPARISON_LESS_EQUAL);
			ThrowIfFailed(result,
						  "Less-equal, read-write depth stencil state creation failed: {:08X}.",
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::LessEqualDepthRead),
				D3D11_COMPARISON_LESS_EQUAL);
			ThrowIfFailed(result,
						  "Less-equal, read depth stencil state creation failed: {:08X}.",
						  result);
		}

		{
			const HRESULT result = CreateDepthReadWriteDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::LessDepthReadWrite),
				D3D11_COMPARISON_LESS);
			ThrowIfFailed(result,
						  "Less, read-write depth stencil state creation failed: {:08X}.",
						  result);
		}

		{
			const HRESULT result = CreateDepthReadDepthStencilState(
				m_device, ReleaseAndGetAddressOf(DepthStencilStateID::LessDepthRead),
				D3D11_COMPARISON_LESS);
			ThrowIfFailed(result,
						  "Less, read depth stencil state creation failed: {:08X}.",
						  result);
		}
	}

	void StateManager::SetupRasterizerStates() {
		{
			const HRESULT result = CreateCullNoneRasterizerState(
				m_device, ReleaseAndGetAddressOf(RasterizerStateID::NoCulling));
			ThrowIfFailed(result, 
						  "No-culling rasterizer state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateCullClockwiseRasterizerState(
				m_device, ReleaseAndGetAddressOf(RasterizerStateID::ClockwiseCulling));
			ThrowIfFailed(result, 
						  "Clockwise-culling rasterizer state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateCullCounterClockwiseRasterizerState(
				m_device, ReleaseAndGetAddressOf(RasterizerStateID::CounterClockwiseCulling));
			ThrowIfFailed(result, 
						  "Counter-clockwise-culling rasterizer state creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateWireframeRasterizerState(
				m_device, ReleaseAndGetAddressOf(RasterizerStateID::Wireframe));
			ThrowIfFailed(result, 
						  "Wireframe rasterizer state creation failed: {:08X}.", 
						  result);
		}
	}

	void StateManager::SetupSamplerStates() {
		{
			const HRESULT result = CreatePointWrapSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::PointWrap));
			ThrowIfFailed(result, 
						  "Point sampling state with wrapping creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreatePointClampSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::PointClamp));
			ThrowIfFailed(result, 
						  "Point sampling state with clamping creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreatePointMirrorSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::PointMirror));
			ThrowIfFailed(result, 
						  "Point sampling state with mirroring creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateLinearWrapSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::LinearWrap));
			ThrowIfFailed(result, 
						  "Linear sampling state with wrapping creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateLinearClampSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::LinearClamp));
			ThrowIfFailed(result, 
						  "Linear sampling state with clamping creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateLinearMirrorSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::LinearMirror));
			ThrowIfFailed(result, 
						  "Linear sampling state with mirroring creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateAnisotropicWrapSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::AnisotropicWrap));
			ThrowIfFailed(result, 
						  "Anisotropic sampling state with wrapping creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateAnisotropicClampSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::AnisotropicClamp));
			ThrowIfFailed(result, 
						  "Anisotropic sampling state with clamping creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreateAnisotropicMirrorSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::AnisotropicMirror));
			ThrowIfFailed(result, 
						  "Anisotropic sampling state with mirroring creation failed: {:08X}.", 
						  result);
		}

		{
			const HRESULT result = CreatePCFSamplerState(
				m_device, ReleaseAndGetAddressOf(SamplerStateID::PCF));
			ThrowIfFailed(result, 
						  "PCF sampling state creation failed: {:08X}.", 
						  result);
		}
	}

	void StateManager::BindPersistentState(
		ID3D11DeviceContext& device_context) const noexcept {

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
		ID3D11SamplerState* const samplers[] = {
			Get(SamplerStateID::PointWrap),
			Get(SamplerStateID::PointClamp),
			Get(SamplerStateID::PointMirror),
			Get(SamplerStateID::LinearWrap),
			Get(SamplerStateID::LinearClamp),
			Get(SamplerStateID::LinearMirror),
			Get(SamplerStateID::AnisotropicWrap),
			Get(SamplerStateID::AnisotropicClamp),
			Get(SamplerStateID::AnisotropicMirror),
			Get(SamplerStateID::PCF),
		};

		// Bind the samplers.
		Pipeline::BindSamplers(device_context,
							   SLOT_SAMPLER_POINT_WRAP,
			                   static_cast< U32 >(std::size(samplers)),
			                   samplers);
	}
}