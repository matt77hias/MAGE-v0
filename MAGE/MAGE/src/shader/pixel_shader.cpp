//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3dcompiler.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\pixel_shader.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PixelShader::PixelShader(ComPtr< ID3D11Device2 > device, const wstring &fname) 
		: Resource(fname) {

		const HRESULT result_shader = InitializeShader(device);
		if (FAILED(result_shader)) {
			Error("Shader initialization failed: %ld.", result_shader);
		}
	}
	
	HRESULT PixelShader::InitializeShader(ComPtr< ID3D11Device2 > device) {

		// Compile the pixel shader.
		ComPtr< ID3DBlob > pixel_shader_blob;
		const HRESULT result_pixel_shader_blob = D3DReadFileToBlob(GetFilename().c_str(), pixel_shader_blob.GetAddressOf());
		if (FAILED(result_pixel_shader_blob)) {
			Error("D3DReadFileToBlob failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader_blob;
		}

		// Create the pixel shader.
		// 1. A pointer to the compiled pixel shader.
		// 2. The size of the compiled pixel shader.
		// 3. A pointer to a class linkage interface.
		// 4. Address of a pointer to a pixel shader.
		const HRESULT result_pixel_shader = device->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), nullptr, m_pixel_shader.ReleaseAndGetAddressOf());
		if (FAILED(result_pixel_shader)) {
			Error("PixelShader creation failed: %ld.", result_pixel_shader_blob);
			return result_pixel_shader;
		}

		return S_OK;
	}

	void PixelShader::Update(ComPtr< ID3D11DeviceContext2 > device_context) {
		device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}
}