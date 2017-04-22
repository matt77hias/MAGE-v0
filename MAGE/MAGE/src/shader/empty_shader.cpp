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

	void EmptyVertexShader::PrepareShading(const XMMATRIX &transform) const {
		UNUSED(transform);
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
	}

	void EmptyVertexShader::PrepareShading(const TransformBuffer &transform) const {
		UNUSED(transform);
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
	}

	void EmptyPixelShader::PrepareShading(ID3D11ShaderResourceView * const *texture) const {
		UNUSED(texture);
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}
	
	void EmptyPixelShader::PrepareShading(const Material &material, const LightBuffer &lighting) const {
		UNUSED(material);
		UNUSED(lighting);
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
	}
}