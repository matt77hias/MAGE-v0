//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\pixel_shader.hpp"
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

	PixelShader::PixelShader(ID3D11Device2 *device, const wstring &fname) {

		const HRESULT result_shader = InitializeShader(device, fname);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
		}
	}
	
	PixelShader::~PixelShader() {
		const HRESULT result_shader = UninitializeShader();
		if (FAILED(result_shader)) {
			Error("Shader uninitialization failed: %ld.", result_shader);
		}
	}

	HRESULT PixelShader::InitializeShader(ID3D11Device2 *device, const wstring &fname) {

		// Compile the pixel shader.
		ID3DBlob *pixel_shader_blob = nullptr;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(fname.c_str(), &pixel_shader_blob);
		if (FAILED(result_pixel_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader_blob;
		}

		// Create the pixel shader.
		// 1. A pointer to the compiled pixel shader.
		// 2. The size of the compiled pixel shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a pixel shader.
		const HRESULT result_pixel_shader = device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), nullptr, &m_pixel_shader);
		// Release the ID3DBlob.
		pixel_shader_blob->Release();
		if (FAILED(result_pixel_shader)) {
			Error("PixelShader creation failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader;
		}

		return S_OK;
	}

	HRESULT PixelShader::UninitializeShader() {
		SAFE_RELEASE(m_pixel_shader);
		return S_OK;
	}
}