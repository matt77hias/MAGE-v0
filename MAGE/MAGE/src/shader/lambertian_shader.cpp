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

	LambertianVertexShader::LambertianVertexShader(const RenderingDevice &device)
		: VertexShader(device, MAGE_FNAME_LAMBERTIAN_VS,
			VertexPositionNormalTexture::input_element_desc,
			VertexPositionNormalTexture::nb_input_elements) {

		const HRESULT result_buffers = device.CreateConstantBuffer< TransformBuffer >(m_cb_transform.ReleaseAndGetAddressOf());
		if (FAILED(result_buffers)) {
			Error("Constant buffer creation failed: %ld.", result_buffers);
			return;
		}
	}
}