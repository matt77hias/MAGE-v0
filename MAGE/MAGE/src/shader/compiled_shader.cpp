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

	CompiledShader::CompiledShader(const wstring &fname) 
		: m_bytecode(nullptr), m_bytecode_size(0), m_shader_blob() {

		// Compile/Read the vertex shader.
		const HRESULT result_shader_blob = D3DReadFileToBlob(fname.c_str(), m_shader_blob.ReleaseAndGetAddressOf());
		if (FAILED(result_shader_blob)) {
			throw FormattedException("D3DReadFileToBlob failed: %08X.", result_shader_blob);
		}

		m_bytecode      = static_cast< BYTE * >(m_shader_blob->GetBufferPointer());
		m_bytecode_size = m_shader_blob->GetBufferSize();
	}

	CompiledShader::CompiledShader(const BYTE *bytecode, SIZE_T bytecode_size)
		: m_bytecode(bytecode), m_bytecode_size(bytecode_size), m_shader_blob() {
		Assert(m_bytecode);	
	}

	CompiledShader::CompiledShader(const CompiledShader &compiled_shader) = default;

	CompiledShader::CompiledShader(CompiledShader &&compiled_shader) = default;

	CompiledShader::~CompiledShader() = default;

	//-------------------------------------------------------------------------
	// CompiledVertexShader
	//-------------------------------------------------------------------------
	
	CompiledVertexShader::CompiledVertexShader(const wstring &fname)
		: CompiledShader(fname) {}

	CompiledVertexShader::CompiledVertexShader(const BYTE *bytecode, SIZE_T bytecode_size)
		: CompiledShader(bytecode, bytecode_size) {}

	CompiledVertexShader::CompiledVertexShader(const CompiledVertexShader &compiled_vertex_shader) = default;

	CompiledVertexShader::CompiledVertexShader(CompiledVertexShader &&compiled_vertex_shader) = default;
	
	CompiledVertexShader::~CompiledVertexShader() = default;

	//-------------------------------------------------------------------------
	// CompiledPixelShader
	//-------------------------------------------------------------------------

	CompiledPixelShader::CompiledPixelShader(const wstring &fname)
		: CompiledShader(fname) {}

	CompiledPixelShader::CompiledPixelShader(const BYTE *bytecode, SIZE_T bytecode_size)
		: CompiledShader(bytecode, bytecode_size) {}

	CompiledPixelShader::CompiledPixelShader(const CompiledPixelShader &compiled_pixel_shader) = default;

	CompiledPixelShader::CompiledPixelShader(CompiledPixelShader &&compiled_pixel_shader) = default;

	CompiledPixelShader::~CompiledPixelShader() = default;
}