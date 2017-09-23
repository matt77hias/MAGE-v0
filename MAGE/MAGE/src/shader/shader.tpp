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
	Shader< ShaderT, PipelineStageT >::Shader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: Shader(guid, Pipeline::GetDevice(), compiled_shader) {}

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::Shader(const wstring &guid,
		ID3D11Device2 *device, const CompiledShader *compiled_shader)
		: Resource< Shader >(guid), m_shader() {

		SetupShader(device, compiled_shader);
	}

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::Shader(
		Shader< ShaderT, PipelineStageT > &&shader) = default;

	template< typename ShaderT, typename PipelineStageT >
	Shader< ShaderT, PipelineStageT >::~Shader() = default;

	template<>
	void Shader< ID3D11HullShader, Pipeline::HS >
		::SetupShader(ID3D11Device2 *device, 
			const CompiledShader *compiled_shader) {
		
		Assert(device);
		Assert(compiled_shader);

		// Create the hull shader.
		const HRESULT result_shader = device->CreateHullShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader, 
			"Hull shader creation failed: %08X.", result_shader);
	}

	template<>
	void Shader< ID3D11DomainShader, Pipeline::DS >
		::SetupShader(ID3D11Device2 *device, 
			const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the domain shader.
		const HRESULT result_shader = device->CreateDomainShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader, 
			"Domain shader creation failed: %08X.", result_shader);
	}

	template<>
	void Shader< ID3D11GeometryShader, Pipeline::GS >
		::SetupShader(ID3D11Device2 *device, 
			const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the geometry shader.
		const HRESULT result_shader = device->CreateGeometryShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader, 
			"Geometry shader creation failed: %08X.", result_shader);
	}

	template<>
	void Shader< ID3D11PixelShader, Pipeline::PS >
		::SetupShader(ID3D11Device2 *device, 
			const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the pixel shader.
		const HRESULT result_shader = device->CreatePixelShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader, 
			"Pixel shader creation failed: %08X.", result_shader);
	}

	template<>
	void Shader< ID3D11ComputeShader, Pipeline::CS >
		::SetupShader(ID3D11Device2 *device, 
			const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the compute shader.
		const HRESULT result_shader = device->CreateComputeShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader, 
			"Compute shader creation failed: %08X.", result_shader);
	}

	template< typename ShaderT, typename PipelineStageT >
	inline void Shader< ShaderT, PipelineStageT >::BindShader(
		ID3D11DeviceContext2 *device_context) const noexcept {

		PipelineStageT::BindShader(device_context, m_shader.Get());
	}
}