//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\empty_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void EmptyVertexShader::Render(ComPtr< ID3D11DeviceContext2 > device_context, const Material &material, const World &world, const TransformBuffer &transform_buffer) const {
		UNUSED(material);
		UNUSED(world);
		UNUSED(transform_buffer);
		device_context->IASetInputLayout(m_vertex_layout.Get());
		device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
	}
	
	void EmptyPixelShader::Render(ComPtr< ID3D11DeviceContext2 > device_context, const Material &material, const World &world) const {
		UNUSED(material);
		UNUSED(world);
		device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}
}