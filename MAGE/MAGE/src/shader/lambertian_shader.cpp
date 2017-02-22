//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\lambertian_shader.hpp"
#include "logging\error.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	LambertianVertexShader::LambertianVertexShader(ComPtr< ID3D11Device2 > device)
		: VertexShader(device, MAGE_FNAME_LAMBERTIAN_VS,
			VertexPositionNormalTexture::input_element_desc,
			VertexPositionNormalTexture::nb_input_elements) {

		const HRESULT result_buffers = SetupBuffers(device);
		if (FAILED(result_buffers)) {
			Error("Buffer setup failed: %ld.", result_buffers);
			return;
		}
	}

	HRESULT LambertianVertexShader::SetupBuffers(ComPtr< ID3D11Device2 > device) {
		// Describe the buffer resource.
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.Usage          = D3D11_USAGE_DEFAULT;	     // How the buffer is expected to be read from and written to.
		buffer_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER; // How the buffer will be bound to the pipeline.
		buffer_desc.CPUAccessFlags = 0;						     // No CPU access is necessary.
		buffer_desc.ByteWidth      = sizeof(TransformBuffer);	 // Size of the buffer in bytes.

		// Create the index buffer.
		// 1. A pointer to a D3D11_BUFFER_DESC structure that describes the buffer.
		// 2. A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initialization data.
		// 3. Address of a pointer to the ID3D11Buffer interface for the buffer object created.
		const HRESULT result_cb_transform = device->CreateBuffer(&buffer_desc, nullptr, m_cb_transform.ReleaseAndGetAddressOf());
		if (FAILED(result_cb_transform)) {
			return result_cb_transform;
		}

		return S_OK;
	}
}