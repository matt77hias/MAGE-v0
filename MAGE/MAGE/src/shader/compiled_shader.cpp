#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader.hpp"
#include "shader\shading.hpp"
#include "utils\logging\error.hpp"
#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	CompiledShader::CompiledShader() noexcept = default;

	CompiledShader::CompiledShader(
		const CompiledShader &compiled_shader) noexcept = default;

	CompiledShader::CompiledShader(
		CompiledShader &&compiled_shader) noexcept = default;

	CompiledShader::~CompiledShader() = default;

	CompiledShader &CompiledShader::operator=(
		const CompiledShader &compiled_shader) noexcept = default;

	CompiledShader &CompiledShader::operator=(
		CompiledShader &&compiled_shader) noexcept = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// BufferCompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	BufferCompiledShader::BufferCompiledShader(const BYTE *bytecode, 
		SIZE_T bytecode_size) noexcept
		: CompiledShader(), 
		m_bytecode(bytecode), 
		m_bytecode_size(bytecode_size) {
		
		Assert(m_bytecode);	
	}

	BufferCompiledShader::BufferCompiledShader(
		const BufferCompiledShader &compiled_shader) noexcept = default;

	BufferCompiledShader::BufferCompiledShader(
		BufferCompiledShader &&compiled_shader) noexcept = default;

	BufferCompiledShader::~BufferCompiledShader() = default;

	BufferCompiledShader &BufferCompiledShader::operator=(
		const BufferCompiledShader &compiled_shader) noexcept = default;

	BufferCompiledShader &BufferCompiledShader::operator=(
		BufferCompiledShader &&compiled_shader) noexcept = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// BlobCompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	BlobCompiledShader::BlobCompiledShader(const wstring &fname) noexcept
		: CompiledShader(), 
		m_shader_blob() {
			
		// Compile/Read the vertex shader.
		const HRESULT result_shader_blob 
			= D3DReadFileToBlob(fname.c_str(), 
				m_shader_blob.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader_blob, 
			"D3DReadFileToBlob failed: %08X.", result_shader_blob);
	}

	BlobCompiledShader::BlobCompiledShader(
		const BlobCompiledShader &compiled_shader) noexcept = default;

	BlobCompiledShader::BlobCompiledShader(
		BlobCompiledShader &&compiled_shader) noexcept = default;

	BlobCompiledShader::~BlobCompiledShader() = default;

	BlobCompiledShader &BlobCompiledShader::operator=(
		const BlobCompiledShader &compiled_shader) noexcept = default;

	BlobCompiledShader &BlobCompiledShader::operator=(
		BlobCompiledShader &&compiled_shader) noexcept = default;

	#pragma endregion
}