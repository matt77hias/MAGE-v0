#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader.hpp"
#include "memory\memory.hpp"
#include "logging\exception.hpp"
#include "shader\shading.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CompiledVertexShader
	//-------------------------------------------------------------------------

	CompiledVertexShader::CompiledVertexShader(const wstring &fname) 
		: m_name(fname), m_bytecode(nullptr), m_bytecode_size(0) {

		// Compile/Read the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(fname.c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			throw FormattedException("D3DReadFileToBlob failed: %08X.", result_vertex_shader_blob);
		}

		m_bytecode      = static_cast< BYTE * >(vertex_shader_blob->GetBufferPointer());
		m_bytecode_size = vertex_shader_blob->GetBufferSize();

	}

	//-------------------------------------------------------------------------
	// CompiledPixelShader
	//-------------------------------------------------------------------------

	CompiledPixelShader::CompiledPixelShader(const wstring &fname) 
		: m_name(fname), m_bytecode(nullptr), m_bytecode_size(0) {

		// Compile/Read the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(fname.c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			throw FormattedException("D3DReadFileToBlob failed: %08X.", result_pixel_shader_blob);
		}

		m_bytecode      = static_cast< BYTE * >(pixel_shader_blob->GetBufferPointer());
		m_bytecode_size = pixel_shader_blob->GetBufferSize();
	}
}