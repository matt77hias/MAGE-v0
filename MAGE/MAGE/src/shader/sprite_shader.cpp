//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "shader\sprite_shader.hpp"
#include "mesh\vertex.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SpriteVertexShader
	//-------------------------------------------------------------------------

	SpriteVertexShader::SpriteVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: VertexShader(device, device_context, CreateCompiledSpriteVertexShader(),
			VertexPositionColorTexture::input_element_desc, VertexPositionColorTexture::nb_input_elements) {}

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

	SpritePixelShader::SpritePixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context)
		: PixelShader(device, device_context, CreateCompiledSpritePixelShader()) {}

	SpritePixelShader::SpritePixelShader(SpritePixelShader &&pixel_shader) = default;

	SpritePixelShader::~SpritePixelShader() = default;

	void SpritePixelShader::PrepareShading(ID3D11ShaderResourceView *texture) const {
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		m_device_context->PSSetShaderResources(0, 1, &texture);
	}

	//-------------------------------------------------------------------------
	// Combined Sprite Shader
	//-------------------------------------------------------------------------

	const CombinedShader CreateSpriteShader() {
		ID3D11Device2 *device = GetRenderingDevice();
		Assert(device);

		ID3D11DeviceContext2 *device_context = GetRenderingDeviceContext();
		Assert(device_context);

		ResourceFactory *factory = GetResourceFactory();
		Assert(factory);

		SharedPtr< VertexShader > vs = factory->CreateSpriteVertexShader(device, device_context);
		SharedPtr< PixelShader >  ps = factory->CreateSpritePixelShader(device, device_context);
		return CombinedShader(vs, ps);
	}
}