#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\compiled_shader.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3dcompiler.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Linker Directives
//-----------------------------------------------------------------------------
#pragma region

#pragma comment (lib, "d3dcompiler.lib")

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// CompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	CompiledShader::CompiledShader() noexcept = default;

	CompiledShader::CompiledShader(
		const CompiledShader& compiled_shader) noexcept = default;

	CompiledShader::CompiledShader(
		CompiledShader&& compiled_shader) noexcept = default;

	CompiledShader::~CompiledShader() = default;

	CompiledShader& CompiledShader
		::operator=(const CompiledShader& compiled_shader) noexcept = default;

	CompiledShader& CompiledShader
		::operator=(CompiledShader&& compiled_shader) noexcept = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// BufferCompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	BufferCompiledShader::BufferCompiledShader(
		gsl::span< const BYTE > bytecode) noexcept
		: CompiledShader(), 
		m_bytecode(bytecode.data()), 
		m_bytecode_size(static_cast< SIZE_T >(bytecode.size())) {}

	BufferCompiledShader::BufferCompiledShader(
		const BufferCompiledShader& compiled_shader) noexcept = default;

	BufferCompiledShader::BufferCompiledShader(
		BufferCompiledShader&& compiled_shader) noexcept = default;

	BufferCompiledShader::~BufferCompiledShader() = default;

	BufferCompiledShader& BufferCompiledShader
		::operator=(const BufferCompiledShader& compiled_shader) noexcept = default;

	BufferCompiledShader& BufferCompiledShader
		::operator=(BufferCompiledShader&& compiled_shader) noexcept = default;

	#pragma endregion

	//-------------------------------------------------------------------------
	// BlobCompiledShader
	//-------------------------------------------------------------------------
	#pragma region

	BlobCompiledShader::BlobCompiledShader(const wstring& fname) noexcept
		: CompiledShader(), 
		m_shader_blob() {
			
		// Compile/Read the vertex shader.
		const HRESULT result 
			= D3DReadFileToBlob(fname.c_str(), 
								m_shader_blob.ReleaseAndGetAddressOf());
		ThrowIfFailed(result, "D3DReadFileToBlob failed: %08X.", result);
	}

	BlobCompiledShader::BlobCompiledShader(
		const BlobCompiledShader& compiled_shader) noexcept = default;

	BlobCompiledShader::BlobCompiledShader(
		BlobCompiledShader&& compiled_shader) noexcept = default;

	BlobCompiledShader::~BlobCompiledShader() = default;

	BlobCompiledShader& BlobCompiledShader
		::operator=(const BlobCompiledShader& compiled_shader) noexcept = default;

	BlobCompiledShader& BlobCompiledShader
		::operator=(BlobCompiledShader&& compiled_shader) noexcept = default;

	#pragma endregion
}