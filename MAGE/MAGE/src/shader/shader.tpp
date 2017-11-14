#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Shader
	//-------------------------------------------------------------------------

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::Shader(wstring guid,
		const CompiledShader &compiled_shader)
		: Shader(std::move(guid), Pipeline::GetDevice(), compiled_shader) {}

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::Shader(wstring guid, 
		ID3D11Device5 *device, const CompiledShader &compiled_shader)
		: Resource< Shader >(std::move(guid)), 
		m_shader() {

		SetupShader(device, compiled_shader);
	}

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::Shader(
		Shader< ShaderT, PipelineStageT > &&shader) = default;

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::~Shader() = default;
	
	template<>
	inline void Shader< ID3D11HullShader, Pipeline::HS >
		::SetupShader(ID3D11Device5 *device, 
			const CompiledShader &compiled_shader) {
		
		Assert(device);

		// Create the hull shader.
		const HRESULT result = device->CreateHullShader(
										compiled_shader.GetBytecode(), 
										compiled_shader.GetBytecodeSize(),
										nullptr, 
										m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Hull shader creation failed: %08X.", result);
	}

	template<>
	inline void Shader< ID3D11DomainShader, Pipeline::DS >
		::SetupShader(ID3D11Device5 *device, 
			const CompiledShader &compiled_shader) {

		Assert(device);

		// Create the domain shader.
		const HRESULT result = device->CreateDomainShader(
										compiled_shader.GetBytecode(), 
										compiled_shader.GetBytecodeSize(),
										nullptr, 
										m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Domain shader creation failed: %08X.", result);
	}

	template<>
	inline void Shader< ID3D11GeometryShader, Pipeline::GS >
		::SetupShader(ID3D11Device5 *device, 
			const CompiledShader &compiled_shader) {

		Assert(device);

		// Create the geometry shader.
		const HRESULT result = device->CreateGeometryShader(
										compiled_shader.GetBytecode(), 
										compiled_shader.GetBytecodeSize(),
										nullptr, 
										m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Geometry shader creation failed: %08X.", result);
	}

	template<>
	inline void Shader< ID3D11PixelShader, Pipeline::PS >
		::SetupShader(ID3D11Device5 *device, 
			const CompiledShader &compiled_shader) {

		Assert(device);

		// Create the pixel shader.
		const HRESULT result = device->CreatePixelShader(
										compiled_shader.GetBytecode(), 
										compiled_shader.GetBytecodeSize(),
										nullptr, 
										m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Pixel shader creation failed: %08X.", result);
	}

	template<>
	inline void Shader< ID3D11ComputeShader, Pipeline::CS >
		::SetupShader(ID3D11Device5 *device, 
			const CompiledShader &compiled_shader) {

		Assert(device);

		// Create the compute shader.
		const HRESULT result = device->CreateComputeShader(
										compiled_shader.GetBytecode(), 
										compiled_shader.GetBytecodeSize(),
										nullptr, 
										m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Compute shader creation failed: %08X.", result);
	}

	template< typename ShaderT, typename PipelineStageT >
	inline void Shader< ShaderT, PipelineStageT >::BindShader(
		ID3D11DeviceContext4 *device_context) const noexcept {

		PipelineStageT::BindShader(device_context, m_shader.Get());
	}
}