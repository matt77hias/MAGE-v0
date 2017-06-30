//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\sprite_shader.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SpriteVertexShader
	//-------------------------------------------------------------------------

	SpriteVertexShader::SpriteVertexShader(const wstring &fname)
		: SpriteVertexShader(fname, GetRenderingDevice(), GetRenderingDeviceContext()) {}

	SpriteVertexShader::SpriteVertexShader(const wstring &fname,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: VertexShader(fname, device, device_context,
			VertexPositionColorTexture::s_input_element_desc,
			VertexPositionColorTexture::s_nb_input_elements) {}

	SpriteVertexShader::SpriteVertexShader(const wstring &guid,
		const CompiledVertexShader &compiled_vertex_shader)
		: SpriteVertexShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_vertex_shader) {}

	SpriteVertexShader::SpriteVertexShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledVertexShader &compiled_vertex_shader)
		: VertexShader(guid, device, device_context,
			compiled_vertex_shader,
			VertexPositionColorTexture::s_input_element_desc,
			VertexPositionColorTexture::s_nb_input_elements) {}

	SpriteVertexShader::SpriteVertexShader(SpriteVertexShader &&vertex_shader) = default;

	SpriteVertexShader::~SpriteVertexShader() = default;

	void SpriteVertexShader::PrepareShading(ID3D11Buffer *transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &transform);
	}

	//-------------------------------------------------------------------------
	// SpritePixelShader
	//-------------------------------------------------------------------------

	SpritePixelShader::SpritePixelShader(const wstring &fname)
		: SpritePixelShader(fname, GetRenderingDevice(), GetRenderingDeviceContext()) {}

	SpritePixelShader::SpritePixelShader(const wstring &fname,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: PixelShader(fname, device, device_context) {}

	SpritePixelShader::SpritePixelShader(const wstring &guid,
		const CompiledPixelShader &compiled_pixel_shader)
		: SpritePixelShader(guid, GetRenderingDevice(), GetRenderingDeviceContext(),
			compiled_pixel_shader) {}

	SpritePixelShader::SpritePixelShader(const wstring &guid,
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledPixelShader &compiled_pixel_shader)
		: PixelShader(guid, device, device_context, compiled_pixel_shader) {}

	SpritePixelShader::SpritePixelShader(SpritePixelShader &&pixel_shader) = default;

	SpritePixelShader::~SpritePixelShader() = default;

	void SpritePixelShader::PrepareShading(ID3D11ShaderResourceView *texture) const {
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		m_device_context->PSSetShaderResources(0, 1, &texture);
	}
}