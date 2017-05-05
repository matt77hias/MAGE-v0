//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\basic_shader.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// BasicVertexShader
	//-------------------------------------------------------------------------

	BasicVertexShader::BasicVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &fname) 
		: VertexShader(device, device_context, fname, 
			VertexPositionNormalTexture::input_element_desc, 
			VertexPositionNormalTexture::nb_input_elements) {}
			
	BasicVertexShader::BasicVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledVertexShader &compiled_vertex_shader)
		: VertexShader(device, device_context, compiled_vertex_shader,
			VertexPositionNormalTexture::input_element_desc, 
			VertexPositionNormalTexture::nb_input_elements) {}
	
	BasicVertexShader::BasicVertexShader(BasicVertexShader &&vertex_shader) = default;

	BasicVertexShader::~BasicVertexShader() = default;

	void BasicVertexShader::PrepareShading(ID3D11Buffer *transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &transform);
	}

	//-------------------------------------------------------------------------
	// BasicPixelShader
	//-------------------------------------------------------------------------

	BasicPixelShader::BasicPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &fname)
			: PixelShader(device, device_context, fname),
			m_material_buffer(m_device, m_device_context) {}
			
	BasicPixelShader::BasicPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledPixelShader &compiled_pixel_shader)
			: PixelShader(device, device_context, compiled_pixel_shader),
			m_material_buffer(m_device, m_device_context) {}
	
	BasicPixelShader::BasicPixelShader(BasicPixelShader &&pixel_shader) = default;

	BasicPixelShader::~BasicPixelShader() = default;

	void BasicPixelShader::PrepareShading(const Material &material, const Lighting &lighting) const {

		MaterialBuffer buffer;
		buffer.m_Kd       = material.m_diffuse_reflectivity;
		buffer.m_dissolve = material.m_dissolve;
		buffer.m_Ks       = material.m_specular_reflectivity;
		buffer.m_Ns       = material.m_specular_exponent;
		m_material_buffer.UpdateData(buffer);
		
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		
		m_device_context->PSSetConstantBuffers(1, 1, m_material_buffer.GetAddressOf());
		m_device_context->PSSetConstantBuffers(2, 1, &lighting.m_light_data);
		m_device_context->PSSetShaderResources(1, 1, &lighting.m_omni_lights);
		m_device_context->PSSetShaderResources(2, 1, &lighting.m_spot_lights);

		// TODO
		if (material.m_diffuse_reflectivity_texture) {
			m_device_context->PSSetShaderResources(0, 1, material.m_diffuse_reflectivity_texture->GetTextureResourceViewAddress());
		}
	}
}