//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\bump_shader.hpp"
#include "mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// BumpVertexShader
	//-------------------------------------------------------------------------

	BumpVertexShader::BumpVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &fname) 
		: VertexShader(device, device_context, fname, 
			VertexPositionNormalTexture::input_element_desc, 
			VertexPositionNormalTexture::nb_input_elements) {}
			
	BumpVertexShader::BumpVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledVertexShader &compiled_vertex_shader)
		: VertexShader(device, device_context, compiled_vertex_shader,
			VertexPositionNormalTexture::input_element_desc, 
			VertexPositionNormalTexture::nb_input_elements) {}
	
	BumpVertexShader::BumpVertexShader(BumpVertexShader &&vertex_shader) = default;

	BumpVertexShader::~BumpVertexShader() = default;

	void BumpVertexShader::PrepareShading(ID3D11Buffer *transform) const {
		m_device_context->IASetInputLayout(m_vertex_layout.Get());
		m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &transform);
	}

	//-------------------------------------------------------------------------
	// BumpPixelShader
	//-------------------------------------------------------------------------

	BumpPixelShader::BumpPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &fname)
			: PixelShader(device, device_context, fname),
			m_material_buffer(m_device, m_device_context) {}
			
	BumpPixelShader::BumpPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledPixelShader &compiled_pixel_shader)
			: PixelShader(device, device_context, compiled_pixel_shader),
			m_material_buffer(m_device, m_device_context) {}
	
	BumpPixelShader::BumpPixelShader(BumpPixelShader &&pixel_shader) = default;

	BumpPixelShader::~BumpPixelShader() = default;

	void BumpPixelShader::PrepareShading(const Material &material, const Lighting &lighting) const {

		MaterialBuffer buffer;
		buffer.m_Kd       = material.GetDiffuseReflectivity();
		buffer.m_dissolve = material.GetDissolve();
		buffer.m_Ks       = material.GetSpecularReflectivity();
		buffer.m_Ns       = material.GetSpecularExponent();
		buffer.m_param1   = material.GetParameter1();
		buffer.m_param2   = material.GetParameter2();
		buffer.m_param3   = material.GetParameter3();
		buffer.m_param4   = material.GetParameter4();
		m_material_buffer.UpdateData(buffer);
		
		m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		
		m_device_context->PSSetConstantBuffers(1, 1, m_material_buffer.GetAddressOf());
		m_device_context->PSSetConstantBuffers(2, 1, &lighting.m_light_data);
		m_device_context->PSSetShaderResources(1, 1, &lighting.m_omni_lights);
		m_device_context->PSSetShaderResources(2, 1, &lighting.m_spot_lights);

		Assert(material.GetDiffuseReflectivitySRV());
		m_device_context->PSSetShaderResources(0, 1, material.GetDiffuseReflectivitySRVAddress());
		Assert(material.GetNormalSRV());
		m_device_context->PSSetShaderResources(4, 1, material.GetNormalSRVAddress());
	}
}