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

	template< typename ShaderT >
	Shader< ShaderT >::Shader(const wstring &guid,
		const CompiledShader *compiled_shader)
		: Shader(guid, GetDevice(), compiled_shader) {}

	template< typename ShaderT >
	Shader< ShaderT >::Shader(const wstring &guid,
		ID3D11Device2 *device, const CompiledShader *compiled_shader)
		: Resource< Shader >(guid), m_shader() {

		SetupShader(device, compiled_shader);
	}

	template< typename ShaderT >
	Shader< ShaderT >::Shader(Shader< ShaderT > &&shader) = default;

	template< typename ShaderT >
	Shader< ShaderT >::~Shader() = default;

	template<>
	inline void Shader< ID3D11HullShader >::SetupShader(
		ID3D11Device2 *device, const CompiledShader *compiled_shader) {
		
		Assert(device);
		Assert(compiled_shader);

		// Create the hull shader.
		const HRESULT result_shader = device->CreateHullShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());

		if (FAILED(result_shader)) {
			throw FormattedException("Hull shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11DomainShader >::SetupShader(
		ID3D11Device2 *device, const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the domain shader.
		const HRESULT result_shader = device->CreateDomainShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_shader)) {
			throw FormattedException("Domain shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11GeometryShader >::SetupShader(
		ID3D11Device2 *device, const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the geometry shader.
		const HRESULT result_shader = device->CreateGeometryShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_shader)) {
			throw FormattedException("Geometry shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11PixelShader >::SetupShader(
		ID3D11Device2 *device, const CompiledShader *compiled_shader) {

		Assert(device);
		Assert(compiled_shader);

		// Create the pixel shader.
		const HRESULT result_shader = device->CreatePixelShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_shader)) {
			throw FormattedException("Pixel shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11ComputeShader >::SetupShader(
		ID3D11Device2 *device, const CompiledShader *compiled_shader) {

		// Create the compute shader.
		const HRESULT result_shader = device->CreateComputeShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_shader)) {
			throw FormattedException("Compute shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11HullShader >::BindShader(
		ID3D11DeviceContext2 *device_context) const noexcept {
		HS::BindShader(device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11DomainShader >::BindShader(
		ID3D11DeviceContext2 *device_context) const noexcept {
		DS::BindShader(device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11GeometryShader >::BindShader(
		ID3D11DeviceContext2 *device_context) const noexcept {
		GS::BindShader(device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11PixelShader >::BindShader(
		ID3D11DeviceContext2 *device_context) const noexcept {
		PS::BindShader(device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11ComputeShader >::BindShader(
		ID3D11DeviceContext2 *device_context) const noexcept {
		CS::BindShader(device_context, m_shader.Get());
	}
}