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

	VertexShader::VertexShader(ComPtr< ID3D11Device2 > device, const wstring &name, const wstring &path)
		: Resource(name, path) {

		const HRESULT result_shader = InitializeShader(device);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
		}
	}

	HRESULT VertexShader::InitializeShader(ComPtr< ID3D11Device2 > device) {

		// Compile the vertex shader.
		ComPtr< ID3DBlob > vertex_shader_blob;
		const HRESULT result_vertex_shader_blob = D3DReadFileToBlob(GetFilename().c_str(), vertex_shader_blob.GetAddressOf());
		if (FAILED(result_vertex_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_vertex_shader_blob);
			return result_vertex_shader_blob;
		}

		// Create the vertex shader
		// 1. A pointer to the compiled vertex shader.
		// 2. The size of the compiled vertex shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a vertex shader.
		const HRESULT result_vertex_shader = device->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), nullptr, m_vertex_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_vertex_shader)) {
			Error("VertexShader creation failed: %ld.", result_vertex_shader);
			return result_vertex_shader;
		}

		return S_OK;
	}
}