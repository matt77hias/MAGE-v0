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
		: Shader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_shader) {}

	template< typename ShaderT >
	Shader< ShaderT >::Shader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledShader *compiled_shader)
		: Resource< Shader >(guid), 
		m_device(device), m_device_context(device_context), 
		m_shader() {

		Assert(device);
		Assert(device_context);
		Assert(compiled_shader);

		SetupShader(compiled_shader);
	}

	template< typename ShaderT >
	Shader< ShaderT >::Shader(Shader< ShaderT > &&shader) = default;

	template< typename ShaderT >
	Shader< ShaderT >::~Shader() = default;

	template<>
	inline void Shader< ID3D11HullShader >::SetupShader(const CompiledShader *compiled_shader) {

		// Create the hull shader.
		const HRESULT result_shader = m_device->CreateHullShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());

		if (FAILED(result_shader)) {
			throw FormattedException("Hull shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11DomainShader >::SetupShader(const CompiledShader *compiled_shader) {

		// Create the domain shader.
		const HRESULT result_shader = m_device->CreateDomainShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());

		if (FAILED(result_shader)) {
			throw FormattedException("Domain shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11GeometryShader >::SetupShader(const CompiledShader *compiled_shader) {

		// Create the geometry shader.
		const HRESULT result_shader = m_device->CreateGeometryShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());

		if (FAILED(result_shader)) {
			throw FormattedException("Geometry shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11PixelShader >::SetupShader(const CompiledShader *compiled_shader) {

		// Create the pixel shader.
		const HRESULT result_shader = m_device->CreatePixelShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());

		if (FAILED(result_shader)) {
			throw FormattedException("Pixel shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11ComputeShader >::SetupShader(const CompiledShader *compiled_shader) {

		// Create the compute shader.
		const HRESULT result_shader = m_device->CreateComputeShader(
			compiled_shader->GetBytecode(), compiled_shader->GetBytecodeSize(),
			nullptr, m_shader.ReleaseAndGetAddressOf());

		if (FAILED(result_shader)) {
			throw FormattedException("Compute shader creation failed: %08X.", result_shader);
		}
	}

	template<>
	inline void Shader< ID3D11HullShader >::BindShader() const noexcept {
		HS::BindShader(m_device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11DomainShader >::BindShader() const noexcept {
		DS::BindShader(m_device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11GeometryShader >::BindShader() const noexcept {
		GS::BindShader(m_device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11PixelShader >::BindShader() const noexcept {
		PS::BindShader(m_device_context, m_shader.Get());
	}

	template<>
	inline void Shader< ID3D11ComputeShader >::BindShader() const noexcept {
		CS::BindShader(m_device_context, m_shader.Get());
	}
}