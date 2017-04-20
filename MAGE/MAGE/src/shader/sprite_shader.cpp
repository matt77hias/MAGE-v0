//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "rendering\rendering_factory.hpp"
#include "shader\sprite_shader.hpp"
#include "shader\cso\sprite_PS.hpp"
#include "shader\cso\sprite_VS.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SpriteVertexShader
	//-------------------------------------------------------------------------

	SpriteVertexShader::SpriteVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: VertexShader(device, device_context, MAGE_GUID_SPRITE_VS, g_sprite_vs, sizeof(g_sprite_vs),
			VertexPositionColorTexture::input_element_desc, VertexPositionColorTexture::nb_input_elements) {

		const HRESULT result_cb_transform = CreateConstantBuffer< XMMATRIX >(m_device, m_transform_buffer.ReleaseAndGetAddressOf());
		if (FAILED(result_cb_transform)) {
			Error("Transformation constant buffer creation failed: %08X.", result_cb_transform);
			return;
		}
	}

	void SpriteVertexShader::PrepareShading(const XMMATRIX &transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->UpdateSubresource(m_transform_buffer.Get(), 0, nullptr, &transform, 0, 0);
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, m_transform_buffer.GetAddressOf());
	}

	//-------------------------------------------------------------------------
	// SpritePixelShader
	//-------------------------------------------------------------------------

	SpritePixelShader::SpritePixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: PixelShader(device, device_context, MAGE_GUID_SPRITE_PS, g_sprite_ps, sizeof(g_sprite_ps)) {}

	void SpritePixelShader::PrepareShading(ID3D11ShaderResourceView * const *texture) const {
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		m_device_context->PSSetShaderResources(0, 1, texture);
	}

	//-------------------------------------------------------------------------
	// Combined Sprite Shader
	//-------------------------------------------------------------------------

	CombinedShader CreateSpriteShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		ResourceFactory *factory = GetResourceFactory();
		SharedPtr< VertexShader > vs = factory->CreateSpriteVertexShader(device, device_context);
		SharedPtr< PixelShader >  ps = factory->CreateSpritePixelShader(device, device_context);
		return CombinedShader(vs, ps);
	}
}