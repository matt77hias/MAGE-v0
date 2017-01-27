//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\vertex_shader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3dcompiler.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VertexShader::VertexShader(ID3D11Device2 *device, const wstring &fname) {

		const HRESULT result_shader = InitializeShader(device, fname);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
		}
	}

	VertexShader::~VertexShader() {
		const HRESULT result_shader = UninitializeShader();
		if (FAILED(result_shader)) {
			Error("Shader uninitialization failed: %ld.", result_shader);
		}
	}

	HRESULT VertexShader::InitializeShader(ID3D11Device2 *device, const wstring &fname) {

		// Compile the vertex shader.
		ID3DBlob *vertex_shader_blob = nullptr;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(fname.c_str(), &vertex_shader_blob);
		if (FAILED(result_vertex_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_vertex_shader_blob);
			return result_vertex_shader_blob;
		}

		// Create the vertex shader
		// 1. A pointer to the compiled vertex shader.
		// 2. The size of the compiled vertex shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a vertex shader.
		const HRESULT result_vertex_shader = device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), nullptr, &m_vertex_shader);
		// Release the ID3DBlob.
		vertex_shader_blob->Release();
		if (FAILED(result_vertex_shader)) {
			Error("VertexShader creation failed: %ld.", result_vertex_shader);
			return result_vertex_shader;
		}

		return S_OK;
	}

	HRESULT VertexShader::UninitializeShader() {
		SAFE_RELEASE(m_vertex_shader);
		return S_OK;
	}
}