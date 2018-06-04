#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::Shader(ID3D11Device& device, 
											  std::wstring guid,
											  const CompiledShader& compiled_shader)
		: Resource< Shader >(std::move(guid)), 
		m_shader() {

		SetupShader(device, compiled_shader);
	}

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >
		::Shader(Shader&& shader) noexcept = default;

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::~Shader() = default;
	
	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >& Shader< ShaderT, PipelineStageT >
		::operator=(Shader&& shader) noexcept = default;

	template<>
	inline void HullShader
		::SetupShader(ID3D11Device& device, 
		              const CompiledShader& compiled_shader) {
		
		// Create the hull shader.
		const HRESULT result = device.CreateHullShader(
			                           compiled_shader.GetBytecode(), 
			                           compiled_shader.GetBytecodeSize(), 
			                           nullptr, 
			                           m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Hull shader creation failed: %08X.", result);
	}

	template<>
	inline void DomainShader
		::SetupShader(ID3D11Device& device, 
		              const CompiledShader& compiled_shader) {

		// Create the domain shader.
		const HRESULT result = device.CreateDomainShader(
			                           compiled_shader.GetBytecode(), 
			                           compiled_shader.GetBytecodeSize(), 
			                           nullptr, 
			                           m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Domain shader creation failed: %08X.", result);
	}

	template<>
	inline void GeometryShader
		::SetupShader(ID3D11Device& device, 
		              const CompiledShader& compiled_shader) {

		// Create the geometry shader.
		const HRESULT result = device.CreateGeometryShader(
			                           compiled_shader.GetBytecode(), 
			                           compiled_shader.GetBytecodeSize(), 
			                           nullptr, 
			                           m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Geometry shader creation failed: %08X.", result);
	}

	template<>
	inline void PixelShader
		::SetupShader(ID3D11Device& device, 
		              const CompiledShader& compiled_shader) {

		// Create the pixel shader.
		const HRESULT result = device.CreatePixelShader(
			                           compiled_shader.GetBytecode(), 
			                           compiled_shader.GetBytecodeSize(), 
			                           nullptr, 
			                           m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Pixel shader creation failed: %08X.", result);
	}

	template<>
	inline void ComputeShader
		::SetupShader(ID3D11Device& device, 
		              const CompiledShader& compiled_shader) {

		// Create the compute shader.
		const HRESULT result = device.CreateComputeShader(
			                           compiled_shader.GetBytecode(), 
			                           compiled_shader.GetBytecodeSize(), 
			                           nullptr, 
			                           m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "Compute shader creation failed: %08X.", result);
	}

	template< typename ShaderT, typename PipelineStageT >
	inline void Shader< ShaderT, PipelineStageT >
		::BindShader(ID3D11DeviceContext& device_context) const noexcept {

		PipelineStageT::BindShader(device_context, m_shader.Get());
	}
}