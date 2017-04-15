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

	void EmptyVertexShader::PrepareShading(const Material &material, const World &world, const TransformBuffer &transform_buffer) const {
		UNUSED(material);
		UNUSED(world);
		UNUSED(transform_buffer);
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
	}
	
	void EmptyPixelShader::PrepareShading(const Material &material, const World &world) const {
		UNUSED(material);
		UNUSED(world);
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}
}