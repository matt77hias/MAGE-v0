#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader.hpp"
#include "shader\shading.hpp"
#include "logging\error.hpp"
#include "logging\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CompiledShader
	//-------------------------------------------------------------------------

	CompiledShader::CompiledShader() = default;

	CompiledShader::CompiledShader(
		const CompiledShader &compiled_shader) = default;

	CompiledShader::CompiledShader(
		CompiledShader &&compiled_shader) = default;

	CompiledShader::~CompiledShader() = default;

	//-------------------------------------------------------------------------
	// BufferCompiledShader
	//-------------------------------------------------------------------------

	BufferCompiledShader::BufferCompiledShader(
		const BYTE *bytecode, SIZE_T bytecode_size)
		: CompiledShader(), 
		m_bytecode(bytecode), 
		m_bytecode_size(bytecode_size) {
		
		Assert(m_bytecode);	
	}

	BufferCompiledShader::BufferCompiledShader(
		const BufferCompiledShader &compiled_shader) = default;

	BufferCompiledShader::BufferCompiledShader(
		BufferCompiledShader &&compiled_shader) = default;

	BufferCompiledShader::~BufferCompiledShader() = default;

	//-------------------------------------------------------------------------
	// BlobCompiledShader
	//-------------------------------------------------------------------------

	BlobCompiledShader::BlobCompiledShader(const wstring &fname)
		: CompiledShader(), m_shader_blob() {
			
		// Compile/Read the vertex shader.
		const HRESULT result_shader_blob 
			= D3DReadFileToBlob(fname.c_str(), 
				m_shader_blob.ReleaseAndGetAddressOf());
		ThrowIfFailed(result_shader_blob, 
			"D3DReadFileToBlob failed: %08X.", result_shader_blob);
	}

	BlobCompiledShader::BlobCompiledShader(
		const BlobCompiledShader &compiled_shader) = default;

	BlobCompiledShader::BlobCompiledShader(
		BlobCompiledShader &&compiled_shader) = default;

	BlobCompiledShader::~BlobCompiledShader() = default;
}